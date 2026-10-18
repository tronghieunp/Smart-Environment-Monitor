#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#define LED 5
#define DHTPIN 4
#define DHTTYPE DHT22

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const unsigned long interval = 2000;
const float temperatureLimit = 35;
const float humidityLimit = 80;
const float timeLimit = 15000;
unsigned long lastRead = 0;
unsigned long startAttempt;
float temperature;
float humidity;
DHT dht(DHTPIN, DHTTYPE);

void sendJSON(String json){
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi chua ket noi");
    return;
  }
  HTTPClient http;
  http.begin("https://httpbin.org/post");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(json);
  if(httpCode > 0) {
    Serial.printf("HTTP status: %d \n", httpCode);
    Serial.println("Phan hoi tu may chu:");
    Serial.println(http.getString());
  }
  else {
    Serial.printf("Gui that bai: %s \n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void readSensor() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}
void printData() {
  Serial.printf("Nhieu do: %.1f °C \n",temperature);
  Serial.printf("Do am: %.1f %% \n",humidity);
}
int checkAlert() {
  if(temperature >= temperatureLimit || humidity >= humidityLimit) return HIGH;
  return LOW;
}
void controlLED(int statusLED) {
  digitalWrite(LED, statusLED);
}
String createJSON() {
  String json = "{";
  json += "\"temperature\":" + String(temperature, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"alert\":" + String((checkAlert() == LOW ? "false" : "true"));
  json += "}";
  return json;
}

void reconnectWiFi() {
  if(WiFi.status() == WL_CONNECTED){
    return;
  }
  Serial.println("WiFi mat ket noi, dang thu ket noi lai");
  WiFi.disconnect();
  Serial.printf("Dang ket noi toi WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  startAttempt = millis();
  while(WiFi.status() != WL_CONNECTED && millis() - startAttempt <= timeLimit) {
    delay(500);
    Serial.printf(".");
  }
  Serial.println("");
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Ket noi WiFi that bai");
  } 
  else {
    Serial.println("Ket noi WiFi thanh cong");
    Serial.printf("Dia chi WiFi la: ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  dht.begin();
  Serial.begin(115200);
}

void loop() {
  if(millis() - lastRead > interval){
    reconnectWiFi();
    lastRead = millis();
    readSensor();
    if(isnan(temperature) || isnan(humidity)) {
      Serial.printf("loi DHT22 \n");
      return;
    }
    printData();
    controlLED(checkAlert());
    String json = createJSON();\
    Serial.println("JSON gui di:");
    Serial.println(json);
    sendJSON(json);
  }
}
