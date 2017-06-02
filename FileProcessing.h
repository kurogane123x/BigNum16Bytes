/*
* Lớp thao tác với file và xử lý phép toán trong file.
* Đây là lớp thuần tĩnh được xây dựng theo mẫu thiết kế Singleton.
* Dễ dàng trong việc bảo trì và nâng cấp chương trình.
*/

#ifndef _FILE_PROCESSING_H_
#define _FILE_PROCESSING_H_

#include <sstream>
#include <fstream>
#include "Convert.h"

#pragma pack(1)
class CFileProcessing
{
protected:
	static CFileProcessing *m_Instance;

	//--------------------------NHÓM HÀM TẠO, HỦY--------------------------
	//Hàm tạo.
	CFileProcessing();
	//Hàm hủy.
	~CFileProcessing();
public:
	//Hàm lấy thực thể.
	static CFileProcessing* getInstance();
	//Hàm đọc file vào xử lý sau đó ghi vào file khác.
	static bool Processing(const string&, const string&);
};
#endif