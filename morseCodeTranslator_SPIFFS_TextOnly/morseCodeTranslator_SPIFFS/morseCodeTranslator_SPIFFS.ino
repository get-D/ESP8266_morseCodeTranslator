
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char* ssid = "D's-iQOO Z6 Lite 5G";
const char* password = "UN-limited";
const int BUZZER_PIN = 4;

ESP8266WebServer server(80);

const char* getMorseCode(char c) {
  switch (c) {
    case 'A': return ".-"; case 'B': return "-..."; case 'C': return "-.-.";
    case 'D': return "-.."; case 'E': return "."; case 'F': return "..-.";
    case 'G': return "--."; case 'H': return "...."; case 'I': return "..";
    case 'J': return ".---"; case 'K': return "-.-"; case 'L': return ".-..";
    case 'M': return "--"; case 'N': return "-."; case 'O': return "---";
    case 'P': return ".--."; case 'Q': return "--.-"; case 'R': return ".-.";
    case 'S': return "..."; case 'T': return "-"; case 'U': return "..-";
    case 'V': return "...-"; case 'W': return ".--"; case 'X': return "-..-";
    case 'Y': return "-.--"; case 'Z': return "--..";
    case '0': return "-----"; case '1': return ".----"; case '2': return "..---";
    case '3': return "...--"; case '4': return "....-"; case '5': return ".....";
    case '6': return "-...."; case '7': return "--..."; case '8': return "---..";
    case '9': return "----."; case ' ': return " ";
    default: return NULL;
  }
}

void handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";
  String contentType = "text/plain";
  if (path.endsWith(".html")) contentType = "text/html";
  else if (path.endsWith(".css")) contentType = "text/css";
  else if (path.endsWith(".js")) contentType = "application/javascript";

  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
  } else {
    server.send(404, "text/plain", "File Not Found");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("Connected! IP address: " + WiFi.localIP().toString());

  SPIFFS.begin();

  server.on("/", []() { handleFileRead("/index.html"); });
  server.on("/style.css", []() { handleFileRead("/style.css"); });
  server.on("/script.js", []() { handleFileRead("/script.js"); });

  server.on("/send", []() {
    String text = server.arg("text");
    text.toUpperCase();
    server.send(200, "text/plain", "OK");

    for (int i = 0; i < text.length(); i++) {
      const char* morse = getMorseCode(text.charAt(i));
      if (morse != NULL) {
        for (int j = 0; morse[j]; j++) {
          if (morse[j] == '.') {
            tone(BUZZER_PIN, 1000); delay(200); noTone(BUZZER_PIN);
          } else if (morse[j] == '-') {
            tone(BUZZER_PIN, 1000); delay(600); noTone(BUZZER_PIN);
          }
          delay(200);
        }
        delay(400);
      }
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
