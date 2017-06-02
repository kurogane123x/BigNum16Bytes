#ifndef _QINT_H_
#define _QINT_H_

/*
- Vị trí của a[i] trong mảng được xác dịnh như sau:
((Độ dài chuỗi - 1 - i) / kích thước bit của một vùng nhớ (ở đây là 32 bit).

Hình vẽ:
Chuỗi bit nhị phân: 11011110111110110000000000000000000000000000011
|	                        a[3]								   |...|	                        a[1]								  ||	                        a[0]								  |
|0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7|...|0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7|
|0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0|...|0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|1|1|0|1|1||1|1|0|1|1|1|1|1|0|1||1|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|1|1|

- Độ dời của bit về bên trái để thực hiện đưa bit vào số được tính như sau:
((Độ dài chuỗi - 1) % Kích thước bit của 1 vùng nhớ đang xét) - (i % Kích thước bit của 1 vùng nhớ)
Công thức này được tạo thành do chuỗi có vị trí bắt đầu ngược so với chuổi bit thực sự
Ví dụ: 1101 thì 1 trong chuỗi ký tự là phần tử đầu tiên tuy nhiên đây sẽ là bit thứ 3 trong một chuỗi bit
có độ dài 4 bit.
*/

#define _BIT_UINT32_		32 //Kiểu __int32 gồm có 32 bit.
#define _DEFAULT_SIZE	16	//Kích thước byte mặc định của kiểu QInt theo yêu cầu (16 byte)
#define _POSITION		((Binary.size() - 1 - i) / (sizeof(_Uint32t) * CHAR_BIT)) //Vị trí Vùng 4 Byte cần ghi vào.
#define _SHIFT_OFFSET	(((Binary.size() - 1) % (CHAR_BIT * sizeof(_Uint32t))) - (i % (CHAR_BIT * sizeof(_Uint32t)))) //Số bit cần dời.

/*
* Lớp số nguyên lớn được xây dụng cới dữ liệu được lưu theo Little Endian.
* Có thể dễ dàng mở rộng chương trình vo số nguyên lớn 32, 64, 128 bytes,...
* Dễ dàng trong việc bảo trì và nâng cấp chương trình.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#pragma pack(1)
class CQInt //Lớp QInt dùng cho số nguyên lớn có dấu.
{
protected:
	//Vùng nhớ lưu trữ cho kiểu QInt.
	vector<_Uint32t> m_Data;
public:
	//---------------------------------NHÓM HÀM TẠO, HỦY---------------------------------
	//Hàm khởi tạo mặc định (tạo số QInt với kích thước lưu trữ 16 byte).
	CQInt(const int& = _DEFAULT_SIZE);
	//Hàm khỏi tạo bằng cách truyền vào chuỗi bit nhị phân.
	CQInt(const string&, const int& = _DEFAULT_SIZE);
	//Hàm hủy dữ liệu của kiểu QInt (Không có xử lý gì đặc biệt).
	~CQInt();

	//---------------------------------NHÓM HÀM GET, SET---------------------------------
	//Hàm lấy data .
	vector<_Uint32t> getData() const;

	//---------------------------------NHÓM TOÁN TỬ VÀ PHÉP TOÁN SỐ HỌC---------------------------------
	//Toán tử +.
	CQInt operator + (CQInt) const;
	//Toán tử -.
	CQInt operator - (CQInt) const;
	//Toán tử *.
	CQInt operator * (CQInt) const;
	//Toán tử /.
	CQInt operator / (CQInt) const;
	//Toán tử gán =.
	CQInt& operator = (const CQInt&);

	//---------------------------------NHÓM TOÁN TỬ VÀ PHÉP TOÁN THAO TÁC TRÊN BIT---------------------------------
	//Phép toán dịch phải(Shift Right).
	CQInt operator >> (const int&);
	//Phép toán dịch trái(Shift Left).
	CQInt operator << (const int&);
	//Phép toán &.
	CQInt operator & (const CQInt&) const;
	//Phép toán |.
	CQInt operator | (const CQInt&) const;
	//Phép toán ^.
	CQInt operator ^ (const CQInt&) const;
	//Phép toán ~.
	CQInt& operator ~ ();
	//Phép toán xoay trái.
	CQInt& RoL();
	//Phép toán xoay trái.
	CQInt& RoR();

	//---------------------------------NHÓM HÀM KIỂM TRA---------------------------------
	//Hàm kiếm tra bằng không.
	bool isEqualZero() const;
	//Hàm kiểm tra số âm.
	bool isNegative() const;
};
#endif