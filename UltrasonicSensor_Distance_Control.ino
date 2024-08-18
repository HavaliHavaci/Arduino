// Pin tanımları
const int trigPin = 5;   // HC-SR04'ün TRIG pininin bağlı olduğu pin
const int echoPin = 4;  // HC-SR04'ün ECHO pininin bağlı olduğu pin

long duration;           // Ses dalgasının geri dönüş süresi
int distance;            // Mesafe

void setup() {
  Serial.begin(115200); // Seri haberleşmeyi başlat
  pinMode(trigPin, OUTPUT); // TRIG pinini çıkış olarak ayarla
  pinMode(echoPin, INPUT);  // ECHO pinini giriş olarak ayarla
}

void loop() {
  // Ultrasonik sensör ile mesafeyi ölç
  digitalWrite(trigPin, LOW); // TRIG pinini LOW yap
  delayMicroseconds(2);       // 2 mikro saniye bekle
  digitalWrite(trigPin, HIGH); // TRIG pinini HIGH yap
  delayMicroseconds(10);      // 10 mikro saniye bekle
  digitalWrite(trigPin, LOW); // TRIG pinini LOW yap

  duration = pulseIn(echoPin, HIGH); // ECHO pininden HIGH durumundaki pulse süresini oku
  distance = duration * 0.0344 / 2;  // Mesafeyi cm cinsinden hesapla

  // Mesafeyi seri monitörde yazdır
  Serial.print("Mesafe = ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // 500 ms bekle
}
