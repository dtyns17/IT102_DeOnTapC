#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ma[11];
    char ten[41];
    char dvt[11];
    double donGia;
    int soLuong;
} SanPham;

typedef struct {
    char ma[11];
    char ten[41];
    double donGia;
    int soLuong;
    double thanhTien;
} DongHoaDon;

void nhapChuoi(char s[], int size) {
    char buf[256];

    while (1) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            exit(0);
        buf[strcspn(buf, "\n")] = '\0';
        if ((int)strlen(buf) < size)
            break;
        printf("Toi da %d ky tu, nhap lai: ", size - 1);
    }
    strcpy(s, buf);
}

int nhapSoNguyen() {
    char buf[100], thua;
    int x;

    while (1) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%d %c", &x, &thua) == 1)
            return x;
        printf("Gia tri khong hop le, nhap lai: ");
    }
}

double nhapSoThuc() {
    char buf[100], thua;
    double x;

    while (1) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%lf %c", &x, &thua) == 1)
            return x;
        printf("Gia tri khong hop le, nhap lai: ");
    }
}

int timViTri(SanPham ds[], int n, char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].ma, ma) == 0)
            return i;
    }
    return -1;
}

void inTieuDe() {
    printf("%-4s %-10s %-40s %-10s %12s %6s %14s\n",
           "STT", "Ma", "Ten", "DVT", "Don gia", "SL", "Gia tri ton");
}

void inSanPham(int stt, SanPham sp) {
    printf("%-4d %-10s %-40s %-10s %12.0f %6d %14.0f\n",
           stt, sp.ma, sp.ten, sp.dvt, sp.donGia, sp.soLuong,
           sp.donGia * sp.soLuong);
}

int themSanPham(SanPham ds[], int n) {
    SanPham sp;

    if (n == 100) {
        printf("Danh sach da day.\n");
        return n;
    }
    printf("Ma san pham: ");
    nhapChuoi(sp.ma, 11);
    if (strlen(sp.ma) == 0) {
        printf("Ma khong duoc rong.\n");
        return n;
    }
    if (strcmp(sp.ma, "0") == 0) {
        printf("Ma 0 dung de ket thuc khi ban hang, khong the dung lam ma san pham.\n");
        return n;
    }
    if (timViTri(ds, n, sp.ma) != -1) {
        printf("Ma da ton tai.\n");
        return n;
    }
    printf("Ten san pham: ");
    nhapChuoi(sp.ten, 41);
    printf("Don vi tinh: ");
    nhapChuoi(sp.dvt, 11);
    do {
        printf("Don gia: ");
        sp.donGia = nhapSoThuc();
        if (sp.donGia <= 0)
            printf("Don gia phai lon hon 0, nhap lai.\n");
    } while (sp.donGia <= 0);
    do {
        printf("So luong ton: ");
        sp.soLuong = nhapSoNguyen();
        if (sp.soLuong < 0)
            printf("So luong khong duoc am, nhap lai.\n");
    } while (sp.soLuong < 0);

    ds[n] = sp;
    printf("Da them san pham.\n");
    return n + 1;
}

void hienThi(SanPham ds[], int n) {
    inTieuDe();
    for (int i = 0; i < n; i++)
        inSanPham(i + 1, ds[i]);
}

void timTheoMa(SanPham ds[], int n) {
    char ma[11];

    printf("Nhap ma can tim: ");
    nhapChuoi(ma, 11);
    int vt = timViTri(ds, n, ma);
    if (vt == -1) {
        printf("Khong tim thay\n");
        return;
    }
    inTieuDe();
    inSanPham(vt + 1, ds[vt]);
}

void capNhat(SanPham ds[], int n) {
    char ma[11];
    double giaMoi;
    int nhapThem;

    printf("Nhap ma san pham: ");
    nhapChuoi(ma, 11);
    int vt = timViTri(ds, n, ma);
    if (vt == -1) {
        printf("Khong tim thay\n");
        return;
    }
    do {
        printf("Don gia moi: ");
        giaMoi = nhapSoThuc();
        if (giaMoi <= 0)
            printf("Don gia phai lon hon 0, nhap lai.\n");
    } while (giaMoi <= 0);
    do {
        printf("So luong nhap them: ");
        nhapThem = nhapSoNguyen();
        if (nhapThem < 0)
            printf("So luong khong duoc am, nhap lai.\n");
    } while (nhapThem < 0);

    ds[vt].donGia = giaMoi;
    ds[vt].soLuong += nhapThem;
    printf("Da cap nhat.\n");
}

int xoaSanPham(SanPham ds[], int n) {
    char ma[11];

    printf("Nhap ma san pham can xoa: ");
    nhapChuoi(ma, 11);
    int vt = timViTri(ds, n, ma);
    if (vt == -1) {
        printf("Khong tim thay\n");
        return n;
    }
    for (int i = vt; i < n - 1; i++)
        ds[i] = ds[i + 1];
    printf("Da xoa san pham.\n");
    return n - 1;
}

