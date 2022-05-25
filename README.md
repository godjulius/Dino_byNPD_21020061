- giải nén file debug.rar để được 1 thư mục tên debug rồi copy paste các folder font, imgs, sound ở ngoài vào folder debug để chạy được file .exe.

## **PART 1: Hướng dẫn cài đặt**
- Chạy code trên ide Visual studio bản 2019 trở lên rồi thực hiện hướng dẫn theo link dưới
https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
Các file của thư viện đồ hoạ SDL đã có sẵn trên folder LibSdl2 trong project
- Tổ chức vị trí các file như trong project.																												
## 	**PART 2: Mô tả chung về trò chơi Dino Jump:**
- Tương tự như game khủng long khi mất mạng ở Google Chrome
- Con khủng long sẽ nhảy để tránh các chướng ngại vật, ăn điểm thưởng để có nhiều điểm nhất có thể
- Các chướng ngại vật có 2 loại là InAir và OnGround sẽ di chuyển về phía khủng long
- Có 3 chế độ chơi là Easy, Medium và Hard với độ khó tăng dần(tăng số lượng vật cản, tăng về gia tốc của các vật cản)
## 	**PART 3: Mô tả các chức năng đã cài đặt, link video minh hoạ:**
- Điểm cao: hiển thị top 7 người chơi điểm cao nhất
- Nút help: giới thiệu trò chơi, hướng dẫn chơi
- 3 chế độ chơi Easy, Medium, Hard (tăng số lượng vật cản, tăng về gia tốc của các vật cản)
- có 4 màu nhân vật để lựa chọn
- Ghi tên người chơi để lưu lại khi nằm trong top điểm cao
- ấn SPACE hoặc MŨI TÊN LÊN để nhảy
- ấn MŨI TÊN XUỐNG ĐỂ rơi
- Nút Pause để tạm dừng khi đang chơi
## **PART 4: Các kĩ thuật được sử dụng trong lập trình**
- Đồ hoạ SDL, SDL_Image, SDL_ttf
- Âm thanh SDL_Mixer
- Class, kế thừa
- vòng lặp game loop
- dùng mảng, vector pair, sắp xếp mảng
- con trỏ
- nhập xuất bằng file
## **PART 5: Kết luận:**
- 1, Hướng phát triển:
- Làm mượt hơn, tăng fps
- Chơi trong mạng Lan, các máy sẽ được chơi cùng 1 map và các người chơi sẽ thi xem ai nhiều điểm hơn
- 2, Các điều rút ra được sau khi hoàn thiện chương trình:
- Tổ chức các class hợp lý
- Làm các hàm chức năng tối ưu
- Tính kế thừa
- Code sạch đẹp, refactor
- Chia file
## **P/S:**
- Các hàm cơ bản của đối tượng được tham khảo từ phattrienphanmem123az
- Các hàm nâng cao hơn về game học từ lazyfoo
- Nhân vật khủng long: https://arks.itch.io/dino-characters
