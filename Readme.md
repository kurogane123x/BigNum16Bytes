### Thông tin cá nhân:
- Họ và tên: Võ Sỹ Liên Thành
- Sinh viên trường Đại học Khoa học tự nhiên - ĐHQG TP.HCM
- Khoa Công nghệ thông tin
- Chuyên ngành Kỹ thuật phần mềm

### Giới thiệu chung về project:

#### Số Bignum16Bytes là gì?
- Trong Project này số Bignum là số nguyên (int) được lưu trữ trong 16 bytes (128 bit) trong những phần sau sẽ được gọi bằng số QInt cho ngắn gọn

#### Ý tưởng cài đặt:
- Lưu QInt trong 1 dãy 4 số nguyên unsinged int.
- Các phép tính được xây dựng theo cách thao tác trên 1 block 4 byte tức 1 số unsigned int.

###### Tại sao lại dùng số unsigned int mà không dùng những số khác.
- Vì số nguyên int có các đặc điểm của số nguyên.
- Vì ta sẽ không cần để ý đến dấu của các block lưu trữ.
- Vì dễ quản lý và cài đặt.

###### Cài đặt như thế nào?
- Project này được cài đặt theo hướng đối tượng (chi tiết xem các file mã nguồn).

#### Các chức năng chính:
- Chương trình được xây dựng theo lập trình hướng đối tượng nên số QInt có đầy đủ các phương thức của số nguyên như: +, -, *, /, >>, <<, &, ^, |, ~
- Ngoài ra còn có so sánh >, <, =
- Chi tiết cách xữ lý xem phần mã nguồn.

#### Luồng xử lý phụ:
- Máy tính không đủ bộ nhớ sẽ hiển thị thông báo.
