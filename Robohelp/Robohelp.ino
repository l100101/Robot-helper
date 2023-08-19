#include <GyverHC595.h> //74hc595 lib
#include <GyverButton.h>//для кнопок

//#include <

//GyverHC595<2, HC_SPI, 8000000> reg(10); // аппаратный SPI, кастомная скорость
//GyverHC595<2, HC_PINS> reg(10, 11, 13); // программный SPI (bit bang)

GButton butt1(BTN_PIN);

const int photoresistorPin = A0;   // Пин для фоторезистора
const int ledPin = 13;             // Пин для Сигнального светодиода
const int buzzer_pin = 5;          //Пин для пищалки
const int btn_pin 3   // кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)

const int threshold = 100;         // Пороговое значение для определения мигания
const int period = 1000;	 //Измеряемый период

byte mode = 0;  //режим работы

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
  if (butt1.isSingle()) mode++;     // проверка на один клик

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


void lesson_1()
{
  int lightValue = analogRead(photoresistorPin); // Считываем значение с фоторезистора

  if (lightValue > threshold) {
    int startMillis = millis();  // Запоминаем текущее время
    int blinkPeriod = 0;

    while (digitalRead(photoresistorPin) > threshold) {
      // Ждем, пока светодиод выключится
      blinkPeriod = millis() - startMillis;
    }

    if (blinkPeriod > period - 50 && blinkPeriod < period + 50   ) {
      //Serial.println("Период мигания составляет 1 секунду.");
      success();//функция, сигнализирующая об успехе
    }
    else {
      fail();//функция, сигнализирующая об ошибке
    }
  }
}

void success()
{

}

void fail()
{

}

void lesson_2()
{}
void lesson_3()
{}
