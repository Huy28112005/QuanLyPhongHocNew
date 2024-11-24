#pragma once
#include<iostream>
#include<iomanip>
using namespace std;
#define endl "\n"
#define rows2 "\n\n"

class PhongHoc
{
protected:
	char toaNha;
	unsigned short soTang;
	unsigned int stt;
public:
	PhongHoc() : toaNha(' '), soTang(0), stt(0) {}
	PhongHoc(char toaNha, unsigned short soTang, unsigned int stt) 
		: toaNha(toaNha), soTang(soTang), stt(stt) {}
	~PhongHoc() = default;
	// setter getter
	void setToaNha(char toaNha) { this->toaNha = toaNha; }
	char getToaNha() const { return toaNha; }

	void setSoTang(unsigned short soTang) { this->soTang = soTang; }
	unsigned short getSoTang() const { return soTang; }

	void setSTT(unsigned int stt) { this->stt = stt; }
	unsigned int getSTT() const { return stt; }
	// nhap xuat
	virtual void nhap() {
		cout << "\nNhap toa Nha: "; cin >> toaNha;
		cin.ignore();
		cout << "\nNhap so Tang: "; cin >> soTang;
		cout << "\nNhap STT: "; cin >> stt;
	}
	virtual void xuat() const {
		cout << "\nToa Nha: " << toaNha << rows2;
		cout << "So Tang: " << soTang << rows2;
		cout << "STT: " << stt << rows2;
	}
	virtual unsigned int getSucChua() const {
		return 0;
	}
	virtual void setSucChua(unsigned int sucChua) { return; }
};
