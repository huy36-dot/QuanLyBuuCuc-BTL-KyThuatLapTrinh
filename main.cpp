#include <iostream>
#include "Repository.h"
#include "BuuCuc.h"
#include "PhieuGui.h"
#include "BuuPham.h"
#include "LoaiDichVu.h"

using namespace std;

void xoaManHinh() { system("cls"); }

int main() {
    // 1. Khoi tao co so du lieu (Repositories)
    Repository<BuuCuc> repoBC("data/buu_cuc.txt");
    Repository<PhieuGui> repoPG("data/phieu_gui.txt");
    Repository<BuuPham> repoBP("data/buu_pham.txt");
    Repository<LoaiDichVu> repoLDV("data/loai_dich_vu.txt");

    // 2. Khoi tao Giao dien va lien ket du lieu
    BuuCucMenu menuBC(repoBC);
    PhieuGuiMenu menuPG(repoPG, repoBC);
    BuuPhamMenu menuBP(repoBP, repoBC);
    LoaiDichVuMenu menuLDV(repoLDV);

    // 3. Vong lap menu chinh
    int choice = -1;
    do {
        xoaManHinh();
        cout << "=================== MENU CHINH QUAN LY BUU CUC ===================\n";
        cout << "1. Quan ly Buu Cuc\n";
        cout << "2. Quan ly Phieu Gui\n";
        cout << "3. Quan ly Buu Pham\n";
        cout << "4. Quan ly Loai Dich Vu\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "=================================================================\n";
        cout << "Chon chuc nang: ";

        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; continue; }

        switch (choice) {
        case 1: menuBC.menu(); break;
        case 2: menuPG.menu(); break;
        case 3: menuBP.menu(); break;
        case 4: menuLDV.menu(); break;
        case 0: cout << "Dang thoat chuong trinh...\n"; break;
        default: cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (choice != 0);

    return 0;
}