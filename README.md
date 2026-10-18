# 🌡️ Smart Environment Monitor (Hệ thống Giám sát Môi trường)

> Dự án IoT đầu tiên: Giám sát nhiệt độ & độ ẩm bằng ESP32 và gửi dữ liệu qua WiFi.

## 📝 Giới thiệu (Introduction)
Đây là dự án sử dụng vi điều khiển **ESP32** kết hợp với cảm biến **DHT22** để đo nhiệt độ và độ ẩm của môi trường. Dữ liệu sau khi thu thập sẽ được đóng gói dưới dạng chuỗi **JSON** và gửi lên Server thông qua giao thức WiFi (HTTP POST).

*(This is an IoT project using ESP32 and DHT22 to monitor temperature and humidity. Data is sent to a server via WiFi in JSON format.)*

## 🚀 Tính năng (Features)
- 🌡️ Đọc dữ liệu nhiệt độ (°C) và độ ẩm (%) liên tục.
- 🚨 Tự động bật đèn LED cảnh báo khi Nhiệt độ > 35°C hoặc Độ ẩm > 80%.
- 📡 Tự động kết nối lại WiFi nếu bị rớt mạng.
- 📦 Đóng gói dữ liệu thành chuỗi JSON để dễ dàng gửi lên Server.
- 💻 Hỗ trợ chạy mô phỏng hoàn chỉnh trên nền tảng Wokwi.

## 🛠️ Linh kiện sử dụng (Hardware)
| Linh kiện | Số lượng | Ghi chú |
| :--- | :---: | :--- |
| Board mạch ESP32 DevKit V1 | 1 | Vi điều khiển chính |
| Cảm biến DHT22 | 1 | Đo nhiệt độ & độ ẩm |
| Đèn LED (Đỏ) | 1 | Đèn báo cảnh báo |
| Dây cắm (Jumper wires) | Nhiều | Đấu nối |

## 🔌 Sơ đồ nối dây (Wiring Diagram)
<img width="665" height="571" alt="image" src="https://github.com/user-attachments/assets/04bff8aa-8f60-4469-8bcb-6edc5210fc8c" />


**Chi tiết kết nối:**
- **DHT22:**
  - VCC ➔ 3V3 (ESP32)
  - GND ➔ GND (ESP32)
  - DATA ➔ GPIO 4 (ESP32)
- **LED Cảnh báo:**
  - Anode (Chân dài) ➔ GPIO 5 (ESP32)
  - Cathode (Chân ngắn) ➔ GND (ESP32) *(qua điện trở 220Ω)*

## 💻 Công nghệ sử dụng (Tech Stack)
- **Ngôn ngữ:** C++ (Arduino Framework)
- **Môi trường phát triển:** VS Code + PlatformIO
- **Mô phỏng:** Wokwi Simulator
- **Giao thức:** HTTP, JSON, WiFi

## ⚙️ Cách chạy dự án (How to run)
1. **Clone dự án này về máy:**
   ```bash
   git clone https://github.com/tronghieunp/Smart-Environment-Monitor.git
