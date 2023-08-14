const int photoresistorPin = A0;   // Пин для фоторезистора
const int ledPin = 13;             // Пин для Сигнального светодиода
const int threshold = 100;         // Пороговое значение для определения мигания
const int period = 1000;	 //Измеряемый период

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(photoresistorPin); // Считываем значение с фоторезистора

  if (lightValue > threshold) {
    int startMillis = millis();  // Запоминаем текущее время
    int blinkPeriod = 0;

    while (digitalRead(photoresistorPin) > threshold) {
      // Ждем, пока светодиод выключится
      blinkPeriod = millis() - startMillis;
    }

    if (blinkPeriod > period-50 && blinkPeriod < period+50   ) {
      Serial.println("Период мигания составляет 1 секунду.");

    }
  }
}
