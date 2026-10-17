#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <memory> // Thu vien de dung Smart Pointer (unique_ptr)
#include <cstdlib>

#include "Repository.h"
#include "BuuCuc.h"
#include "PhieuGui.h"
// #include "TuyenVanChuyen.h"
// #include "KhachHangGui.h"
// ... (Cac file cua thanh vien khac)

using namespace std;

class Application {
private:
    // 1. KHAI BAO TAT CA REPOSITORY O DAY
    Repository<BuuCuc> repoBC;
    Repository<PhieuGui> repoPG;
    // Repository<TuyenVanChuyen> repoTuyen;
    // Repository<KhachHangGui> repoKH;

    // 2. DUNG SMART POINTER DE QUAN LY MENU (An diem cong tuyet doi)
    unique_ptr<BuuCucMenu> menuBC;
    unique_ptr<PhieuGuiMenu> menuPG;
    // unique_ptr<TuyenVanChuyenMenu> menuTuyen;

    void xoaManHinh() const { system("cls"); }

public:
    // CONSTRUCTOR: Noi lap rap va the hien cac rang buoc chéo
    Application()
        : repoBC("data/buu_cuc.txt"),
        repoPG("data/phieu_gui.txt")
    {
        // a. Viet cac ham Lambda kiem tra rang buoc tai day
        auto kiemTraBC_trong_PG = [&](string maBC) {
            auto list = repoPG.getAll();
            for (const auto& pg : list) {
                if (pg.getMaBuuCucGui() == maBC) 
                    return true;
            }
            return false;
            };

        // b. Khoi tao cac Menu va bom (inject) cac Repository / Lambda vao
        menuBC = make_unique<BuuCucMenu>(repoBC, kiemTraBC_trong_PG);
        menuPG = make_unique<PhieuGuiMenu>(repoPG, repoBC);
    }

    // HAM CHAY MENU CHINH
    void run() {
        int choice = -1;
        do {
            xoaManHinh();
            cout << "================ HE THONG QUAN LY BUU CUC ================\n";
            cout << "1. Quan ly Buu Cuc\n";
            cout << "2. Quan ly Phieu Gui\n";
            cout << "3. Quan ly Buu Pham\n";
            cout << "4. Quan ly Loai Dich Vu\n";
            cout << "5. Quan ly Phieu Khieu Nai\n";
            cout << "6. Quan ly Khach Hang Gui\n";
            cout << "7. Quan ly Buu Ta\n";
            cout << "8. Quan ly Ban Ghi Hanh Trinh\n";
            cout << "9. Quan ly Cuoc Phi - Hoa Don\n";
            cout << "10. Quan ly Tuyen Van Chuyen\n";
            cout << "0. Thoat chuong trinh\n";
            cout << "==========================================================\n";
            cout << "Nhap lua chon phan he (0-10): ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n'); 
                choice = -1; 
                continue;
            }

            switch (choice) {
            case 1: 
                menuBC->menu(); 
                break; 
            case 2: 
                menuPG->menu();
                break;
            case 0:
                cout << "Dang thoat chuong trinh va sao luu du lieu...\n";
                break;
            default: cout << "Lua chon khong hop le! Vui long chon lai.\n";
            }
        } while (choice != 0);
    }
};

#endif
