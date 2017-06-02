/*
* Lớp số nguyên lớn được xây dụng cới dữ liệu được lưu theo Little Endian.
* Có thể dễ dàng mở rộng chương trình với số nguyên lớn 32, 64, 128 bytes,...
* Dễ dàng trong việc bảo trì và nâng cấp chương trình.
*/

#include "QInt.h"
#include "Convert.h"

//---------------------------------NHÓM HÀM TẠO, HỦY---------------------------------
//Hàm khởi tạo mặc định (tạo số QInt với kích thước lưu trữ 16 byte).
CQInt::CQInt(const int &nSize)
{
	if (nSize > 0 && nSize % 4 == 0)
	{
		this->m_Data.resize(nSize / 4);
	}
}

//Hàm khỏi tạo bằng cách truyền vào chuỗi bit nhị phân.
CQInt::CQInt(const string &Binary, const int &nSize)
{
	if (nSize > 0 && nSize % 4 == 0)
	{
		this->m_Data.resize(nSize / 4);

		for (size_t i = 0; i < Binary.size(); i++)
		{
			if (Binary[i] == '1')
			{
				this->m_Data[_POSITION] = this->m_Data[_POSITION] | (1 << _SHIFT_OFFSET);
			}
		}
	}
}

//Hàm hủy dữ liệu của kiểu QInt (Không có xử lý gì đặc biệt).
CQInt::~CQInt()
{
}

//---------------------------------NHÓM HÀM GET, SET---------------------------------
//Hàm lấy data .
vector<_Uint32t> CQInt::getData() const
{
	return this->m_Data;
}

//---------------------------------NHÓM TOÁN TỬ VÀ PHÉP TOÁN SỐ HỌC---------------------------------
//Toán tử +.
CQInt CQInt::operator + (CQInt QInt) const
{
	CQInt Result = *this;
	CQInt Carry;

	while (!(QInt.isEqualZero()))
	{
		//Carry là những bit cùng là 1 giữa 2 số.
		Carry = Result & QInt;
		
		//Tổng các bit khác nhau của hai số (0 + 1 = 1).
		Result = Result ^ QInt;

		//Đưa các bit cùng là 1 bên 1 bit để tiếp tục phép cộng cần thực hiện.
		QInt = Carry << 1;
	}

	return Result;
}

//Toán tử -.
CQInt CQInt::operator - (CQInt QInt) const
{
	return (*this + CConvert::CQInttoTwosComplement(QInt));
}

//Toán tử *.
CQInt CQInt::operator * (CQInt QInt) const
{
	CQInt Result;
	CQInt Temp = *this;
	CQInt One("1"); //Số 1
	bool Negative = false; //Flag số âm

	if ((Temp.isNegative() && !QInt.isNegative()) || (!Temp.isNegative() && QInt.isNegative()))//Nếu 2 số trái dấu.
	{
		Negative = true;
	}

	if (QInt.isNegative())
	{
		QInt = ~(QInt - One); //Nếu âm thì chuyển về dạng số dương
	}
	if (Temp.isNegative())
	{
		Temp = ~(Temp - One); //Nếu âm thì chuyển về dạng số dương
	}

	//Nhân hai số dương.
	while (!(QInt.isNegative() || QInt.isEqualZero()))
	{
		if (((QInt & One) - One).isEqualZero()) //Nếu QInt lẻ thì cộng kết quả với Temp.
		{
			/*
			Giải thích: Vì sau mỗi lân ta đều chia QInt cho 2 nên QInt sẽ có 2 trạng thái chẫn và lẻ.
			Nếu QInt lẻ thì chia 2 sẽ dư 1 nên ta phải cộng Temp vào kết quả.
			VD: 6*3 = (6*2) + 6*1
			*/
			Result = Result + Temp;
		}

		Temp = Temp << 1; //Nhân Temp cho 2;
		QInt = QInt >> 1; //Chia QInt cho 2.
	}

	//Nếu như 2 số trái dấu.
	if (Negative == true)
	{
		Result = ~Result + One; //Chuyển Result về dạng bù 2.
	}

	return Result;
}

//Toán tử /.
CQInt CQInt::operator / (CQInt QInt) const
{
	CQInt Result;

	if (this->isEqualZero() || QInt.isEqualZero())
	{
		return Result;
	}
	else
	{
		CQInt One("1");

		if ((QInt - CQInt(1)).isEqualZero())
		{
			Result = *this;
		}
		else
		{
			CQInt Temp = *this;
			int k = Result.m_Data.size() * _BIT_UINT32_;
			bool Negative = false;

			if ((Temp.isNegative() && !QInt.isNegative()) || (!Temp.isNegative() && QInt.isNegative()))//Nếu 2 số trái dấu.
			{
				Negative = true;
			}

			if (QInt.isNegative())
			{
				QInt = ~(QInt - One); //Nếu âm thì chuyển về dạng số dương
			}
			if (Temp.isNegative())
			{
				Temp = ~(Temp - One); //Nếu âm thì chuyển về dạng số dương
			}

			while (k > 0)
			{
				Result = Result << 1;
				Result.m_Data[0] = Result.m_Data[0] | ((Temp.m_Data[Temp.m_Data.size() - 1] & (1 << (_BIT_UINT32_ - 1))) >> (_BIT_UINT32_ - 1));
				Temp = Temp << 1;

				Result = Result - QInt;
				if (Result.isNegative())
				{
					Result = Result + QInt;
				}
				else
				{
					Temp.m_Data[0] = Temp.m_Data[0] | 1;
				}

				--k;
			}

			Result = Temp;
			if (Negative == true)
			{
				Result = ~Result + One;
			}
		}
	}

	return Result;
}

