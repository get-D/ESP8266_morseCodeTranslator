# 📡 Morse Code Translator (ESP8266 + SPIFFS)

A lightweight and interactive Morse code translator that runs entirely from a NodeMCU (ESP8266) using SPIFFS. Type a message into the web interface, and the microcontroller will play it in real-time using a buzzer.

---

## Features

- **Self-hosted** web app served directly from NodeMCU via SPIFFS
- **Text input** based UI
- Plays Morse code through a buzzer
- Clean, electronics-themed frontend 
- Fully offline-capable once uploaded

---

## 🔧 Tools & Tech

- **ESP8266 NodeMCU**
- **SPIFFS (ESP8266 Filesystem)**
- **HTML/CSS/JS** for frontend
- **Arduino IDE** for firmware
- Optional: **ESP8266FS Upload Tool** to flash web assets

---

##  How to Upload (Using Arduino IDE)

###  1. Install ESP8266 & SPIFFS Tools
- Install **ESP8266 Board** via Board Manager
- Add SPIFFS plugin (for Arduino 1.8.x only) → [Plugin Guide](https://github.com/esp8266/arduino-esp8266fs-plugin)

###  2. Upload the Web UI
1. Place `index.html`, `style.css`, and `script.js` inside a `data/` folder in your sketch directory
2. In Arduino IDE, go to:  
   **Tools → ESP8266 Sketch Data Upload**

### 3. Upload the Sketch
Upload `morseCodeTranslator_SPIFFS.ino` as usual

---

##  Accessing the Web App

1. Open the **Serial Monitor**
2. Note the IP address (e.g. `192.168.x.x`)
3. Open a browser and go to:
   ```
   http://192.168.x.x/
   ```

Type your message and press "Send" — the buzzer will beep out the Morse code!

---

##  Developed By

**Divyatwa Kirnapure**  
A fun, hands-on project to blend IoT, embedded systems, and user interface design.  
Built with passion and patience!
