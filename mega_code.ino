#include "DHT.h"
#include "max6675.h"
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

//--> config DHT22
#define DHTPIN 8
#define DHTTYPE DHT22

//--> pin SoftwareSerial
const uint8_t pin_serial[2] = { 10, 9 };  //--> RX, TX

//--> Pin Sensor Tekanan
const uint8_t arr_Pin_s[4] = { A0, A1, A2, A3 };

//--> Pin Sensor Termokopel
const uint8_t arr_C_S[4] = { 22, 24, 26, 28 };
const uint8_t arr_S_O[4] = { 45, 47, 49, 51 };
const uint8_t arr_SCK[4] = { 35, 37, 39, 41 };

SoftwareSerial data_serial(pin_serial[0], pin_serial[1]);
DHT dht(DHTPIN, DHTTYPE);
PZEM004Tv30 pzem(data_serial);
MAX6675 suhu_1(arr_SCK[0], arr_C_S[0], arr_S_O[0]);
MAX6675 suhu_2(arr_SCK[1], arr_C_S[1], arr_S_O[1]);
MAX6675 suhu_3(arr_SCK[2], arr_C_S[2], arr_S_O[2]);
MAX6675 suhu_4(arr_SCK[3], arr_C_S[3], arr_S_O[3]);

float arr_dat[4] = { 0, 0, 0, 0 };
float arr_S_S[4] = { 0, 0, 0, 0 };
float arr_P_S[4] = { 0, 0, 0, 0 };

unsigned long time_1 = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  dht.begin();
}

void loop() {
  if (millis() - time_1 > 2000) {
    time_1 = millis();
    arr_S_S[0] = suhu_1.readCelsius();
    arr_S_S[1] = suhu_2.readCelsius();
    arr_S_S[2] = suhu_3.readCelsius();
    arr_S_S[3] = suhu_4.readCelsius();
    arr_P_S[0] = 3.00 * (float(5.00 * int(analogRead(arr_Pin_s[0])) / 1023.00) - 0.47);
    arr_P_S[1] = 3.00 * (float(5.00 * int(analogRead(arr_Pin_s[1])) / 1023.00) - 0.47);
    arr_P_S[2] = 3.00 * (float(5.00 * int(analogRead(arr_Pin_s[2])) / 1023.00) - 0.47);
    arr_P_S[3] = 3.00 * (float(5.00 * int(analogRead(arr_Pin_s[3])) / 1023.00) - 0.47);
    arr_dat[0] = dht.readHumidity();
    arr_dat[1] = pzem.voltage();
    arr_dat[2] = pzem.current();
    arr_dat[3] = pzem.power();

    //--> Kirim data
    Serial3.print("#" + String(arr_S_S[0]) + "#" + String(arr_S_S[1]) + "#" + String(arr_S_S[2]) + "#" + String(arr_S_S[3]));
    Serial3.print("#" + String(arr_P_S[0]) + "#" + String(arr_P_S[1]) + "#" + String(arr_P_S[2]) + "#" + String(arr_P_S[3]));
    Serial3.print("#" + String(arr_dat[0]) + "#" + String(arr_dat[1]) + "#" + String(arr_dat[2]) + "#" + String(arr_dat[3]));
    Serial3.println();
  }
  if (Serial3.available() > 0) {
    Serial.write(Serial3.read());
  }
}
