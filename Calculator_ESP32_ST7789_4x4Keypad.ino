#include <stdio.h>
#include <stdlib.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <SPIFFS.h>
#include <Keypad.h>

#define TFT_CS                -1
#define TFT_RST                4  // Res
#define TFT_DC                15  // DC
#define TFT_SCLK              18  // SCL
#define TFT_MOSI              23  // SDA

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define ROWS  4
#define COLS  4

char keyMap[ROWS][COLS] = {
  {'1','2','3', '+'},
  {'4','5','6', '-'},
  {'7','8','9', '/'},
  {'*','0','#', 'x'}
};

uint8_t rowPins[ROWS] = {14, 27, 26, 25};
uint8_t colPins[COLS] = {33, 32, 5, 22};

Keypad keypad = Keypad(makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);

void setup_display() {
  tft.init(240, 240, SPI_MODE3);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_WHITE);
}

void print_display(byte x_pos, byte y_pos, char* text, byte text_size, uint16_t color) {
  tft.setCursor(x_pos, y_pos);
  tft.setTextSize(text_size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

String input = "";
String operand1 = "";
String operand2 = "";
char operatorChar = 0;
bool resultDisplayed = false;

void setup() {
  Serial.begin(115200);
  setup_display();
  print_display(0,20,"HAVALIHAVACI",6,ST77XX_BLUE);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (resultDisplayed) {
      input = "";
      operand1 = "";
      operand2 = "";
      operatorChar = 0;
      resultDisplayed = false;
      tft.fillScreen(ST77XX_WHITE);
    }

    Serial.println(key);

    // Operatör tuşu mu kontrol et
    bool isOperator = (key == '+' || key == '-' || key == 'x' || key == '/');

    // Hatalı durumları kontrol et
    if (isOperator) {
      if (input.length() > 0 && (input.endsWith("+") || input.endsWith("-") || input.endsWith("x") || input.endsWith("/"))) 
      {
        tft.fillScreen(ST77XX_WHITE);
        print_display(10, 100, "Error", 3, ST77XX_RED);
        resultDisplayed = true;
        return;
      }
      operand1 = input;
      operatorChar = key;
    }

    // Sayı tuşları veya geçerli bir operatör tuşu basıldığında
    input += key;

    // Eşittir tuşuna basıldığında (örneğin '#')
    if (key == '#') {
      operand2 = input.substring(operand1.length() + 1);  // İkinci operandı input'tan ayıkla
      float num1 = operand1.toFloat();
      float num2 = operand2.toFloat();
      float result = 0.0;

      switch (operatorChar) {
        case '+':
          result = num1 + num2;
          break;
        case '-':
          result = num1 - num2;
          break;
        case 'x':
          result = num1 * num2;
          break;
        case '/':
          if (num2 != 0) {
            result = num1 / num2;
          } else {
            print_display(10, 100, "Error", 3, ST77XX_RED);
            return;
          }
          break;
      }

      char resultStr[20];
      dtostrf(result, 4, 2, resultStr);  // Convert float to string
      tft.fillScreen(ST77XX_WHITE);
      print_display(10, 100, resultStr, 4, ST77XX_BLUE);
      resultDisplayed = true;
      return;
    }

    tft.fillScreen(ST77XX_WHITE);
    print_display(10, 100, (char*)input.c_str(), 4, ST77XX_BLUE);
  }
}
