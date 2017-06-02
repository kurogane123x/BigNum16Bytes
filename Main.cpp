/*
* Họ và tên: Võ Sỹ Liên Thành
* MSSV: 1512515
* Email: vosylienthanh@gmail.com
* Facebook: https://www.facebook.com/VoSyLienThanh
*
* ------------------------------------------------------------------------
* Đây là ĐỒ ÁN I môn Kiến trúc máy tính và hợp ngữ (2016-2017).
* Ngày cập nhật: 03/04/2017
*
* ------------------------------------------------------------------------
* Yêu cầu đồ án: Thực hiện xây dựng chương trình thao tác với số nguyên lớn.
*
* ------------------------------------------------------------------------
* Ghi chú: Chương trình có thể dễ dàng xây dựng thành kiểu dữ liệu QInt 32, 64, 128 bytes,... bằng việc thay các số được
* define trong các file Header.
*/

#include "FileProcessing.h"

void main(int argc, char *argv[])
{
	if (argc != 3) //Nếu tham số truyền vào không đủ 3.
	{
		cout << "Your command doesn't exit." << endl;
		cout << "Please check and try again." << endl;
		cout << "We are so sorry about this problem." << endl;
	}
	else
	{
		cout << "Program is Calculating the result." << endl;
		cout << "Please be patient!" << endl;
		cout << "Tips: You can get something to drink when you run program." << endl;

		if (CFileProcessing::Processing(argv[1], argv[2])) //Xử lý file, tính toán, ghi file thành công.
		{
			cout << "--------------------------------------------" << endl;
			cout << "--------------------------------------------" << endl;
			cout << "Process have been done. You can see the result in file: " << argv[2] << endl;
		}
		else //Nếu không thành công.
		{
			cout << "--------------------------------------------" << endl;
			cout << "--------------------------------------------" << endl;
			cout << "Something went wong. Please try again." << endl;
			cout << "We are so sorry about this problem." << endl;
		}
	}

	//system("pause");
}