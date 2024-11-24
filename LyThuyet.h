#pragma once
#include "PhongHoc.h"

class LyThuyet : public PhongHoc {
private:
	unsigned int soBan;
	unsigned int sucChua;
public:
	LyThuyet() : PhongHoc(), soBan(0), sucChua(0) {}
	LyThuyet(unsigned int soBan, unsigned int sucChua , char toaNha, unsigned short soTang, unsigned int stt) : PhongHoc(toaNha,soTang,stt), soBan(soBan), sucChua(sucChua) {}
	~LyThuyet() = default;
	// nhap xuat
	void nhap() {
		PhongHoc::nhap();
		cout << "\nNhap so Ban hoc: ";
		cin >> soBan;
		sucChua = soBan * 3;
	}
	void xuat() const {
		PhongHoc::xuat();
		cout << "So Ban hoc: " << soBan << rows2;
		cout << "Suc Chua: " << sucChua << rows2;
	}
	// getter setter
	void setsoBan(unsigned int soBan) { this->soBan = soBan; }
	unsigned int getsoBan() const { return soBan; }

	unsigned int getSucChua() const {
		return sucChua;
	}
	void setSucChua(unsigned int sucChua) { this->sucChua = sucChua; }
};


