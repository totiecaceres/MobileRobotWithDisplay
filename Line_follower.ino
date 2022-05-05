
int TRIGPIN=2;
int ECHOPIN=3;
int irleft=5;
int irright=6;
float DISTANCE;
float DURATION;
int MOTOR_1_DIRECTION_A=9;
int MOTOR_1_DIRECTION_B=8;
int MOTOR_2_DIRECTION_A=11;
int MOTOR_2_DIRECTION_B=10;
int MOTOR_1_SPEED=A3;
int MOTOR_2_SPEED=A4;
int LEFT_LINE_SENSOR=A2;
int CENTER_LINE_SENSOR=A1;
int RIGHT_LINE_SENSOR=A0;
int LINER=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIGPIN,OUTPUT);
  pinMode(ECHOPIN,INPUT);
  pinMode(MOTOR_1_DIRECTION_A,OUTPUT);
  pinMode(MOTOR_1_DIRECTION_B,OUTPUT);
  pinMode(MOTOR_2_DIRECTION_A,OUTPUT);
  pinMode(MOTOR_2_DIRECTION_B,OUTPUT);
  pinMode(MOTOR_1_SPEED,OUTPUT);
  pinMode(MOTOR_2_SPEED,OUTPUT);

  pinMode(LEFT_LINE_SENSOR,INPUT);
  pinMode(CENTER_LINE_SENSOR,INPUT);
  pinMode(RIGHT_LINE_SENSOR,INPUT);
}
int ping(){
  digitalWrite(TRIGPIN,LOW);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN,LOW);
  DURATION=pulseIn(ECHOPIN,HIGH);
  DISTANCE=DURATION*0.034/2;
  return(DISTANCE);
}
void loop() {
  // put your main code here, to run repeatedly:
  int LINE_SENSE_LEFT =      digitalRead(LEFT_LINE_SENSOR);
  int LINE_SENSE_CENTER =    digitalRead(CENTER_LINE_SENSOR);
  int LINE_SENSE_RIGHT =     digitalRead(RIGHT_LINE_SENSOR);
  float VALUE;
  VALUE=ping();
  if(LINE_SENSE_LEFT==HIGH || LINE_SENSE_CENTER==HIGH || LINE_SENSE_RIGHT==HIGH)
  {
    LINER=LINER-1;
  }
  while((VALUE <= 70 && VALUE > 0) && LINER == 1) 
  {
    ATTACK(); 
    delay(70);
    break; 
  }
  if((digitalRead(irright)==LOW) && (digitalRead(irleft)== HIGH)){
      SPIN_LEFT();
      //break;
  }
   if((digitalRead(irright)==LOW) && (digitalRead(irleft)== HIGH)){
      SPIN_LEFT();
      //break;
  }
   while(LINER==1 && VALUE>70){
    SPIN_LEFT();
    //delay(10);
    break;
  }
  if(LINER == 0)
  {
    GO_BACKWARD();
    delay(500);
  }
  LINER = 1;
}


void ATTACK()
{
  digitalWrite(MOTOR_1_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_1_DIRECTION_B,LOW);
  digitalWrite(MOTOR_2_DIRECTION_B,LOW);
  analogWrite(MOTOR_1_SPEED,255);
  analogWrite(MOTOR_2_SPEED,255);

}

void GO_FORWARD_SLOW()
{
  digitalWrite(MOTOR_1_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_1_DIRECTION_B,LOW);
  digitalWrite(MOTOR_2_DIRECTION_B,LOW);
  analogWrite(MOTOR_1_SPEED,180);
  analogWrite(MOTOR_2_SPEED,180);
}

void GO_BACKWARD()
{
  digitalWrite(MOTOR_1_DIRECTION_A,LOW);
  digitalWrite(MOTOR_2_DIRECTION_A,LOW);
  digitalWrite(MOTOR_1_DIRECTION_B,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_B,HIGH);
  analogWrite(MOTOR_1_SPEED,180);
  analogWrite(MOTOR_2_SPEED,180);
}

void STOP()
{
  
  analogWrite(MOTOR_1_SPEED,0);
  analogWrite(MOTOR_2_SPEED,0); 
}

void SPIN_LEFT()
{
  digitalWrite(MOTOR_1_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_A,LOW);
  digitalWrite(MOTOR_1_DIRECTION_B,LOW);
  digitalWrite(MOTOR_2_DIRECTION_B,HIGH);
  analogWrite(MOTOR_1_SPEED,255);
  analogWrite(MOTOR_2_SPEED,255);
}

void SPIN_RIGHT()
{
  digitalWrite(MOTOR_1_DIRECTION_A,LOW);
  digitalWrite(MOTOR_2_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_1_DIRECTION_B,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_B,LOW);
  analogWrite(MOTOR_1_SPEED,255);
  analogWrite(MOTOR_2_SPEED,255);
}