//Toán tử gán =.
CQInt& CQInt::operator = (const CQInt &QInt)
{
	if (this != &QInt)
	{
		this->m_Data.resize(QInt.m_Data.size(), 0);

		for (int i = 0; i < QInt.m_Data.size(); i++)
		{
			this->m_Data[i] = QInt.m_Data[i];
		}
	}

	return *this;
}

//---------------------------------NHÓM TOÁN TỬ VÀ PHÉP TOÁN THAO TÁC TRÊN BIT---------------------------------
//Phép toán dịch phải (Shift Right).
CQInt CQInt::operator >> (const int &ShiftOffset)
{
	CQInt Result;
	//_Uint32t SignBit = (1 << (_BIT_UINT32_ - 1)) & this->m_Data[this->m_Data.size() - 1];
	Result.m_Data[0] = this->m_Data[0] >> ShiftOffset;

	for (int i = 1; i < this->m_Data.size(); i++)
	{
		//Đưa các bit tràn ra ngoài vào phần block 4 bytes thấp hơn.
		for (int j = 0; j < ShiftOffset; j++)
		{
			Result.m_Data[i - 1] = Result.m_Data[i - 1] | (((1 << j) & this->m_Data[i]) << (_BIT_UINT32_ - ShiftOffset + j));
		}

		Result.m_Data[i] = this->m_Data[i] >> ShiftOffset; //Tiến hành dịch bit.
	}

	//Result.m_Data[Result.m_Data.size() - 1] = Result.m_Data[Result.m_Data.size() - 1] | SignBit; //Giữ lại bit dấu.

	return Result;
}

//Phép toán dịch trái (Shift Left).
CQInt CQInt::operator << (const int &ShiftOffset)
{
	CQInt Result;
	//_Uint32t SignBit = (1 << (_BIT_UINT32_ - 1)) & this->m_Data[this->m_Data.size() - 1];
	Result.m_Data[Result.m_Data.size() - 1] = this->m_Data[this->m_Data.size() - 1] << ShiftOffset;
	//Result.m_Data[Result.m_Data.size() - 1] = Result.m_Data[Result.m_Data.size() - 1] | SignBit; //Giữ lại bit dấu.

	for (int i = this->m_Data.size() - 2; i > -1; i--)
	{
		//Đưa các bit tràn ra ngoài vào phần block 4 bytes cao hơn.
		for (int j = 0; j < ShiftOffset; j++)
		{
			Result.m_Data[i + 1] = Result.m_Data[i + 1] | (((1 << (_BIT_UINT32_ - j - 1)) & this->m_Data[i]) >> (_BIT_UINT32_ - ShiftOffset));
		}

		Result.m_Data[i] = this->m_Data[i] << ShiftOffset; //Tiến hành dịch bit.
	}

	return Result;
}

//Phép toán &.
CQInt CQInt::operator & (const CQInt &QInt) const
{
	CQInt Result;

	for (int i = 0; i < this->m_Data.size(); i++)
	{
		Result.m_Data[i] = this->m_Data[i] & QInt.m_Data[i];
	}

	return Result;
}

//Phép toán |.
CQInt CQInt::operator | (const CQInt &QInt) const
{
	CQInt Result;

	for (int i = 0; i < this->m_Data.size(); i++)
	{
		Result.m_Data[i] = this->m_Data[i] | QInt.m_Data[i];
	}

	return Result;
}

//Phép toán ^.
CQInt CQInt::operator ^ (const CQInt &QInt) const
{
	CQInt Result;

	for (int i = 0; i < this->m_Data.size(); i++)
	{
		Result.m_Data[i] = this->m_Data[i] ^ QInt.m_Data[i];
	}

	return Result;
}

//Phép toán ~.
CQInt& CQInt::operator ~ ()
{
	for (int i = 0; i < this->m_Data.size(); i++)
	{
		this->m_Data[i] = ~this->m_Data[i];
	}

	return *this;
}

//Phép toán xoay trái.
CQInt& CQInt::RoL()
{
	//Lưu bit bị đẩy ra ngoài.
	_Uint32t TempBit = (1 << (_BIT_UINT32_ - 1)) & this->m_Data[this->m_Data.size() - 1];
	*this = *this << 1; //Dịch trái 1 bit.
	this->m_Data[0] = this->m_Data[0] | (TempBit >> (_BIT_UINT32_ - 1)); //Chèn bit vùa bị đẩy ra vào.

	return *this;
}

//Phép toán xoay phải.
CQInt& CQInt::RoR()
{
	//Lưu bit bị đẩy ra ngoài.
	_Uint32t TempBit = 1 & this->m_Data[0];
	*this = *this >> 1; //Dịch phải 1 bit.
	this->m_Data[this->m_Data.size() - 1] = this->m_Data[this->m_Data.size() - 1] | (TempBit << (_BIT_UINT32_ - 1)); //Chèn bit vùa bị đẩy ra vào.

	return *this;
}

//---------------------------------NHÓM HÀM KIỂM TRA---------------------------------
//Hàm kiếm tra bằng không.
bool CQInt::isEqualZero() const
{
	for (int i = 0; i < this->m_Data.size(); i++)
	{
		if (this->m_Data[i] != 0)
		{
			return false;
		}
	}

	return true;
}

//Hàm kiểm tra số âm.
bool CQInt::isNegative() const
{
	if ((this->m_Data[this->m_Data.size() - 1] & (1 << (_BIT_UINT32_ - 1))) >> (_BIT_UINT32_ - 1) == 1)
	{
		return true;
	}

	return false;
}
