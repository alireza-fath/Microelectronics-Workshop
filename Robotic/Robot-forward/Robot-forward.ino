const int standby = 3;
const int right_power = 5;
const int right_direction = 8;
const int left_power = 6;
const int left_direction = 7;

void setup() {
  // put your setup code here, to run once:

pinMode(standby, OUTPUT);
digitalWrite(standby, 1);
pinMode(right_power, OUTPUT);
pinMode(right_direction, OUTPUT);
pinMode(left_power, OUTPUT);
pinMode(left_direction, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(right_power,100);
digitalWrite(right_direction,1);
analogWrite(left_power,100);
digitalWrite(left_direction,1);
delay(1000);
analogWrite(right_power,0);
analogWrite(left_power,0);
delay(1000);
analogWrite(right_power,100);
digitalWrite(right_direction,0);
analogWrite(left_power,100);
digitalWrite(left_direction,0);
delay(1000);
analogWrite(right_power,0);
analogWrite(left_power,0);
delay(1000);
}
