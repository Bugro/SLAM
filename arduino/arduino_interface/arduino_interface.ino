const int pwmRight = 9;
const int pwmLeft = 10;
const int enable = 2;
const int codLeftA = 18;
const int codLeftB = 19;
const int codRightA = 20;
const int codRightB = 21;
int rCounter = 0;

int valL = 0;
int valR = 0;

unsigned long beginTime = 0;
const unsigned long endTime = 50;


void leftInterrupt()
{
  if (digitalRead(codLeftB))
    valL++;
  else
    valL--;
}

void rightInterrupt()
{
  if (digitalRead(codRightB))
    valR--;
  else
    valR++;
}

void setup()
{
  TCCR2B = (TCCR2B & 0b11111000) | 0x01;
  
  pinMode(pwmRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(codLeftA, INPUT);
  pinMode(codLeftB, INPUT);
  pinMode(codRightA, INPUT);
  pinMode(codRightB, INPUT);
  
  digitalWrite(enable,LOW);

  attachInterrupt(digitalPinToInterrupt(codLeftA), leftInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(codRightA), rightInterrupt, RISING);

  Serial.begin(9600);

  //Serial.println("You are now connected to the robot !");
}

void loop()
{
  beginTime = millis();

  
  //Envoie des codeurs
  Serial.println (250);
  Serial.println (251);
  Serial.println (valR);
  Serial.println (valL);
  valR = 0;
  valL = 0;


  //Réception des pwm
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
  
  while(millis() - beginTime < endTime);
  
  //delay(10);
}
