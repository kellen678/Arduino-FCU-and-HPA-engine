int Recived = 0;
String snum1 ;
int Dwell = 0;
String snum2 ;
int FireRate = 0;
String snum3 ;
int Burst = 0;
int mode = 1;
const int Fire = 5;
const int Bullet = 8;
float FRDelay = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(Fire, INPUT_PULLUP);
  pinMode(Bullet, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    Recived = Serial.read();
  }
  if (Recived == 's') {
    mode = 1;
  }
  else if (Recived == 'b') {
    mode = 2;
  }
  else if (Recived == 'f') {
    mode = 3;
  }
  else if (Recived == 'q') {
    delay(500);
    snum1 = Serial.readString();
    Dwell = snum1.toInt();
  }
  else if (Recived == 'w') {
    delay(500);
    snum2 = Serial.readString();
    FireRate = snum2.toInt();
  }
  else if (Recived == 'e') {
    delay(500);
    snum3 = Serial.readString();
    Burst = snum3.toInt();
  }

  if (digitalRead(Fire) == HIGH) {
    if (mode == 1) {
      digitalWrite(Bullet, HIGH);
      delay(Dwell);
      digitalWrite(Bullet, LOW);
      while (digitalRead(Fire) == HIGH) {}
    }
    else if (mode == 2) {
      for (int i = 0; i < Burst; i++) {
        digitalWrite(Bullet, HIGH);
        delay(Dwell);
        digitalWrite(Bullet, LOW);
        delay(Dwell / 2);
      }
    }
    else if (mode == 3) {
      FRDelay = 1000.0 / FireRate;
      while (digitalRead(Fire) == HIGH) {
        digitalWrite(Bullet, HIGH);
        delay(FRDelay);
        digitalWrite(Bullet, LOW);
        delay(FRDelay / 2.0);
      }
    }
  }
}
