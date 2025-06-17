const int standby = 3;
const int right_power = 5;
const int right_direction = 8;
const int left_power = 6;
const int left_direction = 7;

void setup() {
  Serial.begin(9600);
pinMode(standby, OUTPUT);
digitalWrite(standby, 1);
pinMode(right_power, OUTPUT);
pinMode(right_direction, OUTPUT);
pinMode(left_power, OUTPUT);
pinMode(left_direction, OUTPUT);
}

void loop() {
  Event();
  delay(10);
}

void Event()
{
  int status = SerialPortDataAnalysis();
  if (status)
  {
    switch (status)
    {
      case 1: {
analogWrite(right_power,100);
digitalWrite(right_direction,1);
analogWrite(left_power,100);
digitalWrite(left_direction,1);
delay(1000);
analogWrite(right_power,0);
analogWrite(left_power,0);}; break;
      case 2: {
analogWrite(right_power,100);
digitalWrite(right_direction,0);
analogWrite(left_power,100);
digitalWrite(left_direction,0);
delay(1000);
analogWrite(right_power,0);
analogWrite(left_power,0);};;break;
      case 3: {
analogWrite(right_power,100);
digitalWrite(right_direction,1);
analogWrite(left_power,100);
digitalWrite(left_direction,0);
delay(1000);
analogWrite(right_power,0);
analogWrite(left_power,0);};; break;
      case 4: {
analogWrite(right_power,100);
digitalWrite(right_direction,0);
analogWrite(left_power,100);
digitalWrite(left_direction,1);
delay(1000);
analogWrite(right_power,0);
analogWrite(left_power,0);};; break;
      default: {
analogWrite(right_power,0);
analogWrite(left_power,0);
delay(1000);}; break;
    }
  }
}


int SerialPortDataAnalysis(void)
{
  String SerialPortData = "";
  uint8_t c = "";
  if (Serial.available() > 0)
  {
    while (c != '}' && Serial.available() > 0)
    {
      c = Serial.read();
      SerialPortData += (char)c;
    }
    if (c == '}')
    {
      delay(50);
      return atoi((char*)(SerialPortData.substring(1, SerialPortData.length() - 1).c_str()));
    }
  }
  else
  {
    return 0;
  }
}

uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}
