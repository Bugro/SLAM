const int pwmRight = 9;
const int pwmLeft = 10;
const int enable = 2;
const int codLeftA = 18;
const int codLeftB = 19;
const int codRightA = 20;
const int codRightB = 21;
int rCounter = 0;

volatile boolean moveL;
volatile boolean upL;
volatile boolean moveR;
volatile boolean upR;

int valL = 0;
int valR = 0;

void leftInterrupt()
{
  if (digitalRead(codLeftA))
    upL = digitalRead(codLeftB));
  else 
    upL = digitalRead(codLeftB);
  moveL = true;
}

void rightInterrupt()
{
  if (digitalRead(codRightA))
    upR = digitalRead(codRightB));
  else 
    upR = digitalRead(codRightB);
  moveR = true;
}

void setup()
{
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  
  pinMode(pwmRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(codLeftA, INPUT);
  pinMode(codLeftB, INPUT);
  pinMode(codRightA, INPUT);
  pinMode(codRightB, INPUT);
  
  digitalWrite(enable,LOW);

  attachInterrupt(0, leftInterrupt, FALLING);
  attachInterrupt(1, rightInterrupt, FALLING);

  Serial.begin(9600);

  //Serial.println("You are now connected to the robot !");
}

void loop()
{
  if (moveL)  {
    if (upL)
      valL++;
    else
      valL--;
    moveL= false;         
    Serial.println (valL);
  }

  if (moveR)  {
    if (upR)
      valR++;
    else
      valR--;
    moveR= false;         
    Serial.println (valR);
  }
  
  char cmd = 0;
  int right = 125;
  int left = 125;

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
