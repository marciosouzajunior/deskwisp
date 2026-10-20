#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET = -1;
constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t findDisplayAddress() {
  for (uint8_t address : {0x3C, 0x3D}) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      return address;
    }
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println();
  Serial.println("DeskWisp - teste OLED");

  const uint8_t address = findDisplayAddress();
  if (address == 0) {
    Serial.println("OLED nao encontrado em 0x3C ou 0x3D");
    return;
  }

  Serial.printf("OLED encontrado em 0x%02X\n", address);
  if (!display.begin(SSD1306_SWITCHCAPVCC, address)) {
    Serial.println("Falha ao iniciar o OLED");
    return;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(10, 12);
  display.println("DeskWisp");
  display.setTextSize(1);
  display.setCursor(34, 42);
  display.println("ESP32 OK");
  display.display();

  Serial.println("Teste do OLED concluido");
}

void loop() {
  delay(1000);
}
