#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-Fi Access Point details
const char* ssid = "ESP8266_Relay";
const char* password = "12345678";

// Relay control endpoints
const char* relay1OnURL  = "http://192.168.4.1/relay1/on";
const char* relay1OffURL = "http://192.168.4.1/relay1/off";
const char* relay2OnURL  = "http://192.168.4.1/relay2/on";
const char* relay2OffURL = "http://192.168.4.1/relay2/off";
const char* relay3OnURL  = "http://192.168.4.1/relay3/on";
const char* relay3OffURL = "http://192.168.4.1/relay3/off";
const char* relay4OnURL  = "http://192.168.4.1/relay4/on";
const char* relay4OffURL = "http://192.168.4.1/relay4/off";

// GPIO Pin Definitions
#define SWITCH1 D1
#define SWITCH2 D2
#define SWITCH3 D5
#define SWITCH4 D6
#define LED_RED D7
#define LED_GREEN D8

unsigned long lastStatusBlink = 0;
bool greenBlinkActive = false;
bool lastSwitchStates[4] = {false, false, false, false};

void setup() {
  Serial.begin(115200);

  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  pinMode(SWITCH3, INPUT_PULLUP);
  pinMode(SWITCH4, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to Access Point...");
}

void loop() {
  // Connection Status Indicator
  if (WiFi.status() != WL_CONNECTED) {
    // Red LED blinks continuously
    digitalWrite(LED_RED, HIGH);
    delay(500);
    digitalWrite(LED_RED, LOW);
    delay(500);
    return; // Skip the rest if not connected
  } else {
    // Green LED blinks 5 sec every minute
    if (millis() - lastStatusBlink >= 60000) {
      greenBlinkActive = true;
      lastStatusBlink = millis();
    }
    if (greenBlinkActive) {
      digitalWrite(LED_GREEN, HIGH);
      delay(5000);
      digitalWrite(LED_GREEN, LOW);
      greenBlinkActive = false;
    }
  }

  // Switch Logic
  checkAndSend(SWITCH1, 0, relay1OnURL, relay1OffURL);
  checkAndSend(SWITCH2, 1, relay2OnURL, relay2OffURL);
  checkAndSend(SWITCH3, 2, relay3OnURL, relay3OffURL);
  checkAndSend(SWITCH4, 3, relay4OnURL, relay4OffURL);

  delay(100); // Short delay to debounce
}

void checkAndSend(uint8_t pin, uint8_t index, const char* onURL, const char* offURL) {
  bool currentState = !digitalRead(pin); // Active LOW
  if (currentState != lastSwitchStates[index]) {
    lastSwitchStates[index] = currentState;
    const char* url = currentState ? onURL : offURL;
    sendHttpRequest(url);
  }
}

void sendHttpRequest(const char* url) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, url);  // ✅ FIXED for new library
    int httpCode = http.GET();
    Serial.printf("Request to %s => Code: %d\n", url, httpCode);
    http.end();
  }
}
