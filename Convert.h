/*
* Lớp chuyển đổi đi kèm với các phương thức chuyển đổi
* Đây là lớp thuần tĩnh được xây dựng theo mẫu thiết kế Singleton.
* Dễ dàng trong việc bảo trì và nâng cấp chương trình.
*/

#ifndef _CONVERT_H_
#define _CONVERT_H_

#define _MAX_BIT_	128

#include "QInt.h"

#pragma pack(1)
class CConvert
{
protected:
	static CConvert *m_Instance;

	//--------------------------NHÓM HÀM TẠO, HỦY--------------------------
	//Hàm tạo.
	CConvert();
	//Hàm hủy.
	~CConvert();
public:
	//--------------------------NHÓM HÀM GET, SET--------------------------
	//Hàm lấy đối tượng.
	static CConvert* getInstance();

	//--------------------------NHÓM HÀM CONVERT--------------------------
	//Hàm chuyển chuỗi số nguyên sang chuỗi nhị phân.
	static string StrDectoBin(string);
	//Hàm chuyển chuỗi thập lục phân hoặc bát phân sang nhị phân.
	static string StrHexorOcttoBin(string);
	//Hàm cuyển chuỗi thập lục phân hoặc bát phân sang nhị phân.
	static string StrBintoHex(string);
	//Hàm chuyển số QInt sang số bù 2.
	static CQInt CQInttoTwosComplement(CQInt);
	//Hàm chuyển QInt sang chuỗi nhị phân.
	static string CQInttoBinaryString(const CQInt&);
	//Hàm chuyển QInt sang chuỗi số thập phân.
	static string CQInttoDecimalString(const CQInt&);

	//--------------------------NHÓM HÀM HỖ TRỢ--------------------------
	//Hàm chia một chuỗi số thập phân cho 2.
	static string StrDivTwo(const string&);
	//Hàm cộng hai chuỗi số.
	static string AddNumberString(string, string);
	//Hàm trừ hai chuỗi số dương.
	static string SubNumberString(string, string);
	//Hàm nhân hai chuỗi số.
	static string MultiplyNumberString(string, string);
	//Hàm tính a lũy thừa n (a, n là số nguyên không âm).
	static string Power(int, int);
};
#endif