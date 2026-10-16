#ifndef TUYENVANCHUYEN_H
#define TUYENVANCHUYEN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <filesystem>   
#include <cstdlib>      
#include "Entity.h"

using namespace std;

// ==========================================
// 2. LOP THUC THE (TuyenVanChuyen)
// ==========================================
class TuyenVanChuyen : public Entity {
private:
    string tenTuyen;
    double khoangCach;      
    int thoiGianDuKien;     

public:
    TuyenVanChuyen() : Entity(), tenTuyen(""), khoangCach(0.0), thoiGianDuKien(0) {}

    string getTenTuyen() const { return tenTuyen; }
    void setTenTuyen(const string& ten) 
    {
        if (ten.empty()) throw invalid_argument("Ten tuyen khong duoc de trong!");
        tenTuyen = ten;
    }

    double getKhoangCach() const { return khoangCach; }
    void setKhoangCach(double kc) 
    {
        if (kc <= 0) throw invalid_argument("Khoang cach phai lon hon 0!");
        khoangCach = kc;
    }

    int getThoiGianDuKien() const { return thoiGianDuKien; }
    void setThoiGianDuKien(int tg) 
    {
        if (tg <= 0) throw invalid_argument("Thoi gian du kien phai lon hon 0!");
        thoiGianDuKien = tg;
    }

