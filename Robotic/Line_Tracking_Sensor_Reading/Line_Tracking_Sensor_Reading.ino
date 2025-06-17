const int leftIRpin= A2;
const int middleIRpin = A1;
const int rightIRpin = A0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  delay(50);
  // put your main code here, to run repeatedly:
  int L_IR = analogRead(leftIRpin);
  int R_IR = analogRead(rightIRpin);
  int M_IR = analogRead(middleIRpin);

Serial.print("Left:");
Serial.print(L_IR);
Serial.print("   ||   Middle:");
Serial.print(M_IR);
Serial.print("   ||   Right:");
Serial.println(R_IR);
}
