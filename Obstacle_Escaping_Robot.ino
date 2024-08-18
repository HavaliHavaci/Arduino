#define echo 4
#define trig 5
#define in1 33
#define in2 32
#define ena 14
#define in3 22
#define in4 23
#define enb 18

long duration;       // Ses dalgasının geri dönüş süresi
int distance;        // Mesafe

void setup() 
{
  Serial.begin(115200);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
}

void loop() 
{
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH); // ECHO pininden HIGH durumundaki pulse süresini oku
  distance = duration / 29.1 / 2;  // Mesafeyi cm cinsinden hesapla

  // Mesafeyi seri monitörde yazdır
  Serial.print("Mesafe = ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);

  if(distance <10)
  {
    back();
    delay(500);
    right();
    delay(500);
  }
  
  else
  {
    forward();
  }


}

void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(ena, 20);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enb, 20);

}

void back()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(ena, 1200);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enb, 120);

}

void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(ena, 120);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enb, 120);

}



  