    void nhap() override 
    {
        string temp;
        while (true) {
            try 
            {
                cout << "Nhap ten tuyen: ";
                getline(cin, temp);
                setTenTuyen(temp);
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }

        while (true) 
        {
            try 
            {
                cout << "Nhap khoang cach (km): ";
                cin >> khoangCach;
                if (cin.fail() || khoangCach <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw invalid_argument("Khoang cach phai la so thuc lon hon 0!");
                }
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }

        while (true) 
        {
            try 
            {
                cout << "Nhap thoi gian du kien (gio): ";
                cin >> thoiGianDuKien;
                if (cin.fail() || thoiGianDuKien <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw invalid_argument("Thoi gian phai la so nguyen lon hon 0!");
                }
                cin.ignore(); 
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }
    }

    void xuat() const override 
    {
        cout << left << setw(10) << maID
            << "| " << setw(25) << tenTuyen
            << "| " << setw(15) << khoangCach
            << "| " << setw(15) << thoiGianDuKien << endl;
    }

    string toFileRecord() const override 
    {
        stringstream ss;
        ss << maID << "|" << tenTuyen << "|" << khoangCach << "|" << thoiGianDuKien;
        return ss.str();
    }

    void fromFileRecord(const string& record) override 
    {
        stringstream ss(record);
        string item;
        vector<string> tokens;
        while (getline(ss, item, '|')) {
            tokens.push_back(item);
        }
        if (tokens.size() == 4) {
            maID = tokens[0];
            tenTuyen = tokens[1];
            khoangCach = stod(tokens[2]);
            thoiGianDuKien = stoi(tokens[3]);
        }
    }
};

// ==========================================
// 3. LOP QUAN LY (REPOSITORY / CONTROLLER)
// ==========================================
class QuanLyTuyenVanChuyen 
{
private:
    vector<TuyenVanChuyen> danhSach;
    string filePath = "data/tuyen_van_chuyen.txt";

    // Tu dong tao thu muc data/ neu chua co
    void kiemTraVaTaoThuMuc() 
    {
        if (!filesystem::exists("data")) {
            filesystem::create_directories("data");
        }
    }

    
    void xoaManHinh() const {
        system("cls");
    }

    void tamDung() const {
        cout << "\nNhan Enter de quay lai menu...";
        cin.get();
    }

    void inTieuDeBang() const {
        cout << left << setw(10) << "Ma Tuyen"
            << "| " << setw(25) << "Ten Tuyen"
            << "| " << setw(15) << "Khoang Cach(km)"
            << "| " << setw(15) << "Thoi Gian(h)" << endl;
        cout << string(70, '-') << endl;
    }

public:
    QuanLyTuyenVanChuyen() 
    {
        kiemTraVaTaoThuMuc();
        docFile();
    }

 
    void docFile() {
        danhSach.clear();
        ifstream file(filePath);
        if (!file.is_open()) return; 

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            try {
                TuyenVanChuyen tvc;
                tvc.fromFileRecord(line);
                danhSach.push_back(tvc);
            }
            catch (...) {
                // Bo qua dong bi loi dinh dang
            }
        }
        file.close();
    }

    void ghiFile() {
        kiemTraVaTaoThuMuc();
        ofstream file(filePath);
        for (const auto& item : danhSach) {
            file << item.toFileRecord() << endl;
        }
        file.close();
    }

    // --- C: CREATE (Them moi) ---
    void themMoi() {
        cout << "\n=== THEM MOI TUYEN VAN CHUYEN ===\n";
        TuyenVanChuyen tvc;
        string id;

        while (true) 
        {
            try {
                cout << "Nhap ma tuyen (VD: TVC01): ";
                getline(cin, id);
                tvc.setMaID(id);

                // Kiem tra ma dinh danh khong duoc trung
                auto it = find_if(danhSach.begin(), danhSach.end(), [&](const TuyenVanChuyen& x) {
                    return x.getMaID() == id;
                    });
                if (it != danhSach.end()) {
                    throw invalid_argument("Ma tuyen nay da ton tai trong he thong!");
                }
                break;
            }
            catch (const exception& e) {
                cout << "Loi: " << e.what() << " Vui long nhap lai.\n";
            }
        }

        tvc.nhap();
        danhSach.push_back(tvc);
        ghiFile(); 
        cout << "-> Them moi thanh cong!\n";
    }

    // --- R: READ (Xem danh sach & Tim kiem) ---
    void xemDanhSach() const 
    {
        if (danhSach.empty()) {
            cout << "\nDanh sach trong!\n";
            return;
        }
        cout << "\n======================== DANH SACH TUYEN VAN CHUYEN ========================\n";
        inTieuDeBang();
        for (const auto& item : danhSach) {
            item.xuat();
        }
        cout << "Tong so dau tuyen: " << danhSach.size() << endl;
    }

    void timKiem() const 
    {
        string id;
        cout << "Nhap ma tuyen can tim: ";
        getline(cin, id);

        auto it = find_if(danhSach.begin(), danhSach.end(), [&](const TuyenVanChuyen& x) {
            return x.getMaID() == id;
            });

        if (it != danhSach.end()) {
            cout << "\nDa tim thay thong tin:\n";
            inTieuDeBang();
            it->xuat();
        }
        else {
            cout << "Khong tim thay tuyen co ma: " << id << endl;
        }
    }

    // --- U: UPDATE (Cap nhat) ---
    void capNhat() 
    {
        string id;
        cout << "Nhap ma tuyen can cap nhat: ";
        getline(cin, id);

        auto it = find_if(danhSach.begin(), danhSach.end(), [&](TuyenVanChuyen& x) {
            return x.getMaID() == id;
            });

        if (it == danhSach.end()) {
            cout << "Khong tim thay ma tuyen nay!\n";
            return;
        }

        cout << "\nThong tin hien tai:\n";
        inTieuDeBang();
        it->xuat();
        cout << "\n(Luu y: De trong neu muon giu nguyen gia tri cu)\n";

        string temp;

        // Sua ten tuyen
        cout << "Nhap ten tuyen moi [" << it->getTenTuyen() << "]: ";
        getline(cin, temp);
        if (!temp.empty()) {
            it->setTenTuyen(temp);
        }

        // Sua khoang cach
        try {
            cout << "Nhap khoang cach moi [" << it->getKhoangCach() << "] (Nhap -1 de bo qua): ";
            getline(cin, temp);
            if (!temp.empty() && stod(temp) != -1) {
                it->setKhoangCach(stod(temp));
            }
        }
        catch (...) {
            cout << "Gia tri khoang cach khong hop le, giu nguyen cu.\n";
        }

        // Sua thoi gian du kien
        try {
            cout << "Nhap thoi gian moi [" << it->getThoiGianDuKien() << "] (Nhap -1 de bo qua): ";
            getline(cin, temp);
            if (!temp.empty() && stoi(temp) != -1) {
                it->setThoiGianDuKien(stoi(temp));
            }
        }
        catch (...) {
            cout << "Gia tri thoi gian khong hop le\n";
        }

        ghiFile(); 
        cout << "-> Cap nhat thanh cong!\n";
    }

    // --- D: DELETE (Xoa) ---
    void xoa() 
    {
        string id;
        cout << "Nhap ma tuyen can xoa: ";
        getline(cin, id);

        auto it = find_if(danhSach.begin(), danhSach.end(), [&](const TuyenVanChuyen& x) {
            return x.getMaID() == id;
            });

        if (it == danhSach.end()) {
            cout << "Khong tim thay ma tuyen nay!\n";
            return;
        }

        cout << "\nThong tin ban ghi chuan bi xoa:\n";
        inTieuDeBang();
        it->xuat();

        char confirm;
        cout << "\nBan co chac chan muon xoa khong? (y/n): ";
        cin >> confirm;
        cin.ignore(10000, '\n');

        if (confirm == 'y' || confirm == 'Y') 
        {
            danhSach.erase(it);
            ghiFile(); // Cap nhat lai file
            cout << "-> Xoa thanh cong va da cap nhat file!\n";
        }
        else {
            cout << "Huy thao tac xoa.\n";
        }
    }

    // Menu dieu khien phan he
    void menu() {
        int choice = -1;
        do {
            xoaManHinh(); // Quay ve menu "sach" moi lan lap

            cout << "========== QUAN LY TUYEN VAN CHUYEN ==========\n";
            cout << "1. Them tuyen van chuyen moi (Create)\n";
            cout << "2. Xem danh sach tuyen van chuyen (Read)\n";
            cout << "3. Tim kiem tuyen theo ma (Read)\n";
            cout << "4. Cap nhat thong tin tuyen (Update)\n";
            cout << "5. Xoa tuyen van chuyen (Delete)\n";
            cout << "0. Quay lai menu chinh\n";
            cout << "==============================================\n";
            cout << "Lua chon cua ban: ";

            cin >> choice;
            if (cin.fail()) {          
                cin.clear();
                choice = -1;
            }
            cin.ignore(10000, '\n');

            if (choice == 0) {
                cout << "Thoat phan he...\n";
                break;
            }

            xoaManHinh(); 

            switch (choice) {
            case 1: themMoi(); break;
            case 2: xemDanhSach(); break;
            case 3: timKiem(); break;
            case 4: capNhat(); break;
            case 5: xoa(); break;
            default: cout << "Lua chon khong hop le! Vui long chon lai.\n";
            }

            tamDung(); 
        } while (choice != 0);
    }
};

#endif