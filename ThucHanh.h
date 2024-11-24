#pragma once
#include "PhongHoc.h"

class ThucHanh : public PhongHoc {
private:
	unsigned int soMayTinh;
	unsigned int sucChua;
public:
	ThucHanh() : PhongHoc(), soMayTinh(0), sucChua(0) {}
	ThucHanh(unsigned int soMayTinh, unsigned int sucChua , char toaNha, unsigned short soTang, unsigned int stt) : PhongHoc(toaNha, soTang, stt), soMayTinh(soMayTinh), sucChua(sucChua) {}
	~ThucHanh() = default;
	// nhap xuat
	void nhap() {
		PhongHoc::nhap();
		cout << "\nNhap so May Tinh: ";
		cin >> soMayTinh;
		sucChua = soMayTinh;
	}
	void xuat() const {
		PhongHoc::xuat();
		cout << "So May Tinh: " << soMayTinh << rows2;
		cout << "Suc Chua: " << sucChua << rows2;
	}
	void setSoMayTinh(unsigned int soMayTinh) { this->soMayTinh = soMayTinh; }
	unsigned int getSoMayTinh() const { return soMayTinh; }
	// suc chua
	unsigned int getSucChua() const {
		return sucChua;
	}
	void setSucChua(unsigned int sucChua) { this->sucChua = sucChua; }
};


