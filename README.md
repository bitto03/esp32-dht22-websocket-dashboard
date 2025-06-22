# ESP32 DHT22 WebSocket Dashboard

This project sets up an ESP32 as a Wi-Fi access point that hosts a web-based dashboard to display temperature and humidity readings from a DHT22 sensor using WebSocket for real-time updates.

## Features

- AP mode ESP32 Wi-Fi setup
- Reads temperature and humidity using DHT22 sensor
- Serves a real-time dashboard on a web page
- Uses WebSocket for live updates

## Requirements

- ESP32 board
- DHT22 sensor
- Arduino IDE with the following libraries:
  - WiFi
  - WebServer
  - WebSocketsServer
  - DHT sensor library

## Circuit

- DHT22 Data Pin -> GPIO 4
- VCC -> 3.3V
- GND -> GND

## Usage

1. Upload the code to the ESP32.
2. Connect to Wi-Fi `ESP32_AP` with password `12345678`.
3. Open a browser and go to `192.168.4.1`.
4. View live temperature and humidity readings on the dashboard.
