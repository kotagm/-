#include <Servo.h>
#include "sonar.h"

// Порты сервомоторов:
const int pRM1 = 5;
const int pRM2 = 3;
const int pLM1 = 2;
const int pLM2 = 6;
const int pNk = 34;
//Порты УЗ-дальномера:
const int pTrig = 33;
const int pEcho = 32;
//Сервомоторы приводов:
Servo rM1; Servo rM2; //правая сторона
Servo lM1; Servo lM2; //левая сторона
Servo neck; //шея

//Скорость вращения (значения от 1 до 500):
int speed = 250;
//Дистанция:
int fDist = 0; //впереди
int lDist = 0; //слева
int rDist = 0; //справа
int maxD  = 400; //предельное значения дистанции для sonar.h

void setup() {
  Serial.begin(9600);
  Sonar_init(pTrig, pEcho);
  rM1.attach(pRM1);
  rM2.attach(pRM2);
  lM1.attach(pLM1);
  lM2.attach(pLM2);
  neck.attach(pNk);
  neck.write(90);
  delay(250);
}

void loop() {
  fDist = Sonar(maxD);
  if (fDist >= 50) {
    fwd(speed); delay(10);
  }
  else {
    stp(); delay(500);
    neck.write(180); delay(250); lDist = Sonar(maxD);
    neck.write(0);   delay(250); rDist = Sonar(maxD);
    if (lDist < rDist) {
      rgt(speed); delay(700); stp();
    } else {
      lft(speed); delay(700); stp();
    }
  }
  neck.write(90);
  delay(250);
}

void stp() {
  rM1.writeMicroseconds(1500);
  rM2.writeMicroseconds(1500);
  lM1.writeMicroseconds(1500);
  lM2.writeMicroseconds(1500);
}

void fwd(int spd) {
  int s1 = 1500 - spd;
  int s2 = 1500 + spd;
  rM1.writeMicroseconds(s1);
  rM2.writeMicroseconds(s1);
  lM1.writeMicroseconds(s2);
  lM2.writeMicroseconds(s2);
}

void bck(int spd) {
  int s2 = 1500 - spd;
  int s1 = 1500 + spd;
  rM1.writeMicroseconds(s1);
  rM2.writeMicroseconds(s1);
  lM1.writeMicroseconds(s2);
  lM2.writeMicroseconds(s2);
}

void rgt(int spd) {
  int s1 = 1500 + spd;
  int s2 = 1500 + spd;
  rM1.writeMicroseconds(s1);
  rM2.writeMicroseconds(s1);
  lM1.writeMicroseconds(s2);
  lM2.writeMicroseconds(s2);
}

void lft(int spd) {
  int s1 = 1500 - spd;
  int s2 = 1500 - spd;
  rM1.writeMicroseconds(s1);
  rM2.writeMicroseconds(s1);
  lM1.writeMicroseconds(s2);
  lM2.writeMicroseconds(s2);
}