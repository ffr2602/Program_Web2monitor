#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//--> SSID dan PASS
const char* ssid = "************";  //--> Silahkan Masukkan SSID
const char* password = "********";  //--> Silahkan Masukkan PASSWORD

//--> Deklarasi Object
WiFiClient client;
HTTPClient http;

//--> Deklarasi Alamat Host
String address, payload;
String host = "http://web2monitor.site/";

//--> Data
const long interval[2] = { 60000, 5000 };
float data_terima[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned long time_1 = 0;
unsigned long time_2 = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(interval[1]);
}

void loop() {
  while (Serial.available() > 0 && millis() - time_2 > interval[1]) {
    time_2 = millis();
    String data_temp = Serial.readString();
    if (data_temp.length() > 0) {
      int index_1 = data_temp.indexOf('#');
      int index_2 = data_temp.indexOf('#', index_1 + 1);
      int index_3 = data_temp.indexOf('#', index_2 + 1);
      int index_4 = data_temp.indexOf('#', index_3 + 1);
      int index_5 = data_temp.indexOf('#', index_4 + 1);
      int index_6 = data_temp.indexOf('#', index_5 + 1);
      int index_7 = data_temp.indexOf('#', index_6 + 1);
      int index_8 = data_temp.indexOf('#', index_7 + 1);
      int index_9 = data_temp.indexOf('#', index_8 + 1);
      int index_10 = data_temp.indexOf('#', index_9 + 1);
      int index_11 = data_temp.indexOf('#', index_10 + 1);
      int index_12 = data_temp.indexOf('#', index_11 + 1);
      int index_13 = data_temp.indexOf('#', index_12 + 1);
      data_terima[0] = data_temp.substring(index_1 + 1, index_2).toFloat();
      data_terima[1] = data_temp.substring(index_2 + 1, index_3).toFloat();
      data_terima[2] = data_temp.substring(index_3 + 1, index_4).toFloat();
      data_terima[3] = data_temp.substring(index_4 + 1, index_5).toFloat();
      data_terima[4] = data_temp.substring(index_5 + 1, index_6).toFloat();
      data_terima[5] = data_temp.substring(index_6 + 1, index_7).toFloat();
      data_terima[6] = data_temp.substring(index_7 + 1, index_8).toFloat();
      data_terima[7] = data_temp.substring(index_8 + 1, index_9).toFloat();
      data_terima[8] = data_temp.substring(index_9 + 1, index_10).toFloat();
      data_terima[9] = data_temp.substring(index_10 + 1, index_11).toFloat();
      data_terima[10] = data_temp.substring(index_11 + 1, index_12).toFloat();
      data_terima[11] = data_temp.substring(index_12 + 1, index_13).toFloat();
      data_temp = "";
    }
  }
  if (millis() - time_1 > interval[0]) {
    time_1 = millis();
    if ((WiFi.status() == WL_CONNECTED)) {
      address = host + "api.php?";
      address += "&T1=" + String(data_terima[0]);
      address += "&T2=" + String(data_terima[1]);
      address += "&T3=" + String(data_terima[2]);
      address += "&T4=" + String(data_terima[3]);
      address += "&P1=" + String(data_terima[4]);
      address += "&P2=" + String(data_terima[5]);
      address += "&P3=" + String(data_terima[6]);
      address += "&P4=" + String(data_terima[7]);
      address += "&RH=" + String(data_terima[8]);
      address += "&V=" + String(data_terima[9]);
      address += "&I=" + String(data_terima[10]);
      address += "&P=" + String(data_terima[11]);
      http.begin(client, address);
      int httpCode = http.GET();
      if (httpCode > 0) {
        payload = http.getString();
        payload.trim();
        if (payload.length() > 0) {
          Serial.println(payload + "\n");
        }
      }
      http.end();
    }
  }
}
