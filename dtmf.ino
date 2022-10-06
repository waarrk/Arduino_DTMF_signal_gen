#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DTMF_L_1 697
#define DTMF_L_2 770
#define DTMF_L_3 852
#define DTMF_L_4 941

#define DTMF_H_1 1209
#define DTMF_H_2 1336
#define DTMF_H_3 1477
#define DTMF_H_4 1633

LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
                         {'4', '5', '6', 'B'},
                         {'7', '8', '9', 'C'},
                         {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Serial.println("Program Start");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DTMF Signal Gen");
  delay(1000);
  lcd.clear();
}

int lcd_print(char key, int high, int low) {
  lcd.setCursor(0, 0);
  lcd.print("Pushed ... ");
  lcd.print(key);
  lcd.setCursor(0, 1);
  lcd.print("H ");
  lcd.print(high);
  lcd.print("HZ L ");
  lcd.print(low);
  lcd.print("HZ");
  return 0;
}

int buzz(int high, int low) {
  for (int i = 0; i < 20; i++) {
    tone(10, high, 100);
    tone(10, low, 100);
  }
}

int dtmf(char key) {
  switch (key) {
    case '1':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_1, DTMF_H_1);
      buzz(DTMF_L_1, DTMF_H_1);
      break;
    case '2':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_1, DTMF_H_2);
      buzz(DTMF_L_1, DTMF_H_2);
      break;
    case '3':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_1, DTMF_H_3);
      buzz(DTMF_L_1, DTMF_H_3);
      break;
    case 'A':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_1, DTMF_H_4);
      buzz(DTMF_L_1, DTMF_H_4);
      break;
    case '4':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_2, DTMF_H_1);
      buzz(DTMF_L_2, DTMF_H_1);
      break;
    case '5':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_2, DTMF_H_2);
      buzz(DTMF_L_2, DTMF_H_2);
      break;
    case '6':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_2, DTMF_H_3);
      buzz(DTMF_L_2, DTMF_H_3);
      break;
    case 'B':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_2, DTMF_H_4);
      buzz(DTMF_L_2, DTMF_H_4);
      break;
    case '7':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_3, DTMF_H_1);
      buzz(DTMF_L_3, DTMF_H_1);
      break;
    case '8':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_3, DTMF_H_2);
      buzz(DTMF_L_3, DTMF_H_2);
      break;
    case '9':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_3, DTMF_H_3);
      buzz(DTMF_L_3, DTMF_H_3);
      break;
    case 'C':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_3, DTMF_H_4);
      buzz(DTMF_L_3, DTMF_H_4);
      break;
    case '*':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_4, DTMF_H_1);
      buzz(DTMF_L_4, DTMF_H_1);
      break;
    case '0':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_4, DTMF_H_2);
      buzz(DTMF_L_4, DTMF_H_2);
      break;
    case '#':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_4, DTMF_H_3);
      buzz(DTMF_L_4, DTMF_H_3);
      break;
    case 'D':
      digitalWrite(LED_BUILTIN, HIGH);
      lcd_print(key, DTMF_L_4, DTMF_H_4);
      buzz(DTMF_L_4, DTMF_H_4);
      break;
  }
  return 0;
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    lcd.clear();
    Serial.println(key);
    dtmf(key);
  }
  digitalWrite(LED_BUILTIN, LOW);
}