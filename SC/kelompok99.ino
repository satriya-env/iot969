#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

// Inisialisasi RTC dan LCD
RTC_DS3231 rtc;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// Pin buzzer
const int buzzerPin = 8;

// Waktu alarm (ubah sesuai kebutuhan)
int alarmHour = 0;
int alarmMinute = 0;

void setup() {
  Wire.begin();
  rtc.begin();
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  lcd.print("Alarm Siap...");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // Tampilkan waktu di LCD
  lcd.setCursor(0, 0);
  lcd.print("Waktu: ");
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());

  // Cek apakah waktu sama dengan alarm
  if (now.hour() == alarmHour && now.minute() == alarmMinute) {
    lcd.setCursor(0, 1);
    lcd.print("ALARM BERBUNYI!");
    digitalWrite(buzzerPin, HIGH);
    delay(5000); // bunyi selama 5 detik
    digitalWrite(buzzerPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("                "); // hapus pesan
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Alarm: ");
    lcd.print(alarmHour);
    lcd.print(":");
    if (alarmMinute < 10) lcd.print("0");
    lcd.print(alarmMinute);
  }

  delay(1000); // update tiap detik
}
