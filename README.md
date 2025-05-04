# 🔌 ESP8266 Switch Client with Wi-Fi Control & Status Indicator

This project runs on a NodeMCU ESP8266 and works as a **Wi-Fi switch controller**. It connects to a Wi-Fi Access Point (`ESP8266_Relay`) and sends HTTP requests to control relays based on the physical switch states. Additionally, it uses **red and green status LEDs** to show the connection status to the access point.

---

## 📦 Features

- 🖲️ 4 Physical Switches connected to GPIOs
- 📡 Connects to Access Point `ESP8266_Relay`
- 🌐 Sends HTTP requests to control relays
- 🔴 Red LED blinks continuously when not connected
- 🟢 Green LED blinks for 5 seconds every minute when connected
- 🧠 Switch state change detection (no redundant requests)
- ⚡ Compatible with latest ESP8266 Arduino core (uses `WiFiClient` with `HTTPClient`)

---

## 🔧 Hardware Requirements

- 1 × NodeMCU ESP8266
- 4 × Push Button Switches (Active LOW)
- 1 × Red LED (Connection error indicator)
- 1 × Green LED (Connected status indicator)
- 4 × 10kΩ resistors (for pull-ups, optional if using `INPUT_PULLUP`)
- Wires & Breadboard

---

## 📌 GPIO Pinout

| Function        | Pin  |
|----------------|------|
| Switch 1       | D1   |
| Switch 2       | D2   |
| Switch 3       | D5   |
| Switch 4       | D6   |
| Red LED        | D7   |
| Green LED      | D8   |

---

## 🌐 Relay Control Endpoints

| Relay | ON Endpoint                    | OFF Endpoint                   |
|--------|-------------------------------|-------------------------------|
| 1      | `http://192.168.4.1/relay1/on`  | `http://192.168.4.1/relay1/off` |
| 2      | `http://192.168.4.1/relay2/on`  | `http://192.168.4.1/relay2/off` |
| 3      | `http://192.168.4.1/relay3/on`  | `http://192.168.4.1/relay3/off` |
| 4      | `http://192.168.4.1/relay4/on`  | `http://192.168.4.1/relay4/off` |

> These endpoints are expected to be hosted by another NodeMCU or device configured as `ESP8266_Relay` in access point mode.

---

## 🛠️ How It Works

- On boot, the ESP8266 tries to connect to `ESP8266_Relay` AP.
- If not connected, red LED blinks continuously.
- If connected, green LED blinks for 5 seconds every minute.
- The state of each switch is monitored:
  - When a switch is pressed (LOW), it sends an HTTP request to turn ON the corresponding relay.
  - When released (HIGH), it sends an HTTP request to turn OFF the corresponding relay.

---

## 🚀 Getting Started

1. Open the sketch in Arduino IDE.
2. Select the board: `NodeMCU 1.0 (ESP-12E Module)`
3. Install required libraries if not already installed:
   - `ESP8266WiFi`
   - `ESP8266HTTPClient`
4. Upload the sketch to your NodeMCU.
5. Power it and connect to your relay AP (`ESP8266_Relay`).
6. Open Serial Monitor to debug.

---

## 📷 Visual Pinout Diagram

![ESP8266 Pin Diagram with Switches and LEDs](A_labeled_digital_illustration_depicts_an_ESP8266_.png)

---

## License

This project is licensed under the **Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)** License.

You are free to use, modify, and share the contents for **personal and educational purposes only**, with proper credit.  
**Commercial use is strictly prohibited.**

[![License: CC BY-NC 4.0](https://licensebuttons.net/l/by-nc/4.0/88x31.png)](https://creativecommons.org/licenses/by-nc/4.0/)


---

## ✍️ Author

**Somnath Mondal**  
Custom ESP8266 automation project with direct HTTP-based relay control.

