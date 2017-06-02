/*
* Lớp chuyển đổi đi kèm với các phương thức chuyển đổi
* Đây là lớp thuần tĩnh được xây dựng theo mẫu thiết kế Singleton.
* Dễ dàng trong việc bảo trì và nâng cấp chương trình.
*/

#include "Convert.h"

//Khỏi tạo Instance
CConvert* CConvert::m_Instance = NULL;

//--------------------------NHÓM HÀM TẠO, HỦY--------------------------
//Hàm tạo.
CConvert::CConvert()
{
}

//Hàm hủy.
CConvert::~CConvert()
{
	if (this->m_Instance != NULL)
	{
		delete this->m_Instance;
	}
}

//--------------------------NHÓM HÀM GET, SET--------------------------
//Hàm lấy đối tượng.
CConvert* CConvert::getInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CConvert;
	}

	return m_Instance;
}

//--------------------------NHÓM HÀM CONVERT--------------------------
//Hàm chuyển chuỗi số nguyên sang chuỗi nhị phân.
string CConvert::StrDectoBin(string SrcDec)
{
	string Result;
	bool Negative = false;

	if (SrcDec[0] == '-') //Kiểm tra số âm.
	{
		SrcDec.erase(SrcDec.begin());
		Negative = true;
	}

	while (SrcDec != "")
	{
		Result.push_back(((SrcDec[SrcDec.size() - 1] - '0') % 2) + '0');
		SrcDec = StrDivTwo(SrcDec);
	}

	reverse(Result.begin(), Result.end());

	//Nếu là chuỗi ban đầu là số âm.
	if (Negative == true)
	{
		CQInt QInt(Result); //Đưa vài số kiểu CQInt.
		QInt = CQInttoTwosComplement(QInt); //Chuyển sang dạng bù 2.
		Result = CQInttoBinaryString(QInt); //Đưa lại về nhị phân.
	}

	return Result;
}

//Hàm chuyển chuỗi thập lục phân hoặc bát phân sang nhị phân.
string CConvert::StrHexorOcttoBin(string Str)
{
	string Binary;

	for (int i = 0; i < Str.size(); i++)
	{
		switch (Str[i])
		{
			case '0':
			{
				Binary = Binary + "0000";
				break;
			}
			case '1':
			{
				Binary = Binary + "0001";
				break;
			}
			case '2':
			{
				Binary = Binary + "0010";
				break;
			}
			case '3':
			{
				Binary = Binary + "0011";
				break;
			}
			case '4':
			{
				Binary = Binary + "0100";
				break;
			}
			case '5':
			{
				Binary = Binary + "0101";
				break;
			}
			case '6':
			{
				Binary = Binary + "0110";
				break;
			}
			case '7':
			{
				Binary = Binary + "0111";
				break;
			}
			case '8':
			{
				Binary = Binary + "1000";
				break;
			}
			case '9':
			{
				Binary = Binary + "1001";
				break;
			}
			case 'A':
			case 'a':
			{
				Binary = Binary + "1010";
				break;
			}
			case 'B':
			case 'b':
			{
				Binary = Binary + "1011";
				break;
			}
			case 'C':
			case 'c':
			{
				Binary = Binary + "1100";
				break;
			}
			case 'D':
			case 'd':
			{
				Binary = Binary + "1101";
				break;
			}
			case 'E':
			case 'e':
			{
				Binary = Binary + "1110";
				break;
			}
			case 'F':
			case 'f':
			{
				Binary = Binary + "1111";
				break;
			}
		}
	}

	return Binary;
}

