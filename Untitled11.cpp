#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

//============= GIAO DIỆN CHƯƠNG TRÌNH ===============
int displayLength(const string& s) {
    int count = 0;
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char c = s[i];
        if ((c & 0xC0) != 0x80)  
            count++;
    }
    return count;
}

string padRight(const string& s, int width) {
    int len = displayLength(s);
    if (len >= width) return s;

    return s + string(width - len, ' ');
}


void setColor(int textColor, int bgColor = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}
// ================= CẤU TRÚC DỮ LIỆU =================
struct Sach {
    string maSach;
    string tenSach;
    string tacGia;
    string theLoai;
    Sach* next;
};
struct SinhVien {
    string MSSV;
    string hoTen;
    string lop;
    SinhVien* next;
};
struct PhieuMuon {
    int maPhieu;
    string MSSV;
    string maSach[10];
    int soLuong;
    string ngayMuon;
    bool daTra[10];
    PhieuMuon* next;
};

// ================= CLASS QUẢN LÝ SÁCH =================
class QuanLySach {
private:
    Sach* head;
public:
    QuanLySach();
    void themSach();
    void hienThiSach();
    void sapXepTheoTen();
    void timKiem();
    Sach* timSachTheoMa(string ma);
    Sach* timSachTheoTen(string& ten);
    void chinhSuaSach();
    void xoaSach();
};

// ================= CLASS QUẢN LÝ SINH VIÊN =================
class QuanLySinhVien {
private:
    SinhVien* head;
public:
    QuanLySinhVien();
    void themSinhVien();
    void hienThiSinhVien();
    void sapXepTheoMSSV();
    void timKiem();
    SinhVien* timSinhVienTheoMSSV(string mssv);
    SinhVien* timSinhVienTheoTen(const string& ten);
    void chinhSuaSinhVien();
    void xoaSinhVien();
};

// ================= CLASS QUẢN LÝ MƯỢN TRẢ =================
class QuanLyMuonTra {
private:
    PhieuMuon* head;
    QuanLySach* qls;
    QuanLySinhVien* qlsv;
public:
    QuanLyMuonTra(QuanLySach* s, QuanLySinhVien* sv);
    void lapPhieuMuon();
    void hienThiPhieuMuon();
    void trasach();
};

// =======================================================
// =============== HÀM CỦA QUẢN LÝ SÁCH ==================
// =======================================================

QuanLySach::QuanLySach() {
    head = NULL;
}

void QuanLySach::themSach() {
    Sach* s = new Sach;
    cout << "Nhap ma sach: "; cin >> s->maSach;
    cin.ignore();
    cout << "Nhap ten sach: "; getline(cin, s->tenSach);
    cout << "Nhap tac gia: "; getline(cin, s->tacGia);
    cout << "Nhap the loai: "; getline(cin, s->theLoai);
    s->next = NULL;

    if (head == NULL) head = s;
    else {
        Sach* p = head;
        while (p->next != NULL) p = p->next;
        p->next = s;
    }
    cout << "Da them sach thanh cong!\n";
}

void QuanLySach::hienThiSach() {
    if (head == NULL) {
        cout << "Danh sách sách rỗng!\n";
        return;
    }

    const int widthMaSach = 20;
    const int widthTenSach = 25;
    const int widthTacGia = 25;
    const int widthTheLoai = 20;

    Sach* p = head;
    setColor(9);
    cout << "\n======================================== DANH SÁCH SÁCH ========================================\n";
    cout << padRight("Mã sách", widthMaSach)
         << "| " << padRight("Tên sách", widthTenSach)
         << "| " << padRight("Tác giả", widthTacGia)
         << "| " << padRight("Thể loại", widthTheLoai)
         << "\n";
    cout << string(widthMaSach + widthTenSach + widthTacGia + widthTheLoai + 6, '-') << "\n";
    setColor(12);
    while (p != NULL) {
        cout << padRight(p->maSach, widthMaSach)
             << "| " << padRight(p->tenSach, widthTenSach)
             << "| " << padRight(p->tacGia, widthTacGia)
             << "| " << padRight(p->theLoai, widthTheLoai)
             << "\n";
        p = p->next;
    }
    setColor(9);
    cout << string(widthMaSach + widthTenSach + widthTacGia + widthTheLoai + 6, '-') << endl;
    setColor(7);
}

