int sensorPin = 15;       // CNY70 sensörünün bağlı olduğu pin
int ledPin = 13;          // LED'in bağlı olduğu pin (genellikle 13. pin LED için kullanılır)
int sensorValue = 0;      // Sensörden okunan değer
int threshold = 900;      // Eşik değeri, sensör değerinin bu değeri geçip geçmediğini kontrol eder

void setup() {
  Serial.begin(9600);   // Seri haberleşmeyi başlat
  pinMode(ledPin, OUTPUT); // LED pinini çıkış olarak ayarla
}

void loop() {
  sensorValue = analogRead(sensorPin); // Sensör değerini oku
  Serial.print("Sensor Degeri = ");
  Serial.println(sensorValue);

  // Sensör değerini eşik değeri ile karşılaştır
  if (sensorValue > threshold) {
    digitalWrite(ledPin, HIGH); // Eşik değerini geçtiyse LED'i yak
  } else {
    digitalWrite(ledPin, LOW);  // Eşik değerini geçmediyse LED'i söndür
  }

  delay(250); // 250ms bekle
}