//Hàm cuyển chuỗi thập lục phân hoặc bát phân sang nhị phân.
string CConvert::StrBintoHex(string Str)
{
	string Temp;
	string Result;

	//Thêm các số 0 vào để đủ block 4 bit.
	while (Str.size() % 4 != 0)
	{
		Str.insert(Str.begin(), '0');
	}

	for (int i = 0; i < Str.size(); i++)
	{
		Temp.push_back(Str[i]);

		if (i % 4 == 3) //Đã nhận được 4 bit.
		{
			if (Temp == "0000")//0
			{
				Result.push_back('0');
			}
			else
			{
				if (Temp == "0001")//1
				{
					Result.push_back('1');
				}
				else
				{
					if (Temp == "0010")//2
					{
						Result.push_back('2');
					}
					else
					{
						if (Temp == "0011")//3
						{
							Result.push_back('3');
						}
						else
						{
							if (Temp == "0100")//4
							{
								Result.push_back('4');
							}
							else
							{
								if (Temp == "0101")//5
								{
									Result.push_back('5');
								}
								else
								{
									if (Temp == "0110")//6
									{
										Result.push_back('6');
									}
									else
									{
										if (Temp == "0111")//7
										{
											Result.push_back('7');
										}
										else
										{
											if (Temp == "1000")//8
											{
												Result.push_back('8');
											}
											else
											{
												if (Temp == "1001")//9
												{
													Result.push_back('9');
												}
												else
												{
													if (Temp == "1010")//10
													{
														Result.push_back('A');
													}
													else
													{
														if (Temp == "1011")//11
														{
															Result.push_back('B');
														}
														else
														{
															if (Temp == "1100")//12
															{
																Result.push_back('C');
															}
															else
															{
																if (Temp == "1101")//13
																{
																	Result.push_back('D');
																}
																else
																{
																	if (Temp == "1110")//14
																	{
																		Result.push_back('E');
																	}
																	else
																	{
																		if (Temp == "1111")//15
																		{
																			Result.push_back('F');
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			Temp.clear(); //Đã xét xong 4 bit xóa để tiến hành xét 4 bit tiếp theo.
		}
	}

	return Result;
}

//Hàm chuyển số QInt sang số bù 2.
CQInt CConvert::CQInttoTwosComplement(CQInt QInt)
{
	return (~QInt + CQInt("1"));
}

//Hàm chuyển QInt sang chuỗi nhị phân.
string CConvert::CQInttoBinaryString(const CQInt &QInt)
{
	vector<_Uint32t> Data = QInt.getData();
	string BinaryStr;

	for (int i = 0; i < Data.size(); i++)
	{
		for (int j = 0; j < _BIT_UINT32_; j++)
		{
			BinaryStr.push_back(((Data[i] & (1 << j)) >> j) + '0');
		}
	}

	//Đảo chuỗi bit vừa xét và xóa những bit 0 thừa phía trước.
	reverse(BinaryStr.begin(), BinaryStr.end());
	if (BinaryStr.find('1') != string::npos)
	{
		BinaryStr.erase(BinaryStr.begin(), BinaryStr.begin() + BinaryStr.find('1'));
	}
	else
	{
		BinaryStr.resize(1);
	}

	return BinaryStr;
}

//Hàm chuyển QInt sang chuỗi số thập phân.
string CConvert::CQInttoDecimalString(const CQInt &QInt)
{
	vector<_Uint32t> Data = QInt.getData();
	string Decimal = "0";

	for (int i = 0; i < Data.size(); i++)
	{
		Decimal = AddNumberString(Decimal, MultiplyNumberString(to_string(Data[i]), Power(2, _BIT_UINT32_ * i)));
	}

	if (((Data[Data.size() - 1] & (1 << (_BIT_UINT32_ - 1))) >> (_BIT_UINT32_ - 1)) == 1)
	{
		Decimal = SubNumberString(Decimal, Power(2, _MAX_BIT_));
	}

	if (Decimal.empty())
	{
		Decimal.push_back('0');
	}

	/*//Cách 02: Tính theo từng bit.
	string Binary = CQInttoBinaryString(QInt);
	string Decimal = "0";

	for (int i = 0; i < Binary.size(); i++)
	{
		if (Binary[i] != '0')
		{
			if (Binary.size() - i < _MAX_BIT_)
			{
				Decimal = AddNumberString(Decimal, Power(2, Binary.size() - i - 1));
			}
			else
			{
				Decimal = SubNumberString(Decimal, Power(2, Binary.size() - i - 1));
			}
		}
	}*/

	return Decimal;
}


//--------------------------NHÓM HÀM HỖ TRỢ--------------------------
//Hàm chia một chuỗi số thập phân cho 2.
string CConvert::StrDivTwo(const string &Src)
{
	string Result;
	int Temp = 0;

	for (int i = 0; i < Src.size(); i++)
	{
		Temp = Temp * 10 + (Src[i] - '0');

		if (i > 0 || (i == 0 && Temp >= 2))
		{
			Result.push_back((Temp / 2) + '0');
		}

		Temp = Temp % 2;
	}

	return Result;
}

//Hàm cộng hai chuỗi số.
string CConvert::AddNumberString(string a, string b)
{
	if (a[0] == '-' && b[0] != '-')
	{
		a.erase(a.begin());
		a = SubNumberString(b, a);
	}
	else
	{
		if (b[0] == '-' && a[0] != '-')
		{
			b.erase(b.begin());
			a = SubNumberString(a, b);
		}
		else
		{
			int Temp = 0;
			bool Negative = false;

			if (a[0] == '-' && b[0] == '-')
			{
				Negative = true;
			}

			//Thêm các số 0 vào đầu mỗi chuỗi.
			if (a.size() > b.size())
			{
				while (a.size() != b.size())
				{
					b.insert(b.begin(), '0');
				}
			}
			else
			{
				while (a.size() != b.size())
				{
					a.insert(a.begin(), '0');
				}
			}

			//Tiến hành cộng.
			for (int i = a.size() - 1; i > -1; i--)
			{
				Temp = Temp + a[i] + b[i] - 2 * '0';
				a[i] = (Temp % 10) + '0';
				Temp = Temp / 10;
			}

			//Nếu vẫn còn dư (Temp != 0)
			if (Temp != 0)
			{
				a.insert(a.begin(), Temp + '0');
				Temp = 0;
			}
		}
	}

	//Xóa các số 0 thừa.
	while (a[0] == '0')
	{
		a.erase(a.begin());
	}

	return a;
}

//Hàm trừ hai chuỗi số dương.
string CConvert::SubNumberString(string a, string b)
{
	int Temp = 0;
	bool Negative = false;

	//Thêm các số 0 vào đầu mỗi chuỗi.
	if (a.size() > b.size())
	{
		while (a.size() != b.size())
		{
			b.insert(b.begin(), '0');
		}
	}
	else
	{
		while (a.size() != b.size())
		{
			a.insert(a.begin(), '0');
		}
	}

	//Kiểm tra a hay b lớn hơn và chuyển a thành số lớn hơn.
	if (strcmp(a.c_str(), b.c_str()) < 0)
	{
		string TempStr = a;
		a = b;
		b = TempStr;
		Negative = true; //a < b => a - b < 0
	}

	//Thực hiện phép trừ.
	for (int i = a.size() - 1; i > -1; i--)
	{
		if ((a[i] - Temp) < b[i])
		{
			a[i] = (10 + a[i] - b[i] - Temp) + '0';
			Temp = 1;
		}
		else
		{
			a[i] = a[i] - b[i] - Temp + '0';
			Temp = 0;
		}
	}

	//Xóa các số 0 thừa.
	while (a[0] == '0')
	{
		a.erase(a.begin());
	}

	//Nếu vẫn còn dư (Temp != 0)
	if (Negative == true)
	{
		a.insert(a.begin(), '-');
	}

	return a;
}

//Hàm nhân hai chuỗi.
string CConvert::MultiplyNumberString(string a, string b)
{
	string Result = "0";
	string TempStr;
	int Temp = 0;
	bool Negative = false;

	if (a[0] == '-')
	{
		if (b[0] != '-')
		{
			Negative = true;
		}
		a.erase(a.begin());
	}
	if (b[0] == '-')
	{
		if (a[0] != '-')
		{
			Negative = true;
		}
		b.erase(b.begin());
	}

	for (int i = 0; i < b.size(); i++)
	{
		for (int j = a.size() - 1; j > -1; j--)
		{
			Temp = Temp + (a[j] - '0') * (b[b.size() - i - 1] - '0');
			TempStr.push_back((Temp % 10) + '0');
			Temp = Temp / 10;
		}
		if (Temp != 0) //Nếu vẫn còn Temp.
		{
			TempStr.push_back(Temp + '0');
			Temp = 0;
		}

		//Đảo chuỗi.
		reverse(TempStr.begin(), TempStr.end());

		//Thêm các số 0 cần thiết vào sau.
		for (int j = 0; j < i; j++)
		{
			TempStr.push_back('0');
		}

		//Cộng Result và Temp.
		Result = AddNumberString(Result, TempStr);
		TempStr.clear(); //Dọn chuỗi tạm để dùng cho các bước tiếp theo.
	}

	if (Negative == true)
	{
		Result.insert(Result.begin(), '-');
	}

	return Result;
}

//Hàm tính a lũy thừa n (a, n là số nguyên không âm).
string CConvert::Power(int a, int n)
{
	string Result;

	if (a > -1)
	{
		//Nếu a > 1
		if (a > 1)
		{
			int Pow = n;

			if (n > (_BIT_UINT32_ - 1) * 2 / a) //Tránh trường hợp tràn số.
			{
				Pow = (_BIT_UINT32_ - 1) * 2 / a;
			}

			Result = to_string((_Uint32t)pow(a, Pow));

			
			//Phần có khả năng bị tràn số sẽ được nhân theo nhân chuỗi.
			for (int i = Pow + 1; i <= n; i++)
			{
				Result = MultiplyNumberString(Result, to_string(a));
			}
		}
		else
		{
			Result.push_back(a + '0');
		}
	}

	return Result;
}