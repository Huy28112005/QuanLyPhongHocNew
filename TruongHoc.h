#pragma once
#include <vector>
#include "PhongHoc.h"
#include "LyThuyet.h"
#include "ThucHanh.h"
#include <cctype>
#include <string>
#include <algorithm>
#define lt dynamic_cast<LyThuyet*>(dsPhong[i])
#define th dynamic_cast<ThucHanh*>(dsPhong[i])

class TruongHoc
{
private:
	unsigned int soLuong;
	PhongHoc** dsPhong;
	// hàm max kiểu unsigned int do người dùng tạo
	unsigned int MaxUNI(unsigned int a, unsigned int b) const {
		return (a > b) ? a : b;
	}
	// Hàm tiện ích để chuyển đổi chuỗi sang chữ thường
	string toLower(const string& str) {
		string lowerStr = str;
		transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
			[](unsigned char c) { return tolower(c); });
		return lowerStr;
	}
public:
	TruongHoc() : soLuong(0), dsPhong(nullptr) {}
	TruongHoc(unsigned int sl, PhongHoc** phong) : soLuong(sl) {
		dsPhong = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i)
			dsPhong[i] = phong[i];
	}
	~TruongHoc() {
		for (unsigned int i = 0; i < soLuong; ++i)
			delete dsPhong[i];
		delete[] dsPhong;
	}
	// getter setter
	void setSoLuong(unsigned int sl) { soLuong = sl; }
	unsigned int getSoLuong() const { return soLuong; }

	void setDSPhong(PhongHoc** phong, unsigned int sl) {
		if (dsPhong != nullptr) {
			for (unsigned int i = 0; i < soLuong; ++i)
				delete dsPhong[i];
			delete[] dsPhong;
			return;
		}
		soLuong = sl;
		dsPhong = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i)
			dsPhong[i] = phong[i];
	}
	PhongHoc** getDSPhong() const { return dsPhong; }
	// nhap xuat
	void nhap() {
		cout << "\nNhap so Luong: "; cin >> soLuong; cin.ignore();
		if (soLuong == 0) {
			cout << "\nSo luong = 0! End";
			return;
		}
		dsPhong = new PhongHoc * [soLuong];
		for (int i = 0; unsigned int(i) < soLuong; ++i) {
			string loaiPhong;
			cout << "\nNhap loai Phong ' Ly Thuyet / Thuc Hanh ': ";
			getline(cin, loaiPhong);
			// Chuyển đổi chuỗi nhập vào thành chữ thường
			string loaiPhongLower = toLower(loaiPhong);
			if (loaiPhongLower == "ly thuyet") {
				dsPhong[i] = new LyThuyet();
			}
			else if (loaiPhongLower == "thuc hanh") {
				dsPhong[i] = new ThucHanh();
			}
			else {
				cout << "\nLuu y! Ban da nhap sai loai phong, vui long kiem tra va nhap lai!\n";
				--i;
				continue;
			}
			dsPhong[i]->nhap();
			cin.ignore();
		}
	}

	void xuat() const {
		cout << "\nSo luong phong Hoc: " << soLuong ;
		cout << rows2 "---------------" << rows2 ;
		for (unsigned int i = 0; i < soLuong; ++i) {
			dsPhong[i]->xuat();
			cout << "---------------" << rows2 ;
		}
	}

	unsigned int demSoLuongPhongTHTheoToaNha(char toaNha) const {
		if (soLuong == 0) return 0;
		unsigned int dem = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			ThucHanh* thucHanh = th;
			if (thucHanh != nullptr) {
				if (tolower(thucHanh->getToaNha()) == tolower(toaNha))
					++dem;
			}
		}
		return dem;
	}

	unsigned int tongSucChuaTheoTangandToaNha(unsigned short tang, char toaNha) const {
		if (soLuong == 0) return 0;
		unsigned int tongSucChua = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i] != nullptr) {
				unsigned short soTangI = dsPhong[i]->getSoTang();
				char toaNhaI = dsPhong[i]->getToaNha();
				if (soTangI == tang && tolower(toaNhaI) == tolower(toaNha)) {
					LyThuyet* lyThuyet = lt;
					if (lyThuyet != nullptr) {
						tongSucChua += dsPhong[i]->getSucChua();
						continue;
					}
					tongSucChua += dsPhong[i]->getSucChua();
				}
			}
		}
		return tongSucChua;
	}

	float sucChuaTrungBinhPhonglyThuyet() const {
		if (soLuong == 0) return 0.0f;
		float tong = 0.0f;
		unsigned int dem = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			LyThuyet* lyThuyet = lt;
			if (lyThuyet != nullptr) {
				tong += lyThuyet->getSucChua();
				++dem;
			}
		}
		if (dem == 0) return 0.0f;
		return tong / dem;
	}

	bool coPhongTHLonHonPhongLTKhong() const {
		return maxSucChuaPhongTH() > maxSucChuaPhongLT();
	}

	// luyen code them
	PhongHoc** timPhongBangSucChuaChoTruoc(unsigned int sucChuaChoTruoc, unsigned int& soLuongNew) const {
		if (soLuong == 0) return nullptr;
		soLuongNew = 0;
		PhongHoc** listNew = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i]->getSucChua() == sucChuaChoTruoc)
				listNew[soLuongNew++] = dsPhong[i];
		}
		if (soLuongNew == 0) {
			delete[] listNew;
			return nullptr;
		}
		PhongHoc** afterCheck = new PhongHoc * [soLuongNew];
		for (unsigned int i = 0; i < soLuongNew; ++i)
			afterCheck[i] = listNew[i];
		delete[] listNew;
		return afterCheck;
	}

	PhongHoc** checkAndSort(unsigned int sucChuaChoTruoc, unsigned int& soLuongNew) const {
		PhongHoc** listNew = timPhongBangSucChuaChoTruoc(sucChuaChoTruoc, soLuongNew);
		if (listNew == nullptr) return nullptr;

		unsigned int slLT = 0, slTH = 0;
		PhongHoc** sapXepLT = new PhongHoc * [soLuongNew];
		PhongHoc** sapXepTH = new PhongHoc * [soLuongNew];
		for (unsigned int i = 0; i < soLuongNew; ++i) {
			LyThuyet* lyThuyet = lt;
			if (lyThuyet != nullptr)
				sapXepLT[slLT++] = listNew[i];
			else 
				sapXepTH[slTH++] = listNew[i];
		}

		sort(sapXepLT, sapXepLT + slLT, [](PhongHoc* a, PhongHoc* b) {
			return a->getToaNha() < b->getToaNha();
			});

		sort(sapXepTH, sapXepTH + slTH, [](PhongHoc* a, PhongHoc* b) {
			return a->getToaNha() < b->getToaNha();
			});

		for (unsigned int i = 0; i < slLT; ++i)
			listNew[i] = sapXepLT[i];
		for (unsigned int i = 0; i < slTH; ++i) {
			listNew[slLT + i] = sapXepTH[i];
		}
		delete[] sapXepLT;
		delete[] sapXepTH;
		return listNew;
	}
	//Đếm số lượng phòng theo loại (LT cho Lý Thuyết, TH cho Thực Hành).

	unsigned int demSoLuongPhongLT() const {
		if (soLuong == 0) return 0;
		unsigned int dem = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			LyThuyet* lyThuyet = lt;
			if (lyThuyet != nullptr)
				++dem;
		}
		return dem;
	}

	unsigned int demSoLuongPhongTH() const {
		if (soLuong == 0) return 0;
		unsigned int dem = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			ThucHanh* thucHanh = th;
			if (thucHanh != nullptr)
				++dem;
		}
		return dem;
	}
	//Xuất danh sách các phòng ở tầng soTang cho trước.

	PhongHoc** danhsachCacPhongBangSoTangChoTruoc(unsigned short soTang, unsigned int& soLuongNew) const {
		if (soLuong == 0) return nullptr;
		soLuongNew = 0;
		PhongHoc** listNew = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i]->getSoTang() == soTang)
				listNew[soLuongNew++] = dsPhong[i];
		}
		if (soLuongNew == 0) {
			delete[] listNew;
			return nullptr;
		}
		PhongHoc** afterCheck = new PhongHoc * [soLuongNew];
		for (unsigned int i = 0; i < soLuongNew; ++i)
			afterCheck[i] = listNew[i];
		delete[] listNew;
		return afterCheck;
	}

	//5. Tìm phòng có sức chứa lớn nhất trong một loại phòng (LT cho Lý Thuyết, TH cho Thực Hành).
	unsigned int maxSucChuaPhongTH() const {
		unsigned int sucChuaMax = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			ThucHanh* thucHanh = th;
			if (thucHanh != nullptr)
				sucChuaMax = MaxUNI(sucChuaMax, dsPhong[i]->getSucChua());
		}
		return sucChuaMax;
	}

	PhongHoc** phongThucHanhCoSucChuaLonNhat(unsigned int& soLuongNew) const {
		if (soLuong == 0) return nullptr;
		soLuongNew = 0;
		unsigned int maxSucChua = maxSucChuaPhongTH();
		PhongHoc** listTHNew = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			ThucHanh* thucHanh = th;
			if (thucHanh != nullptr && dsPhong[i]->getSucChua() == maxSucChua)
				listTHNew[soLuongNew++] = dsPhong[i];
		}
		if (soLuongNew == 0) {
			delete[] listTHNew;
			return nullptr;
		}
		PhongHoc** afterCheck = new PhongHoc * [soLuongNew];
		for (unsigned int i = 0; i < soLuongNew; ++i)
			afterCheck[i] = listTHNew[i];
		delete[] listTHNew;
		return afterCheck;
	}

	unsigned int maxSucChuaPhongLT() const {
		unsigned int sucChuaMax = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			LyThuyet* lyThuyet = lt;
			if (lyThuyet != nullptr)
				sucChuaMax = MaxUNI(sucChuaMax, dsPhong[i]->getSucChua());
		}
		return sucChuaMax;
	}


	PhongHoc** phongLyThuyetCoSucChuaLonNhat(unsigned int& soLuongNew) const {
		if (soLuong == 0) return nullptr;
		soLuongNew = 0;
		int sucChuaMax = maxSucChuaPhongLT();
		PhongHoc** listLT = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			LyThuyet* lyThuyet = lt;
			if (lyThuyet != nullptr && dsPhong[i]->getSucChua() == sucChuaMax) {
				listLT[soLuongNew++] = dsPhong[i];
			}
		}
		if (soLuongNew == 0) {
			delete[] listLT;
			return nullptr;
		}
		PhongHoc** listLTNew = new PhongHoc * [soLuongNew];
		for (unsigned int i = 0; i < soLuongNew; ++i)
			listLTNew[i] = listLT[i];
		delete[] listLT;
		return listLTNew;
	}
	// hàm copy phòng học
	PhongHoc** copyPhongHoc(PhongHoc** phong) const {
		PhongHoc** copyPhong = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (lt)
				copyPhong[i] = new LyThuyet(*lt);
			else if (th)
				copyPhong[i] = new ThucHanh(*th);
			else
				copyPhong[i] = nullptr;
		}
		return copyPhong;
	}

	//Sắp xếp danh sách dsPhong theo thứ tự tăng dần của sức chứa.
	PhongHoc** sapXepDSPhongTheoThuTuTangDanCuaSucChua() const {
		if (soLuong == 0) return nullptr;
		PhongHoc** listSapXep = copyPhongHoc(dsPhong);
		/*for (unsigned int i = 0; i < soLuong - 1; ++i) {
			unsigned int sucChuaI = listSapXep[i]->getSucChua;
			for (unsigned int j = i + 1; j < soLuong; ++j) {
				unsigned int sucChuaJ = listSapXep[j]->getSucChua;
				if (sucChuaI > sucChuaJ) {
					PhongHoc* temp = listSapXep[i];
					listSapXep[i] = listSapXep[j];
					listSapXep[j] = temp;
					sucChuaI = sucChuaJ;
				}
			}
		}*/

		sort(listSapXep, listSapXep + soLuong, [](PhongHoc* a, PhongHoc* b) 
			{ return a->getSucChua() < b->getSucChua(); });
		//listSapXep: Đây là con trỏ trỏ đến phần tử đầu tiên của mảng bạn muốn sắp xếp. Trong trường hợp này, listSapXep là mảng chứa các con trỏ tới các đối tượng PhongHoc.
		//listSapXep + soLuong: Đây là con trỏ trỏ đến phần tử ngay sau phần tử cuối cùng của mảng.Ta sử dụng listSapXep + soLuong để xác định điểm kết thúc của dải cần sắp xếp.
		return listSapXep;
	}
	//Xóa phòng khỏi danh sách dsPhong dựa trên thuộc tính (ví dụ: tên phòng hoặc tầng).
	void xoaPhongTheoTangPhong(unsigned short tang) {
		if (soLuong == 0) return;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if ( dsPhong[i] != nullptr && dsPhong[i]->getSoTang() == tang) {
				delete dsPhong[i];
				dsPhong[i] = nullptr;
				for (unsigned int j = i; j < soLuong - 1; ++ j) {
					dsPhong[i] = dsPhong[j + 1];
				}
				dsPhong[soLuong - 1] = nullptr;
				--soLuong;
				--i;
			}
		}
	}

	//Cập nhật sức chứa của phòng dựa trên thuộc tính (ví dụ: tên phòng hoặc tầng).
	//Theo Tầng và toaNha
	void updateSucChua(unsigned short soTang, char toaNha, unsigned int sucChuaUpdate) {
		if (soLuong == 0) return;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i]->getSoTang() == soTang
				&& tolower(dsPhong[i]->getToaNha()) == tolower(toaNha)) {
				dsPhong[i]->setSucChua(sucChuaUpdate);
			}
		}
	}

	//Đếm số lượng phòng trong một tòa nhà cụ thể.
	unsigned int demSoPhongTheoToaNha(char toaNha) const {
		if (soLuong == 0) return 0;
		unsigned int dem = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (tolower(dsPhong[i]->getToaNha()) == tolower(toaNha))
				++dem;
		}
		return dem;
	}

	//Tính tổng sức chứa của tất cả các phòng trong một tòa nhà cho trước.
	unsigned int tongSucChuaTheoToaNha(char toaNha) const {
		if (soLuong == 0) return 0;
		unsigned int sum = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (tolower(dsPhong[i]->getToaNha()) == tolower(toaNha))
				sum += dsPhong[i]->getSucChua();
		}
		return sum;
	}
	// tong suc chua cua all phong ly thuyet and thuc hanh trong truong hoc
	unsigned int tongSucChuaPhongLT() const {
		if (soLuong == 0) return 0;
		unsigned int sum = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (lt != nullptr)
				sum += dsPhong[i]->getSucChua();
		}
		return sum;
	}

	unsigned int tongSucChuaPhongTH() const {
		if (soLuong == 0) return 0;
		unsigned int sum = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (th != nullptr)
				sum += dsPhong[i]->getSucChua();
		}
		return sum;
	}

	//Tạo báo cáo thống kê chi tiết về số lượng phòng và sức chứa của từng loại phòng(Lý Thuyết, Thực Hành) trong từng tòa nhà.
	void baoCaoChiTiet() {
		if (soLuong == 0) {
			cout << "\nTruong hoc khong co bat ky phong hoc nao!";
			return;
		}
		cout << "\nHien tai trong truong Cao Dang Ky Thuat Cao Thang dang co " << soLuong << " phong hoc danh cho nganh cong nghe thong tin";
		cout << "\nTrong do so luong phong Ly thuyet chiem " << demSoLuongPhongLT() << " phong";
		cout << "\nPhong Thuc Hanh chiem " << demSoLuongPhongTH() << " phong";
		cout << "\nSuc Chua toi da cua " << demSoLuongPhongLT() << " phong Ly Thuyet la " << tongSucChuaPhongLT();
		cout << "\nSuc Chua toi da cua " << demSoLuongPhongTH() << " phong Thuc Hanh la " << tongSucChuaPhongTH();
		char* toaNhaS = new char[soLuong];
		unsigned int soLuongNew = 0;
		for (unsigned int i = 0; i < soLuong; ++i) {
			char toaNha = dsPhong[i]->getToaNha();
			bool kiemTra = false;
			for (unsigned int j = 0; j < soLuongNew; ++j) {
				if (tolower(toaNhaS[j]) == tolower(toaNha)) {
					kiemTra = true;
					break;
				}
			}
			if (!kiemTra) {
				toaNhaS[soLuongNew++] = toaNha;
			}
		}
		//sức chứa của từng loại phòng (Lý Thuyết, Thực Hành) trong từng tòa nhà.
		for (unsigned int i = 0; i < soLuongNew; ++i) {
			char toaNhaI = toaNhaS[i];
			unsigned int soLuongPhongLT = 0, soLuongPhongTH = 0;
			unsigned int sucChuaPhongLT = 0, sucChuaPhongTH = 0;
			for (unsigned int j = 0; j < soLuong; ++j) {
				if (tolower(toaNhaI) == tolower(dsPhong[j]->getToaNha())) {
					if (dynamic_cast<LyThuyet*>(dsPhong[j]) != nullptr) {
						++soLuongPhongLT;
						sucChuaPhongLT += dsPhong[j]->getSucChua();
					}
					else if (dynamic_cast<ThucHanh*>(dsPhong[j]) != nullptr) {
						++soLuongPhongTH;
						sucChuaPhongTH += dsPhong[j]->getSucChua();
					}
				}
			}

			cout << "\nToa nha " << toaNhaI << ":"; 
			cout << "\n\tSo Luong Phong Ly Thuyet: " << soLuongPhongLT;
			cout << "\n\tSuc Chua toi da phong Ly Thuyet: " << sucChuaPhongLT;
			cout << "\n\tSo Luong Phong Thuc Hanh: " << soLuongPhongTH;
			cout << "\n\tSuc Chua toi da phong Thuc Hanh: " << sucChuaPhongTH;
			cout << "\n\n------------------------\n\n";
		}
		delete[] toaNhaS;
	}

	// Tìm tất cả các phòng có sức chứa lớn hơn một giá trị cụ thể 
	// và xuất danh sách các phòng đó theo thứ tự tăng dần của sức chứa.
	PhongHoc** timPhongCoSucChuaLonHonGiaTriChoTuocAndSort(const float giaTri, unsigned int& soLuongNew) const {
		if (soLuong == 0) return nullptr;
		// Cách làm thông thường
		//soLuongNew = 0;
		/*PhongHoc** listNew = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i]->getSucChua() >= giaTri) {
				listNew[soLuongNew++] = dsPhong[i];
			}
		}
		if (soLuongNew == 0) {
			delete[] listNew;
			return nullptr;
		}
		sort(listNew, listNew + soLuongNew, [](PhongHoc* a, PhongHoc* b) {
			return a->getSucChua() < b->getSucChua();
			});
		return listNew;*/

		// Làm bằng vector
		vector<PhongHoc*> tempList;
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i]->getSucChua() >= giaTri) {
				tempList.push_back(dsPhong[i]);
			}
		}
		soLuongNew = static_cast<unsigned int>(tempList.size());
		if (soLuongNew == 0) return nullptr;
		sort(tempList.begin(), tempList.end(), [](PhongHoc* a, PhongHoc* b) {
			return a->getSucChua() < b->getSucChua();
			});
		PhongHoc** afterAdd = new PhongHoc * [soLuongNew];
		copy(tempList.begin(), tempList.end(), afterAdd);
		return afterAdd;
	}

	// Viết hàm sao chép dữ liệu phòng từ một danh sách dsPhong 
	// sang một danh sách khác mà không cần sử dụng các phương thức copy constructor của đối tượng.
	PhongHoc** copyPhongHoc(const TruongHoc& truongHoc) const {
		unsigned int soLuong = truongHoc.getSoLuong();
		if (soLuong == 0) return nullptr;
		PhongHoc** listNew = new PhongHoc * [soLuong];
		for (unsigned int i = 0; i < soLuong; ++i) {
			if (dsPhong[i] != nullptr) {
				if (LyThuyet* lyThuyet = lt) {
					listNew[i] = new LyThuyet(
						lyThuyet->getsoBan(), lyThuyet->getSucChua(),
						lyThuyet->getToaNha(), lyThuyet->getSoTang(),
						lyThuyet->getSTT()
					);
				}
				else if (ThucHanh* thucHanh = th) {
					listNew[i] = new ThucHanh(
						thucHanh->getSoMayTinh(), thucHanh->getSucChua(),
						thucHanh->getToaNha(), thucHanh->getSoTang(), thucHanh->getSTT()
					);
				}
				else {
					listNew[i] = nullptr;
				}
			}
			else {
				listNew[i] = nullptr;
			}
		}
		return listNew;
	}
	//Viết hàm tính toán tổng diện tích của tất cả các phòng trong danh sách dsPhong (giả sử mỗi phòng có thông tin về diện tích).

};