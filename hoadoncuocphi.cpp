#include <iostream>
#include "Repository.h"
#include "BuuCuc.h"
#include "PhieuGui.h"
#include "HoaDonCuoc.h"
#include "TuyenVanChuyen.h"

using namespace std;

void xoaManHinh() { system("cls"); }

int main() {
    // 1. Khoi tao co so du lieu (Repositories)
    Repository<BuuCuc> repoBC("data/buu_cuc.txt");
    Repository<PhieuGui> repoPG("data/phieu_gui.txt");
    Repository<HoaDonCuoc> repoHD("data/hoa_don.txt");
    Repository<TuyenVanChuyen> repoTVC("data/tuyen_van_chuyen.txt");

    // 2. Khoi tao Giao dien va cap quyen truy cap Data
    BuuCucMenu menuBC(repoBC);
    PhieuGuiMenu menuPG(repoPG, repoBC);
    HoaDonCuocMenu menuHD(repoHD, repoPG);
    TuyenVanChuyenMenu menuTVC(repoTVC, repoBC);

    // 3. Vong lap chuong trinh chinh
    int choice = -1;
    do {
        xoaManHinh();
        cout << "============= MENU CHINH =============\n";
        cout << "1. Quan ly Buu Cuc\n";
        cout << "2. Quan ly Phieu Gui\n";
        cout << "3. Quan ly Hoa Don Cuoc Phi\n";
        cout << "4. Quan ly Tuyen Van Chuyen\n";
        cout << "0. Thoat\n";
        cout << "======================================\n";
        cout << "Chon: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1: menuBC.menu(); break;
        case 2: menuPG.menu(); break;
        case 3: menuHD.menu(); break;
        case 4: menuTVC.menu(); break;
        case 0: cout << "Thoat chuong trinh...\n"; break;
        default: cout << "Loi lua chon!\n";
        }
    } while (choice != 0);

    return 0;
}
