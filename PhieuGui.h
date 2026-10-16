#ifndef PHIEUGUI_H
#define PHIEUGUI_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include "Entity.h"
#include "Repository.h"
#include "BuuCuc.h"

using namespace std;

// --- LOP THUC THE ---
class PhieuGui : public Entity {
private:
    string tenNguoiNhan;
    double trongLuong;
    string maBuuCucGui;

public:
    PhieuGui() : Entity(), tenNguoiNhan(""), trongLuong(0.0), maBuuCucGui("") {}

    string getTenNguoiNhan() const { 
        return tenNguoiNhan; 
    }
    void setTenNguoiNhan(const string& ten) {
        if (ten.empty()) throw invalid_argument("Ten nguoi nhan khong duoc de trong!");
        tenNguoiNhan = ten;
    }

    double getTrongLuong() const {
        return trongLuong; 
    }
    void setTrongLuong(double tl) {
        if (tl <= 0) throw invalid_argument("Trong luong phai lon hon 0!");
        trongLuong = tl;
    }

    string getMaBuuCucGui() const { 
        return maBuuCucGui; 
    }
    void setMaBuuCucGui(const string& maBC) {
        if (maBC.empty()) throw invalid_argument("Ma buu cuc khong duoc de trong!");
        maBuuCucGui = maBC;
    }

    void nhap() override {
        string temp;
        while (true) {
            try {
                cout << "Nhap ten nguoi nhan: "; 
                getline(cin, temp);
                setTenNguoiNhan(temp); 
                break;
            }
            catch (const exception& e) { 
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n"; 
            }
        }
        while (true) {
            try {
                cout << "Nhap trong luong (kg): "; 
                cin >> trongLuong;
                if (cin.fail() || trongLuong <= 0) {
                    cin.clear(); cin.ignore(10000, '\n');
                    throw invalid_argument("Trong luong phai la so thuc lon hon 0!");
                }
                cin.ignore(); break;
            }
            catch (const exception& e) { 
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n"; 
            }
        }
    }

    void xuat() const override {
        cout << left << setw(10) << maID << "| " << setw(25) << tenNguoiNhan
            << "| " << setw(15) << trongLuong << "| " << setw(15) << maBuuCucGui << endl;
    }

    string toFileRecord() const override {
        stringstream ss;
        ss << maID << "|" << tenNguoiNhan << "|" << trongLuong << "|" << maBuuCucGui;
        return ss.str();
    }

    void fromFileRecord(const string& record) override {
        stringstream ss(record);
        string item;
        vector<string> tokens;
        while (getline(ss, item, '|')) tokens.push_back(item);
        if (tokens.size() == 4) {
            maID = tokens[0];
            tenNguoiNhan = tokens[1];
            trongLuong = stod(tokens[2]); 
            maBuuCucGui = tokens[3];
        }
    }
};

// --- LOP GIAO DIEN (MENU) ---
class PhieuGuiMenu {
private:
    Repository<PhieuGui>& repoPG;
    Repository<BuuCuc>& repoBC;

    void xoaManHinh() const {
        system("cls"); 
    }
    void tamDung() const { 
        cout << "\nNhan Enter de tiep tuc...";
        cin.get(); 
    }
    void inTieuDeBang() const {
        cout << left << setw(10) << "Ma Phieu" << "| " << setw(25) << "Nguoi Nhan"
            << "| " << setw(15) << "Trong Luong(kg)" << "| " << setw(15) << "Ma Buu Cuc" << endl;
        cout << string(70, '-') << endl;
    }

public:
    PhieuGuiMenu(Repository<PhieuGui>& pg, Repository<BuuCuc>& bc) : repoPG(pg), repoBC(bc) {}