void QuanLySach::sapXepTheoTen() {
    if (head == NULL || head->next == NULL) return;

    for (Sach* i = head; i->next != NULL; i = i->next) {
        for (Sach* j = i->next; j != NULL; j = j->next) {
            if (i->tenSach > j->tenSach) {
                // Trao doi maSach
                string tmpMa = i->maSach;
                i->maSach = j->maSach;
                j->maSach = tmpMa;

                // Trao doi tenSach
                string tmpTen = i->tenSach;
                i->tenSach = j->tenSach;
                j->tenSach = tmpTen;

                // Trao doi tacGia
                string tmpTacGia = i->tacGia;
                i->tacGia = j->tacGia;
                j->tacGia = tmpTacGia;

                // Trao doi theLoai
                string tmpTheLoai = i->theLoai;
                i->theLoai = j->theLoai;
                j->theLoai = tmpTheLoai;
            }
        }
    }

    cout << "Da sap xep sach theo ten (tang dan)\n";
}


Sach* QuanLySach::timSachTheoMa(string ma) {
    Sach* p = head;
    while (p != NULL) {
        if (p->maSach == ma) return p;
        p = p->next;
    }
    return NULL;
}
Sach* QuanLySach::timSachTheoTen(string& ten) {
        Sach* p = head;
        while (p != NULL) {
            if (p->tenSach == ten)
                return p;
            p = p->next;
        }
        return NULL;
    }

void QuanLySach::timKiem() {
        if (head == NULL) {
            cout << "Danh sach rong!\n";
            return;
        }
        int lua;
        cout << "1. Tim theo ma sach\n2. Tim theo ten sach\nChon: ";
        cin >> lua;
        cin.ignore(); 
        if (lua == 1) {
            string ma;
            cout << "Nhap ma sach: ";
            cin >> ma;
            Sach* s = timSachTheoMa(ma);
            if (s)
                cout << "Tim thay sach: " << s->tenSach << " - Tac gia: " << s->tacGia << endl;
            else
                cout << "Khong tim thay!\n";
        } else if (lua == 2) {
            string ten;
            cout << "Nhap ten sach: ";
            getline(cin, ten);
            Sach* s = timSachTheoTen(ten);
            if (s)
                cout << "Tim thay sach ma " << s->maSach << " - Tac gia: " << s->tacGia << endl;
            else
                cout << "Khong tim thay!\n";
        } else {
            cout << "Lua chon khong hop le!\n";
        }
    }
    
void QuanLySach::chinhSuaSach() {
    if (head == NULL) {
        cout << "Danh sach sach rong!\n";
        return;
    }

    string ma;
    cout << "Nhap ma sach can chinh sua: ";
    cin >> ma;

    Sach* s = timSachTheoMa(ma);
    if (s == NULL) {
        cout << "Khong tim thay ma sach!\n";
        return;
    }
    cin.ignore();
    cout << "Nhap ten sach moi (de trong neu khong doi): ";
    string ten; getline(cin, ten);
    if (!ten.empty()) s->tenSach = ten;

    cout << "Nhap tac gia moi (de trong neu khong doi): ";
    string tg; getline(cin, tg);
    if (!tg.empty()) s->tacGia = tg;

    cout << "Nhap the loai moi (de trong neu khong doi): ";
    string tl; getline(cin, tl);
    if (!tl.empty()) s->theLoai = tl;

    cout << "Da cap nhat thong tin sach thanh cong!\n";
}

