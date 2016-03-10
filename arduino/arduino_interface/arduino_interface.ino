const int pwmRight = 9;
const int pwmLeft = 10;
const int enable = 2;
int rCounter = 0;

void setup()
{
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  
  pinMode(pwmRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);
  pinMode(enable, OUTPUT);
  
  digitalWrite(enable,LOW);

  Serial.begin(9600);

  //Serial.println("You are now connected to the robot !");
}

void loop()
{
  char cmd = 0;
  int right = 125;
  int left = 125;
  
  while (Serial.available() == 0);

  while (Serial.available() > 0) {

    cmd = Serial.read();

    switch (rCounter) {
      case 0:
        if(cmd == 12){
          rCounter++;
        }
        else {
          rCounter = 0;
        }
        break;

      case 1:
        if(cmd == 13){
          rCounter++;
        }
        else {
          rCounter = 0;
        }
        break;

      case 2:
        rCounter++;
        right = cmd;
        
        digitalWrite(enable,HIGH);
        analogWrite(pwmRight, 255 - right);
        
        break;

      case 3:
        rCounter = 0;
        left = cmd;

        digitalWrite(enable,HIGH);
        analogWrite(pwmLeft, 255 - left);
        
        break;
        
      default:
        rCounter = 0;
      break;
    }
  }
  //delay(10);
}
