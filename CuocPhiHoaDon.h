#ifndef PHIEUKHIEUNAI_H
#define PHIEUKHIEUNAI_H

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
#include "PhieuGui.h"

using namespace std;

// --- LOP THUC THE PHIEUKHIEUNAI ---
class PhieuKhieuNai : public Entity {
private:
    string maPhieuGui;
    string lyDo;
    string trangThaiXuLy; // "Tiep nhan", "Dang xu ly", "Da gia quyet"

public:
    PhieuKhieuNai() : Entity(), maPhieuGui(""), lyDo(""), trangThaiXuLy("Tiep nhan") {}

    string getMaPhieuGui() const { return maPhieuGui; }
    void setMaPhieuGui(const string& maPG) {
        if (maPG.empty()) throw invalid_argument("Ma phieu gui khong duoc de trong!");
        maPhieuGui = maPG;
    }

    string getLyDo() const { return lyDo; }
    void setLyDo(const string& ld) {
        if (ld.empty()) throw invalid_argument("Ly do khieu nai khong duoc de trong!");
        lyDo = ld;
    }

    string getTrangThaiXuLy() const { return trangThaiXuLy; }
    void setTrangThaiXuLy(const string& tt) {
        if (tt.empty()) throw invalid_argument("Trang thai xu ly khong duoc de trong!");
        trangThaiXuLy = tt;
    }

    void nhap() override {
        string temp;
        while (true) {
            try {
                cout << "Nhap ly do khieu nai: ";
                getline(cin, temp);
                setLyDo(temp);
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }

        cout << "Chon trang thai xu ly (1 - Tiep nhan, 2 - Dang xu ly, 3 - Da gia quyet) [Default: 1]: ";
        getline(cin, temp);
        if (temp == "2") trangThaiXuLy = "Dang xu ly";
        else if (temp == "3") trangThaiXuLy = "Da gia quyet";
        else trangThaiXuLy = "Tiep nhan";
    }

    void xuat() const override {
        cout << left << setw(12) << maID 
             << "| " << setw(12) << maPhieuGui 
             << "| " << setw(35) << lyDo 
             << "| " << setw(15) << trangThaiXuLy << endl;
    }

    string toFileRecord() const override {
        stringstream ss;
        ss << maID << "|" << maPhieuGui << "|" << lyDo << "|" << trangThaiXuLy;
        return ss.str();
    }

    void fromFileRecord(const string& record) override {
        stringstream ss(record);
        string item;
        vector<string> tokens;
        while (getline(ss, item, '|')) tokens.push_back(item);
        if (tokens.size() == 4) {
            maID = tokens[0];
            maPhieuGui = tokens[1];
            lyDo = tokens[2];
            trangThaiXuLy = tokens[3];
        }
    }
};

// --- LOP GIAO DIEN (MENU PHIEUKHIEUNAI) ---
class PhieuKhieuNaiMenu {
private:
    Repository<PhieuKhieuNai>& repoKN;
    Repository<PhieuGui>& repoPG;

    void xoaManHinh() const { system("cls"); }
    void tamDung() const { cout << "\nNhan Enter de tiep tuc..."; cin.get(); }

    void inTieuDeBang() const {
        cout << left << setw(12) << "Ma Khieu Nai" 
             << "| " << setw(12) << "Ma Phieu Gui" 
             << "| " << setw(35) << "Ly Do Khieu Nai" 
             << "| " << setw(15) << "Trang Thai" << endl;
        cout << string(80, '-') << endl;
    }

public:
    PhieuKhieuNaiMenu(Repository<PhieuKhieuNai>& kn, Repository<PhieuGui>& pg) : repoKN(kn), repoPG(pg) {}