void QuanLySach::xoaSach() {
    if (head == NULL) {
        cout << "Danh sach sach rong!\n";
        return;
    }

    string ma;
    cout << "Nhap ma sach can xoa: ";
    cin >> ma;

    Sach* p = head;
    Sach* truoc = NULL;

    while (p != NULL && p->maSach != ma) {
        truoc = p;
        p = p->next;
    }

    if (p == NULL) {
        cout << "Khong tim thay ma sach!\n";
        return;
    }

    if (truoc == NULL) { 
        head = p->next;
    } else {
        truoc->next = p->next;
    }

    delete p;
    cout << "Da xoa sach thanh cong!\n";
}

// =======================================================
// ============ HÀM CỦA QUẢN LÝ SINH VIÊN ================
// =======================================================

QuanLySinhVien::QuanLySinhVien() {
    head = NULL;
}

void QuanLySinhVien::themSinhVien() {
    SinhVien* sv = new SinhVien;
    
    cout << "Nhap MSSV: "; cin >> sv->MSSV;
    cin.ignore();
    cout << "Nhap ho ten: "; getline(cin, sv->hoTen);
    cout << "Nhap lop: "; getline(cin, sv->lop);
    
    sv->next = NULL;
    if (head == NULL) head = sv;
    else {
        SinhVien* p = head;
        while (p->next != NULL) p = p->next;
        p->next = sv;
    }
    cout << "Da them sinh vien thanh cong!\n";
}

void QuanLySinhVien::hienThiSinhVien() {
    if (head == NULL) {
        cout << "Danh sach sinh vien rong!\n";
        return;
    }
    const int wMSSV = 15;
    const int wHoTen = 30;
    const int wLop = 15;
    
    SinhVien* p = head;
    setColor(9);
    cout << "\n=============== DANH SACH SINH VIEN ===============\n";

        cout << padRight("MSSV", 12)
             << padRight("HoTen", 25)
             << padRight("Lop", 15)
             << endl;
              cout << string(51, '=') << endl;
    setColor(12);
    while (p != NULL) {
        cout << padRight(p->MSSV, 12)
             << padRight(p->hoTen, 25)
             << padRight(p->lop, 15)
             << endl;

        p = p->next;
    }
     setColor(9);
    cout << "==================================================="<< endl;  
    setColor(7);
}

void QuanLySinhVien::sapXepTheoMSSV() {
    if (head == NULL || head->next == NULL) return;

    for (SinhVien* i = head; i->next != NULL; i = i->next) {
        for (SinhVien* j = i->next; j != NULL; j = j->next) {
            if (i->MSSV > j->MSSV) {
                // Trao doi MSSV
                string tmpMSSV = i->MSSV;
                i->MSSV = j->MSSV;
                j->MSSV = tmpMSSV;

                // Trao doi hoTen
                string tmpHoTen = i->hoTen;
                i->hoTen = j->hoTen;
                j->hoTen = tmpHoTen;

                // Trao doi lop
                string tmpLop = i->lop;
                i->lop = j->lop;
                j->lop = tmpLop;
            }
        }
    }

    cout << "Da sap xep sinh vien theo MSSV (tang dan)\n";
}


SinhVien* QuanLySinhVien::timSinhVienTheoMSSV(string mssv) {
    SinhVien* p = head;
    while (p != NULL) {
        if (p->MSSV == mssv) return p;
        p = p->next;
    }
    return NULL;
}

