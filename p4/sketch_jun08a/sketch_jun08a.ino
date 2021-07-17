void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(3) == HIGH)
    {delay(3000);Serial.println("M");delay(10000);}
}
