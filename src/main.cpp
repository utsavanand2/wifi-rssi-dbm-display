#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <iostream>
#include <sstream>
#include <string>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define SCLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN 4
#define CS_PIN 5
#define RST_PIN 15

#define WHITE 0XFFFF
#define BLACK 0x0000
#define RED 0xF000

const char *SSID = "*****";
const char *PASSWD = "*****";

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

void drawText(char const *text, uint16_t color)
{
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.print(text);
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  tft.begin();
  tft.fillScreen(BLACK);
  Serial.println("Connecting to " + String(SSID));
  drawText("Connecting to Wifi", WHITE);
  WiFi.begin(SSID, PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }

  Serial.println("");
  Serial.println("Connected to " + String(SSID) + " with Mac Address: " + String(WiFi.BSSIDstr()) + " and IP: " + WiFi.localIP().toString());
  tft.fillScreen(BLACK);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE, BLACK);
    WiFi.begin(SSID, PASSWD);
    drawText("Connecting to Wifi", WHITE);
    while (WiFi.status() != WL_CONNECTED)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print(".");
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
    tft.fillScreen(BLACK);
  }

  int8_t rssi = WiFi.RSSI();
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.setTextColor(RED, BLACK);
  tft.print("RSSI\n");
  std::string r = std::to_string(rssi);
  char const *rssival = r.c_str();
  Serial.println(rssival);
  tft.setTextSize(2);
  tft.print(rssival);
  tft.print(" dBm");
  delay(500);
}