SinhVien* QuanLySinhVien::timSinhVienTheoTen(const string& ten) {
        SinhVien* p = head;
        while (p != NULL) {
            if (p->hoTen == ten)
                return p;
            p = p->next;
        }
        return NULL;
}

 void QuanLySinhVien::timKiem() {
        if (head == NULL) {
            cout << "Danh sach rong!\n";
            return;
        }

        int lua;
        cout << "1. Tim theo MSSV\n2. Tim theo ho ten\nChon: ";
        cin >> lua;
        cin.ignore();

        if (lua == 1) {
            string mssv;
            cout << "Nhap MSSV: ";
            cin >> mssv;
            SinhVien* s = timSinhVienTheoMSSV(mssv);
            if (s)
                cout << "Tim thay: " << s->hoTen << " - Lop: " << s->lop << endl;
            else
                cout << "Khong tim thay!\n";

        } else if (lua == 2) {
            string ten;
            cout << "Nhap ho ten: ";
            getline(cin, ten);
            SinhVien* s = timSinhVienTheoTen(ten);
            if (s)
                cout << "Tim thay: MSSV " << s->MSSV << " - Lop: " << s->lop << endl;
            else
                cout << "Khong tim thay!\n";
        } else {
            cout << "Lua chon khong hop le!\n";
        }
    }
    
void QuanLySinhVien::chinhSuaSinhVien() {
    if (head == NULL) {
        cout << "Danh sach sinh vien rong!\n";
        return;
    }

    string mssv;
    cout << "Nhap MSSV can chinh sua: ";
    cin >> mssv;

    SinhVien* sv = timSinhVienTheoMSSV(mssv);
    if (sv == NULL) {
        cout << "Khong tim thay sinh vien!\n";
        return;
    }

    cin.ignore();
    cout << "Nhap ho ten moi (de trong neu khong doi): ";
    string ten; getline(cin, ten);
    if (!ten.empty()) sv->hoTen = ten;

    cout << "Nhap lop moi (de trong neu khong doi): ";
    string lop; getline(cin, lop);
    if (!lop.empty()) sv->lop = lop;

    cout << "Da cap nhat thong tin sinh vien!\n";
}


void QuanLySinhVien::xoaSinhVien() {
    if (head == NULL) {
        cout << "Danh sach sinh vien rong!\n";
        return;
    }

    string mssv;
    cout << "Nhap MSSV can xoa: ";
    cin >> mssv;

    SinhVien* p = head;
    SinhVien* truoc = NULL;

    while (p != NULL && p->MSSV != mssv) {
        truoc = p;
        p = p->next;
    }

    if (p == NULL) {
        cout << "Khong tim thay sinh vien!\n";
        return;
    }

    if (truoc == NULL) {
        head = p->next;
    } else {
        truoc->next = p->next;
    }

    delete p;
    cout << "Da xoa sinh vien thanh cong!\n";
}

// =======================================================
// ============ HÀM CỦA QUẢN LÝ MƯỢN TRẢ ================
// =======================================================

QuanLyMuonTra::QuanLyMuonTra(QuanLySach* s, QuanLySinhVien* sv) {
    head = NULL;
    qls = s;
    qlsv = sv;
}

void QuanLyMuonTra::lapPhieuMuon() {
    PhieuMuon* pm = new PhieuMuon;

    cout << "Nhap ma phieu: ";
    cin >> pm->maPhieu;

    cout << "Nhap MSSV: ";
    cin >> pm->MSSV;

    if (qlsv->timSinhVienTheoMSSV(pm->MSSV) == NULL) {
        cout << "Khong tim thay MSSV!\n";
        delete pm;
        return;
    }

    cout << "Nhap so luong sach muon: ";
    cin >> pm->soLuong;

    if (pm->soLuong < 1 || pm->soLuong > 10) {
        cout << "So luong sach chi duoc trong khoang (1 - 10)!\n";
        delete pm;
        return;
    }

    for (int i = 0; i < pm->soLuong; i++) {
        cout << "Nhap ma sach " << i + 1 << ": ";
        cin >> pm->maSach[i];

        if (qls->timSachTheoMa(pm->maSach[i]) == NULL) {
            cout << "Ma sach " << pm->maSach[i] << " khong ton tai!\n";
            delete pm;
            return;
        }
    }

    cin.ignore();
    cout << "Nhap ngay muon: ";
    getline(cin, pm->ngayMuon);

   for (int i = 0; i < pm->soLuong; i++) {
    pm->daTra[i] = false;
    }

    pm->next = NULL;

    if (head == NULL) head = pm;
    else {
        PhieuMuon* p = head;
        while (p->next != NULL) p = p->next;
        p->next = pm;
    }

    cout << "Da lap phieu muon thanh cong!\n";
}




