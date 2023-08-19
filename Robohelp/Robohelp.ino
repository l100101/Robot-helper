#include <GyverHC595.h>  //74hc595 lib. 2 индикатора для вывода режима: основной и подрежим(номер эксперимента и номер самостоятельного задания)
#include <GyverButton.h> //для кнопок
//энкодер вместо кнопок?

// #include <

// GyverHC595<2, HC_SPI, 8000000> reg(10); // аппаратный SPI, кастомная скорость
// GyverHC595<2, HC_PINS> reg(10, 11, 13); // программный SPI (bit bang)

GButton butt1(BTN_PIN);

const int photoresistorPin = A0; // Пин для фоторезистора
const int ledPin = 13;           // Пин для Сигнального светодиода
const int buzzer_pin = 5;        // Пин для пищалки
const int btn_pin = 3;           // кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)

const int threshold = 500;     // Пороговое значение для определения мигания
const int period = 1000;       // Измеряемый период

byte mode = 0;    // режим работы
byte submode = 0; // под-режим
boolean check = false;
void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  butt1.tick(); // обязательная функция отработки. Должна постоянно опрашиваться
  if (butt1.isSingle())
    mode++; // проверка на один клик
  if (butt1.isDouble())
    submode++; // проверка на один клик
  if (butt1.isHold())
    check = !check; // проверка на один клик

  displaymode();

  if (check)
  {
    switch (mode)
    {
    case 0:
      break;
    case 1:
      lesson_1();
      break;
    case 2:
      lesson_2();
      break;
    case 3:
      lesson_3();
      break;
    case defaut:
      mode = 0;
      break;
    }
  }
}

void lesson_1()
{
  switch (submode)
  {
  case 0:
    lesson_1_0();
    break;
  case 1:
    lesson_1_1();
    break;
  case 2:
    lesson_1_2();
    break;
  default:
    break;
  }
}

void lesson_1_0()
{
  int lightValue = analogRead(photoresistorPin); // Считываем значение с фоторезистора

  if (lightValue > threshold)
  {
    int startMillis = millis(); // Запоминаем текущее время
    int blinkPeriod = 0;

    while (digitalRead(photoresistorPin) > threshold)
    {
      // Ждем, пока светодиод выключится
      blinkPeriod = millis() - startMillis;
    }

    if (blinkPeriod > period - 50 && blinkPeriod < period + 50)
    {
      // Serial.println("Период мигания составляет 1 секунду.");
      success(); // функция, сигнализирующая об успехе
    }
    else
    {
      fail(); // функция, сигнализирующая об ошибке
    }
  }
}
void lesson_1_1()
{
  int pause_time = 1000;

  static int step = 0;

  int lightValue = analogRead(photoresistorPin); // Считываем значение с фоторезистора

  if (step == 0 && lightValue > threshold)
  {
    int startMillis = millis(); // Запоминаем текущее время
    int blinkPeriod = 0;

    while (analoglRead(photoresistorPin) > threshold)
    {
      // Ждем, пока светодиод выключится
      blinkPeriod = millis() - startMillis;
    }
    if (blinkPeriod > period - 50 && blinkPeriod < period + 50) // если в пределах +- 50мс
    {
      step = 1;
    }
  }
  if (step == 1)
  {

    period = 1000;
    startMillis = millis(); // Запоминаем текущее время
    blinkPeriod = 0;

    while (analogRead(photoresistorPin) < threshold)
    {
      blinkPeriod = millis() - startMillis;
    }
    if (blinkPeriod > period - 50 && blinkPeriod < period + 50) // если в пределах +- 50мс
    {
      step = 2;
      success();
    }
  }
}

void success() // Анимация на 7-сегментном индикаторе
{
  Serial.println("Success!");
}

void fail()
{
  Serial.println("Good try!");
}

void lesson_2()
{
}
void lesson_3()
{
}

void displaymode()
{
  switch (mode)
  {
  case 0:

    break;
  }

  reg.update(); // обновить
}