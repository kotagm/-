//����� ��� ���:
int Trig, Echo;

Sonar_init(int Tr, int Ec) {
  Trig = Tr;
  Echo = Ec;
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);  
}

int Sonar(unsigned long Limit) {
  int Long_cm;
  unsigned long Lim = Limit*58;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  Long_cm = int(pulseIn(Echo, HIGH, Lim)/58);

  if (Long_cm == 0) return int(Limit);
  return Long_cm;
}