void QuanLyMuonTra::hienThiPhieuMuon() {
    if (head == NULL) {
        cout << "Chua co phieu muon!\n";
        return;
    }
    const int wMaPM = 10, wMSSV = 12, wTenSV = 25, wMaSach = 15, wTenSach = 25, wNgayMuon = 15, wTrangThai = 12;
    
    PhieuMuon* p = head;

    setColor(9);
    cout << "\n============================================ DANH SACH PHIEU MUON ============================================\n";

    cout << padRight("MaPM", 10)
         << padRight("MSSV", 12)
         << padRight("Ten SV", 25)
         << padRight("Ma Sach", 12)
         << padRight("Ten Sach", 25)
         << padRight("Ngay Muon", 15)
         << padRight("Trang Thai", 12)
         << endl;

    cout << "\n==============================================================================================================\n" << endl;

    while (p != NULL) {

        SinhVien* sv = qlsv->timSinhVienTheoMSSV(p->MSSV);

        setColor(12);

        for (int i = 0; i < p->soLuong; i++) {
            Sach* s = qls->timSachTheoMa(p->maSach[i]);

            if (i == 0) {
                cout << padRight(to_string(p->maPhieu), 10)
                     << padRight(p->MSSV, 12)
                     << padRight(sv ? sv->hoTen : "Khong co", 25);
            } else {
                cout << padRight("", 10)
                     << padRight("", 12)
                     << padRight("", 25);
            }

            cout << padRight(p->maSach[i], 12)
                 << padRight(s ? s->tenSach : "Khong co", 25);

            if (i == 0) {
                cout << padRight(p->ngayMuon, 15)
                     << padRight(p->daTra[i] ? "Da tra" : "Dang muon", 12);
            } else {
                cout << padRight("", 15)
                     << padRight("", 12);
            }

            cout << endl;
        }

        setColor(9);
        cout << "\n==========================================================================================================\n"<< endl;

        p = p->next;
    }

    cout << "\n===========================================================================================================\n"<< endl;
    setColor(7);
}



void QuanLyMuonTra::trasach() {
    if (head == NULL) {
        cout << "Chua co phieu muon!\n";
        return;
    }

    string mssv;
    string ma;
    cout << "Nhap MSSV: ";
    cin >> mssv;
    cout << "Nhap ma sach can tra: ";
    cin >> ma;

    PhieuMuon* p = head;
    while (p != NULL) {
        if (p->MSSV == mssv) {

            for (int i = 0; i < p->soLuong; i++) {
                if (p->maSach[i] == ma && p->daTra[i] == false) {

                    p->daTra[i] = true;
                    cout << "Da tra sach thanh cong!\n";
                    return;
                }
            }

        }
        p = p->next;
    }

    cout << "Khong tim thay phieu muon hoac sach da tra!\n";
}


