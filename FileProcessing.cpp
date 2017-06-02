/*
* Lớp thao tác với file và xử lý phép toán trong file.
* Đây là lớp thuần tĩnh được xây dựng theo mẫu thiết kế Singleton.
* Dễ dàng trong việc bảo trì và nâng cấp chương trình.
*/

#include "FileProcessing.h"

CFileProcessing* CFileProcessing::m_Instance = NULL;

//--------------------------NHÓM HÀM TẠO, HỦY--------------------------
//Hàm tạo.
CFileProcessing::CFileProcessing()
{
}

//Hàm hủy.
CFileProcessing::~CFileProcessing()
{
	if (this->m_Instance != NULL)
	{
		delete this->m_Instance;
	}
}

//Hàm lấy thực thể.
CFileProcessing* CFileProcessing::getInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CFileProcessing;
	}

	return m_Instance;
}

//Hàm đọc file vào xử lý sau đó ghi vào file khác.
bool CFileProcessing::Processing(const string &InFileName, const string &OutFileName)
{
	ifstream InFile(InFileName, ios::in);

	if (InFile)
	{
		ofstream OutFile(OutFileName, ios::out);

		if (OutFile)
		{
			string Temp;
			vector<string> Command;

			//Tiếm hành đọc file.
			while (!InFile.eof() && getline(InFile, Temp))
			{
				stringstream StrStream(Temp);
				Temp.clear(); //Xóa để tái sử dụng.

				while (getline(StrStream, Temp, ' '))
				{
					Command.push_back(Temp);
				}

				CQInt A;
				CQInt Result;

				//Toán tử >>, <<, +, -, *, /
				if (Command.size() == 4)
				{
					CQInt B;

					//Gán giá trị cho A và B.
					if (Command[0] == "2") //Số ở hệ nhị phân.
					{
						A = CQInt(Command[1]);
						B = CQInt(Command[3]);
					}
					else
					{
						if (Command[0] == "10") //Số ở hệ thập phân.
						{
							A = CQInt(CConvert::StrDectoBin(Command[1]));
							B = CQInt(CConvert::StrDectoBin(Command[3]));
						}
						else
						{
							A = CQInt(CConvert::StrHexorOcttoBin(Command[1]));
							B = CQInt(CConvert::StrHexorOcttoBin(Command[3]));
						}
					}

					//Thực hiện phép tính.
					if (Command[2] == ">>")
					{
						Result = A >> atoi(CConvert::CQInttoDecimalString(B).c_str()); //Chắc chắn số được tuyền vào là số thập phân.
					}
					else
					{
						if (Command[2] == "<<")
						{
							Result = A << atoi(CConvert::CQInttoDecimalString(B).c_str());
						}
						else
						{
							if (Command[2] == "+")
							{
								Result = A + B;
							}
							else
							{
								if (Command[2] == "-")
								{
									Result = A - B;
								}
								else
								{
									if (Command[2] == "*")
									{
										Result = A * B;
									}
									else
									{
										if (Command[2] == "/")
										{
											Result = A / B;
										}
										else
										{
											if (Command[2] == "&")
											{
												Result = A & B;
											}
											else
											{
												if (Command[2] == "|")
												{
													Result = A | B;
												}
												else
												{
													if (Command[2] == "^")
													{
														Result = A ^ B;
													}
												}
											}
										}
									}
								}
							}
						}
					}

					//Ghi kết quả vào file.
					if (Command[0] == "2") //Số ở hệ nhị phân.
					{
						OutFile << CConvert::CQInttoBinaryString(Result) << endl;
					}
					else
					{
						if (Command[0] == "10") //Số ở hệ thập phân.
						{
							OutFile << CConvert::CQInttoDecimalString(Result) << endl;
						}
						else
						{
							OutFile << CConvert::StrBintoHex(CConvert::CQInttoBinaryString(Result)) << endl;
						}
					}
				}
				else
				{
					if (Command.size() == 3) //Chuyển hệ hoặc toán tử ~, ror, rol.
					{
						//Gán giá trị cho A.
						if (Command[0] == "2") //Số ở hệ nhị phân.
						{
							A = CQInt(Command[2]);
						}
						else
						{
							if (Command[0] == "10") //Số ở hệ thập phân.
							{
								A = CQInt(CConvert::StrDectoBin(Command[2]));
							}
							else
							{
								A = CQInt(CConvert::StrHexorOcttoBin(Command[2]));
							}
						}

						//Thực hiện tính toán.
						if (Command[1] == "2")
						{
							OutFile << CConvert::CQInttoBinaryString(A) << endl;
						}
						else
						{
							if (Command[1] == "10")
							{
								OutFile << CConvert::CQInttoDecimalString(A) << endl;
							}
							else
							{
								if (Command[1] == "16")
								{
									OutFile << CConvert::StrBintoHex(CConvert::CQInttoBinaryString(A)) << endl;
								}
								else
								{
									if (Command[1] == "~")
									{
										Result = ~A;
									}
									else
									{
										if (_stricmp(Command[1].c_str(), "ror") == 0)
										{
											Result = A.RoR();
										}
										else
										{
											if (_stricmp(Command[1].c_str(), "rol") == 0)
											{
												Result = A.RoL();
											}
										}
									}

									//Ghi kết quả vào file.
									if (Command[0] == "2") //Số ở hệ nhị phân.
									{
										OutFile << CConvert::CQInttoBinaryString(Result) << endl;
									}
									else
									{
										if (Command[0] == "10") //Số ở hệ thập phân.
										{
											OutFile << CConvert::CQInttoDecimalString(Result) << endl;
										}
										else
										{
											OutFile << CConvert::StrBintoHex(CConvert::CQInttoBinaryString(Result)) << endl;
										}
									}
								}
							}
						}
					}
				}

				Command.clear(); //Đã thực hiẽn xong dòng đang xét. Xóa để tiếp tục thực hiện các dòng tiếp theo.
			}

			OutFile.close();
			return true; // Thức hiện thành công.
		}

		InFile.close();
	}

	return false;
}