double banHang(SanPham ds[], int n) {
    DongHoaDon hd[20];
    int soDong = 0;
    double tongTien = 0, giamGia = 0;
    char ma[11];
    int sl;

    while (soDong < 20) {
        printf("Nhap ma san pham (0 de ket thuc): ");
        nhapChuoi(ma, 11);
        if (strcmp(ma, "0") == 0)
            break;
        int vt = timViTri(ds, n, ma);
        if (vt == -1) {
            printf("Khong co ma san pham nay.\n");
            continue;
        }
        if (ds[vt].soLuong == 0) {
            printf("San pham da het hang.\n");
            continue;
        }
        printf("So luong mua: ");
        sl = nhapSoNguyen();
        if (sl <= 0) {
            printf("So luong khong hop le.\n");
            continue;
        }
        if (sl > ds[vt].soLuong) {
            printf("Khong du hang, chi con %d.\n", ds[vt].soLuong);
            continue;
        }

        ds[vt].soLuong -= sl;
        strcpy(hd[soDong].ma, ds[vt].ma);
        strcpy(hd[soDong].ten, ds[vt].ten);
        hd[soDong].donGia = ds[vt].donGia;
        hd[soDong].soLuong = sl;
        hd[soDong].thanhTien = ds[vt].donGia * sl;
        tongTien += hd[soDong].thanhTien;
        soDong++;
    }

    if (soDong == 20)
        printf("Hoa don da du 20 dong, tu dong ket thuc.\n");
    if (soDong == 0) {
        printf("Khong co mat hang nao duoc ban.\n");
        return 0;
    }
    if (tongTien >= 500000)
        giamGia = tongTien * 0.1;

    printf("\n========== HOA DON ==========\n");
    printf("%-4s %-10s %-40s %12s %6s %14s\n",
           "STT", "Ma", "Ten", "Don gia", "SL", "Thanh tien");
    for (int i = 0; i < soDong; i++) {
        printf("%-4d %-10s %-40s %12.0f %6d %14.0f\n",
               i + 1, hd[i].ma, hd[i].ten, hd[i].donGia,
               hd[i].soLuong, hd[i].thanhTien);
    }
    printf("Tong tien hang: %.0f\n", tongTien);
    printf("Giam gia      : %.0f\n", giamGia);
    printf("Khach phai tra: %.0f\n", tongTien - giamGia);
    return tongTien - giamGia;
}

void sapHetHang(SanPham ds[], int n) {
    int dem = 0;

    for (int i = 0; i < n; i++) {
        if (ds[i].soLuong < 5) {
            if (dem == 0)
                inTieuDe();
            inSanPham(i + 1, ds[i]);
            dem++;
        }
    }
    if (dem == 0)
        printf("Khong co san pham nao sap het hang.\n");
}

void sapXep(SanPham ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (ds[j].donGia > ds[j + 1].donGia) {
                SanPham tam = ds[j];
                ds[j] = ds[j + 1];
                ds[j + 1] = tam;
            }
        }
    }
    hienThi(ds, n);
}

void thongKe(SanPham ds[], int n, int soHoaDon, double doanhThu) {
    double tongTon = 0;
    int max = 0;

    for (int i = 0; i < n; i++) {
        tongTon += ds[i].donGia * ds[i].soLuong;
        if (ds[i].donGia > ds[max].donGia)
            max = i;
    }
    printf("So mat hang: %d\n", n);
    printf("Tong gia tri ton kho: %.0f\n", tongTon);
    printf("San pham co don gia cao nhat:\n");
    inTieuDe();
    inSanPham(max + 1, ds[max]);
    printf("So hoa don da ban: %d\n", soHoaDon);
    printf("Tong doanh thu: %.0f\n", doanhThu);
}

int main() {
    SanPham ds[100];
    int n = 0;
    int soHoaDon = 0;
    double doanhThu = 0, tien;
    int choice;

    do {
        printf("\n====== QUAN LY CUA HANG ======\n");
        printf("1. Them san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Tim san pham theo ma\n");
        printf("4. Cap nhat gia / nhap them hang\n");
        printf("5. Xoa san pham\n");
        printf("6. Ban hang va in hoa don\n");
        printf("7. Danh sach san pham sap het hang\n");
        printf("8. Sap xep theo don gia tang dan\n");
        printf("9. Thong ke\n");
        printf("0. Thoat\n");
        printf("==============================\n");
        printf("Chon: ");
        choice = nhapSoNguyen();

        if (choice >= 2 && choice <= 9 && n == 0) {
            printf("Chua co san pham nao, hay them san pham truoc.\n");
            continue;
        }

        switch (choice) {
            case 1:
                n = themSanPham(ds, n);
                break;
            case 2:
                hienThi(ds, n);
                break;
            case 3:
                timTheoMa(ds, n);
                break;
            case 4:
                capNhat(ds, n);
                break;
            case 5:
                n = xoaSanPham(ds, n);
                break;
            case 6:
                tien = banHang(ds, n);
                if (tien > 0) {
                    soHoaDon++;
                    doanhThu += tien;
                }
                break;
            case 7:
                sapHetHang(ds, n);
                break;
            case 8:
                sapXep(ds, n);
                break;
            case 9:
                thongKe(ds, n, soHoaDon, doanhThu);
                break;
            case 0:
                printf("Da thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);

    return 0;
}