// =======================================================
// ====================== MAIN ===========================
// =======================================================
int main() {
	
	SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    QuanLySach qls;
    QuanLySinhVien qlsv;
    QuanLyMuonTra qlmt(&qls, &qlsv);

    int chon = -1;

    while (chon != 0) {
        system("cls");
        setColor(9);
        cout << "=====================================================\n";
        cout << "                QUAN LY THU VIEN                     \n";
        cout << "=====================================================\n";
        setColor(12);
        cout << "1. Quan ly sach\n";
        cout << "2. Quan ly sinh vien\n";
        cout << "3. Quan ly muon tra\n";
        cout << "0. Thoat chuong trinh\n";
        setColor(9);
        cout << "=====================================================\n";
        setColor(14);
        cout << "Nhap lua chon: ";
        cin >> chon;
        setColor(7);
        // ===================== QUẢN LÝ SÁCH =====================
        if (chon == 1) {
            int c1 = -1;
            while (c1 != 0) {
                system("cls");
                setColor(9);
                cout << "=================== QUAN LY SACH ===================\n";
                setColor(12);
                cout << "1. Them sach\n";
                cout << "2. Hien thi danh sach sach\n";
                cout << "3. Sắp xếp sách theo tên\n";
                cout << "4. Tim kiem sach\n";
                cout << "5. Chinh sua thong tin sach\n";
                cout << "6. Xoa sach\n";
                cout << "0. Quay lai menu chinh\n";
                setColor(9);
                cout << "====================================================\n";
                setColor(14);
                cout << "Nhap lua chon: ";
                cin >> c1;
                setColor(7);
  
                if (c1 == 1) qls.themSach();
                else if (c1 == 2) qls.hienThiSach();
                else if (c1 == 3) qls.sapXepTheoTen();
                else if (c1 == 4) qls.timKiem();
                else if (c1 == 5) qls.chinhSuaSach();
                else if (c1 == 6) qls.xoaSach();
                else if (c1 == 0) { /* quay lại */ }
                else cout << "Lua chon khong hop le!\n";
                if(c1!=0) system("pause");
              
            }
        }

        // ===================== QUẢN LÝ SINH VIÊN =====================
        else if (chon == 2) {
            int c2 = -1;
            while (c2 != 0) {
                system("cls");
                setColor(9);
                cout << "================ QUAN LY SINH VIEN ================\n";
                setColor(12);
                cout << "1. Them sinh vien\n";
                cout << "2. Hien thi danh sach sinh vien\n";
                cout << "3. Sap xep sinh vien theo MSSV\n";
                cout << "4. Tim kiem sinh vien\n";
                cout << "5. Chinh sua thong tin sinh vien\n";
                cout << "6. Xoa sinh vien\n";
                cout << "0. Quay lai menu chinh\n";
                setColor(9);
                cout << "===================================================\n";
                setColor(14);
                cout << "Nhap lua chon: ";
                cin >> c2;
                setColor(7);

                if (c2 == 1) qlsv.themSinhVien();
                else if (c2 == 2) qlsv.hienThiSinhVien();
                else if (c2 == 3) qlsv.sapXepTheoMSSV();
                else if (c2 == 4) qlsv.timKiem();
                else if (c2 == 5) qlsv.chinhSuaSinhVien();
                else if (c2 == 6) qlsv.xoaSinhVien();
                else if (c2 == 0) { /* quay lại */ }
                else cout << "Lua chon khong hop le!\n";
                 if(c2!=0) system("pause");
            }
        }

        // ===================== QUẢN LÝ MƯỢN TRẢ =====================
        else if (chon == 3) {
            int c3 = -1;
            while (c3 != 0) {
                system("cls");
                setColor(9);
                cout << "================ QUAN LY MUON TRA ================\n";
                setColor(12);
                cout << "1. Lap phieu muon sach\n";
                cout << "2. Hien thi danh sach phieu muon\n";
                cout << "3. Tra sach\n";
                cout << "0. Quay lai menu chinh\n";
                setColor(9);
                cout << "==================================================\n";
                cout << "Nhap lua chon: ";
                cin >> c3;
                setColor(14);

                if (c3 == 1) qlmt.lapPhieuMuon();
                else if (c3 == 2) qlmt.hienThiPhieuMuon();
                else if (c3 == 3) qlmt.trasach();
                else if (c3 == 0) { /* quay lại */ }
                else cout << "Lua chon khong hop le!\n";
                  if(c3!=0) system("pause");
            }
        }

        else if (chon == 0) {
            cout << "\nTam biet! Ket thuc chuong trinh.\n";
        }

        else {
            cout << "Lua chon khong hop le, vui long nhap lai!\n";
            system("pause");
        }
    }

    return 0;
}