    void themMoi() {
        cout << "\n=== THEM MOI PHIEU KHIEU NAI ===\n";
        PhieuKhieuNai kn;
        string temp;

        while (true) {
            try {
                cout << "Nhap ma phieu khieu nai (VD: KN01): ";
                getline(cin, temp);
                kn.setMaID(temp);
                if (repoKN.findById(temp) != nullptr) throw invalid_argument("Ma khieu nai da ton tai!");
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }

        while (true) {
            try {
                cout << "Nhap ma Phieu gui can khieu nai (VD: PG01): ";
                getline(cin, temp);
                if (temp.empty()) throw invalid_argument("Khong duoc de trong!");
                if (repoPG.findById(temp) == nullptr) {
                    throw invalid_argument("Phieu gui nay chua ton tai! Vui long kiem tra lai.");
                }
                kn.setMaPhieuGui(temp);
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << "\n";
            }
        }

        kn.nhap();
        repoKN.add(kn);
        cout << "-> Them phieu khieu nai thanh cong!\n";
    }

    void xemDanhSach() const {
        auto list = repoKN.getAll();
        if (list.empty()) {
            cout << "\nDanh sach khieu nai trong!\n";
            return;
        }
        cout << "\n================================ DANH SACH PHIEU KHIEU NAI ================================\n";
        inTieuDeBang();
        for (const auto& item : list) item.xuat();
        cout << "Tong so phieu khieu nai: " << list.size() << endl;
    }

    void timKiem() const {
        string id;
        cout << "Nhap ma phieu khieu nai can tim: ";
        getline(cin, id);
        PhieuKhieuNai* result = repoKN.findById(id);
        if (result != nullptr) {
            cout << "\nDa tim thay thong tin:\n";
            inTieuDeBang();
            result->xuat();
        }
        else cout << "Khong tim thay phieu khieu nai ma: " << id << "\n";
    }

    void sapXep() {
        auto list = repoKN.getAll();
        if (list.empty()) {
            cout << "\nDanh sach trong!\n";
            return;
        }

        sort(list.begin(), list.end(), [](const PhieuKhieuNai& a, const PhieuKhieuNai& b) {
            return a.getTrangThaiXuLy() < b.getTrangThaiXuLy(); // Theo Alphabet trang thai
        });

        cout << "-> Da sap xep danh sach theo Trang Thai Xu Ly!\n";
        cout << "\n================================ KET QUA SAP XEP ================================\n";
        inTieuDeBang();
        for (const auto& item : list) item.xuat();
    }

    void capNhat() {
        string id;
        cout << "Nhap ma phieu khieu nai can cap nhat: ";
        getline(cin, id);
        PhieuKhieuNai* old = repoKN.findById(id);
        if (old == nullptr) {
            cout << "Khong tim thay ma nay!\n";
            return;
        }

        cout << "\nThong tin hien tai:\n";
        inTieuDeBang();
        old->xuat();
        cout << "\n(Luu y: De trong neu muon giu nguyen gia tri cu)\n";

        PhieuKhieuNai newData = *old;
        string temp;

        cout << "Nhap ma Phieu gui moi [" << old->getMaPhieuGui() << "]: ";
        getline(cin, temp);
        if (!temp.empty()) {
            if (repoPG.findById(temp) == nullptr) {
                cout << "Loi: Phieu gui nay chua ton tai! Giu nguyen ma phieu gui cu.\n";
            }
            else newData.setMaPhieuGui(temp);
        }

        cout << "Nhap ly do moi [" << old->getLyDo() << "]: ";
        getline(cin, temp);
        if (!temp.empty()) newData.setLyDo(temp);

        cout << "Nhap trang thai moi (1 - Tiep nhan, 2 - Dang xu ly, 3 - Da gia quyet) [" << old->getTrangThaiXuLy() << "]: ";
        getline(cin, temp);
        if (temp == "1") newData.setTrangThaiXuLy("Tiep nhan");
        else if (temp == "2") newData.setTrangThaiXuLy("Dang xu ly");
        else if (temp == "3") newData.setTrangThaiXuLy("Da gia quyet");

        if (repoKN.update(id, newData)) cout << "-> Cap nhat thanh cong!\n";
        else cout << "Loi khi cap nhat!\n";
    }

    void xoa() {
        string id;
        cout << "Nhap ma phieu khieu nai can xoa: ";
        getline(cin, id);
        PhieuKhieuNai* target = repoKN.findById(id);
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
            if (repoKN.removeById(id)) cout << "-> Xoa thanh cong!\n";
        }
        else cout << "Huy thao tac xoa.\n";
    }

    void menu() {
        int choice = -1;
        do {
            xoaManHinh();
            cout << "========== QUAN LY PHIEU KHIEU NAI ==========\n";
            cout << "1. Them phieu khieu nai moi\n";
            cout << "2. Xem danh sach\n";
            cout << "3. Tim kiem\n";
            cout << "4. Sap xep theo Trang Thai\n";
            cout << "5. Cap nhat\n";
            cout << "6. Xoa\n";
            cout << "0. Quay lai menu chinh\n";
            cout << "=============================================\nLua chon cua ban: ";
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
