#include "TruongHoc.h"
#include<iostream>

int main() {
	TruongHoc truongHoc;
	truongHoc.nhap();
	truongHoc.xuat();
	cout << "So Luong Phong Thuc Hanh: " << truongHoc.demSoLuongPhongTH() << rows2;
	cout << "So Luong Phong Thuc Hanh Nha F: " << truongHoc.demSoLuongPhongTHTheoToaNha('F') << rows2;
	cout << "Tong Suc Chua cua Tang 7 Nha F: " << truongHoc.tongSucChuaTheoTangandToaNha(7, 'F') << rows2;
	cout << "Suc Chua Trung Binh cua Phong Ly Thuyet Trong Truong Hoc: " << truongHoc.sucChuaTrungBinhPhonglyThuyet() << rows2;
	unsigned int SLNew;
	bool kiemTra = truongHoc.coPhongTHLonHonPhongLTKhong();
	if (kiemTra) cout << "Co Phong Thuc Hanh co Suc Chua Lon Hon Phong Ly Thuyet" << rows2;
	else cout<< "Khong co Phong Thuc Hanh nao co Suc Chua Lon Hon Phong Ly Thuyet" << rows2;
	// luyen tiep code
	unsigned int sucChuaChoTruoc;
	cout << "\nNhap suc Chua de kiem tra: "; cin >> sucChuaChoTruoc;
	PhongHoc** phongTimDuoc = truongHoc.checkAndSort(sucChuaChoTruoc, SLNew);
	if (phongTimDuoc != nullptr) {
		cout << "\nSo luong phong sau khi sap xep: " << SLNew << endl;
		for (unsigned int i = 0; i < SLNew; ++i) { 
			phongTimDuoc[i]->xuat(); 
			cout << "---------------" << rows2;
		}
		delete[] phongTimDuoc;
	}
	else {
		cout << "\nKhong tim thay phong nao co suc chua = " << sucChuaChoTruoc << rows2;
	}
	cout << "\nSo Luong Phong Ly Thuyet: " << truongHoc.demSoLuongPhongLT() << rows2;
	cout << "\nSo Luong Phong Thuc Hanh: " << truongHoc.demSoLuongPhongTH() << rows2;
	unsigned short soTangChoTruoc;
	cout << "\nNhap so Tang de tim kiem: "; cin >> soTangChoTruoc;
	PhongHoc** phongBangSoTangChoTruoc = truongHoc.danhsachCacPhongBangSoTangChoTruoc(soTangChoTruoc, SLNew);
	if (phongBangSoTangChoTruoc != nullptr) {
		cout << "\nSo luong Phong co cung so tang cho truoc: " << SLNew << rows2;
		for (unsigned int i = 0; i < SLNew; ++i) {
			phongBangSoTangChoTruoc[i]->xuat();
			cout << "---------------" << rows2;
		}
		delete[] phongBangSoTangChoTruoc;
	}
	else {
		cout << "\nKhong tim thay phong nao co cung so tang cho truoc!" << rows2;
	}
	// lý thuyết
	PhongHoc** listLTSCMax = truongHoc.phongLyThuyetCoSucChuaLonNhat(SLNew);
	if (listLTSCMax != nullptr) {
		cout << "Phong Ly Thuyet co Suc Chua Lon Nhat: " << rows2;
		for (unsigned int i = 0; i < SLNew; ++i) {
			listLTSCMax[i]->xuat();
			cout << "---------------" << rows2;
		}
		delete[] listLTSCMax;
	}
	else {
		cout << "Khong co Phong Ly Thuyet nao trong Truong Hoc!" << rows2;
	}
	// thực hành
	PhongHoc** listTHSCMax = truongHoc.phongThucHanhCoSucChuaLonNhat(SLNew);
	if (listTHSCMax != nullptr) {
		cout << "Phong Thuc hanh co Suc Chua Lon Nhat: " << rows2;
		for (unsigned int i = 0; i < SLNew; ++i) {
			listTHSCMax[i]->xuat();
			cout << "---------------" << rows2;
		}
		delete[] listTHSCMax;
	}
	else {
		cout << "Khong co Phong Thuc Hanh nao trong Truong Hoc!" << rows2;
	}
	//Xóa phòng khỏi danh sách dsPhong dựa trên thuộc tính(ví dụ : tên phòng hoặc tầng).
	unsigned short tangChoTruoc;
	cout << "\nNhap tang cho truoc de xoa: ";
	cin >> tangChoTruoc;
	truongHoc.xoaPhongTheoTangPhong(tangChoTruoc);
	cout << "\nSau khi xoa: " << rows2;
	truongHoc.xuat();
	char toaNhaChoTruoc;
	unsigned int sucChuaCanUpdate;
	cout << "\nNhap tang cho truoc: "; cin >> tangChoTruoc;
	cout << "\nNhap toa Nha cho truoc: "; cin >> toaNhaChoTruoc;
	cin.ignore();
	cout << "\nNhap sucChua cna update: "; cin >> sucChuaCanUpdate;
	truongHoc.updateSucChua(tangChoTruoc, toaNhaChoTruoc, sucChuaCanUpdate);
	truongHoc.xuat();
	cout << "\nNhap toa nha cho truoc de dem so luong phong: "; cin >> toaNhaChoTruoc;
	cout << "\nSo luong phong trong toa nha " << toaNhaChoTruoc << " : " << truongHoc.demSoPhongTheoToaNha(toaNhaChoTruoc);
	cout << "\nNhap toa nha cho truoc de tinh tong suc chua: "; cin >> toaNhaChoTruoc;
	cout << "\nTong suc chua trong toa nha: " << toaNhaChoTruoc << " : " << truongHoc.tongSucChuaTheoToaNha(toaNhaChoTruoc);
	// Báo cáo chi tiết của trường cao thắng
	truongHoc.baoCaoChiTiet();
	float giaTri;
	cout << "\nNhap gia tri de so sanh: "; cin >> giaTri;
	PhongHoc** listPhongSucChuaLonHonGTChoTruoc = truongHoc.timPhongCoSucChuaLonHonGiaTriChoTuocAndSort(giaTri, SLNew);
	if (listPhongSucChuaLonHonGTChoTruoc != nullptr) {
		cout << "\nSo luong phong hoc co suc chua lon hon " << giaTri << " la: " << SLNew << rows2;
		for (unsigned int i = 0; i < SLNew; ++i) {
			listPhongSucChuaLonHonGTChoTruoc[i]->xuat();
			cout << "---------------" << rows2;
		}
		delete[] listPhongSucChuaLonHonGTChoTruoc;
	}
	else {
		cout << "\nKhong tim thay phong nao co suc chua lon hon " << giaTri << " hoac khong co phong nao trong Truong hoc!";
	}
	PhongHoc** listCopy = truongHoc.copyPhongHoc(truongHoc);
	if (listCopy != nullptr) {
		cout << "\nTat ca phong hoc sau khi duoc copy : " << rows2;
		for (unsigned int i = 0; i < truongHoc.getSoLuong(); ++i) {
			if (listCopy[i] != nullptr) {
				listCopy[i]->xuat();
				cout << "---------------" << rows2;
			}
		}
		for (unsigned int i = 0; i < truongHoc.getSoLuong(); ++i) {
			if (listCopy[i] != nullptr)
				delete listCopy[i];
		}
		delete[] listCopy;
	}
	else {
		cout << "\nKhong co phong nao de copy!" << rows2;
	}

	return 0;
}