    void themMoi() {
        cout << "\n=== THEM MOI PHIEU GUI ===\n";
        PhieuGui pg; string temp;

        while (true) {
            try {
                cout << "Nhap ma phieu gui (VD: PG01): "; getline(cin, temp);
                pg.setMaID(temp);
                if (repoPG.findById(temp) != nullptr) throw invalid_argument("Ma phieu gui da ton tai!");
                break;
            }
            catch (const exception& e) { 
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }

        while (true) {
            try {
                cout << "Nhap ma Buu cuc gui (VD: BC01): ";
                getline(cin, temp);
                if (temp.empty()) throw invalid_argument("Khong duoc de trong!");
                if (repoBC.findById(temp) == nullptr) {
                    throw invalid_argument("Buu cuc nay chua ton tai! Vui long kiem tra hoac tao Buu cuc truoc.");
                }
                pg.setMaBuuCucGui(temp);
                break;
            }
            catch (const exception& e) { 
                cout << "Loi: " << e.what() << "\n";
            }
        }

        pg.nhap();
        repoPG.add(pg);
        cout << "-> Them moi thanh cong!\n";
    }

    void xemDanhSach() const {
        auto list = repoPG.getAll();
        if (list.empty()) { 
            cout << "\nDanh sach trong!\n"; 
            return; 
        }
        cout << "\n====================== DANH SACH PHIEU GUI ======================\n";
        inTieuDeBang();
        for (const auto& item : list) item.xuat();
        cout << "Tong so phieu gui: " << list.size() << endl;
    }

    // BO SUNG CHUC NANG TIM KIEM
    void timKiem() const {
        string id; cout << "Nhap ma phieu gui can tim: "; getline(cin, id);
        PhieuGui* result = repoPG.findById(id);
        if (result != nullptr) {
            cout << "\nDa tim thay thong tin:\n"; inTieuDeBang(); result->xuat();
        }
        else cout << "Khong tim thay phieu gui ma: " << id << "\n";
    }

    // CHUC NANG 4: SAP XEP
    void sapXep() {
        auto list = repoPG.getAll();
        if (list.empty()) { 
            cout << "\nDanh sach trong!\n";
            return;
        }

        sort(list.begin(), list.end(), [](const PhieuGui& a, const PhieuGui& b) {
            return a.getTrongLuong() > b.getTrongLuong(); // Giam dan
            });

        cout << "-> Da sap xep danh sach hien thi theo Trong Luong (Giam dan)!\n";
        cout << "\n====================== KET QUA SAP XEP ======================\n";
        inTieuDeBang();
        for (const auto& item : list) item.xuat();
    }

    void capNhat() {
        string id; cout << "Nhap ma phieu can cap nhat: "; 
        getline(cin, id);
        PhieuGui* old = repoPG.findById(id);
        if (old == nullptr) { 
            cout << "Khong tim thay ma nay!\n";
            return; 
        }

        cout << "\nThong tin hien tai:\n"; 
        inTieuDeBang(); 
        old->xuat();
        cout << "\n(Luu y: De trong hoac nhap -1 neu muon giu nguyen gia tri cu)\n";

        PhieuGui newData = *old;
        string temp;

        cout << "Nhap nguoi nhan moi [" << old->getTenNguoiNhan() << "]: "; 
        getline(cin, temp);
        if (!temp.empty()) newData.setTenNguoiNhan(temp);

        try {
            cout << "Nhap trong luong moi [" << old->getTrongLuong() << "]: "; 
            getline(cin, temp);
            if (!temp.empty() && stod(temp) != -1) newData.setTrongLuong(stod(temp));
        }
        catch (...) {}

        cout << "Nhap ma Buu cuc moi [" << old->getMaBuuCucGui() << "]: "; 
        getline(cin, temp);
        if (!temp.empty()) {
            if (repoBC.findById(temp) == nullptr) {
                cout << "Loi: Buu cuc nay chua ton tai! Giu nguyen ma buu cuc cu.\n";
            }
            else newData.setMaBuuCucGui(temp);
        }

        if (repoPG.update(id, newData)) cout << "-> Cap nhat thanh cong!\n";
        else cout << "Loi khi cap nhat!\n";
    }

    void xoa() {
        string id; cout << "Nhap ma phieu gui can xoa: "; 
        getline(cin, id);
        PhieuGui* target = repoPG.findById(id);
        if (target == nullptr) { 
            cout << "Khong tim thay ma nay!\n";
            return; 
        }

        cout << "\nThong tin chuan bi xoa:\n"; 
        inTieuDeBang(); 
        target->xuat();
        cout << "Ban co chac chan muon xoa khong? (y/n): ";
        char confirm;
        cin >> confirm; 
        cin.ignore(10000, '\n');

        if (confirm == 'y' || confirm == 'Y') {
            if (repoPG.removeById(id)) cout << "-> Xoa thanh cong!\n";
        }
        else cout << "Huy thao tac xoa.\n";
    }

    void menu() {
        int choice = -1;
        do {
            xoaManHinh();
            cout << "========== QUAN LY PHIEU GUI ==========\n";
            cout << "1. Them phieu gui moi\n";
            cout << "2. Xem danh sach\n";
            cout << "3. Tim kiem\n";
            cout << "4. Sap xep theo Trong Luong\n";
            cout << "5. Cap nhat\n";
            cout << "6. Xoa\n";
            cout << "0. Quay lai menu chinh\n";
            cout << "=======================================\nLua chon cua ban: ";
            if (!(cin >> choice)) { 
                cin.clear(); choice = -1; 
            }
            cin.ignore(10000, '\n');
            if (choice == 0) break;

            xoaManHinh();
            switch (choice) {
            case 1: themMoi(); break;
            case 2: xemDanhSach(); break;
            case 3: timKiem(); break;
            case 4: sapXep(); break;
            case 5: capNhat(); break;
            case 6: xoa(); break;
            default: cout << "Lua chon khong hop le!\n";
            }
            tamDung();
        } while (choice != 0);
    }
};

#endif