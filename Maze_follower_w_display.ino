#include<Servo.h>
Servo myservo;

// INITIALIZATION:
const int NUM_ROWS = 9;
const int NUM_COLS = 8;

int latchPin2 = 5;
int dataPin2 = 6;
int clockPin2 = 7;

const int latchPin = A0;
const int dataPin = A1;
const int clockPin = A2;

int gdataset[30][9] = { {31,63,108,204,204,108,63,31,0}, {63,108,204,204,108,63,31,0,0},
  {108,204,204,108,63,31,0,0,0}, {204,204,108,63,31,0,0,31,0},
  {204,108,63,31,0,0,31,63,0}, {108,63,31,0,0,31,63,108,0},
  {63,31,0,0,31,63,108,204,0}, {31,0,0,31,63,108,204,204,0},
  {0,0,31,63,108,204,204,108,0}, {0,31,63,108,204,204,108,63,0},

  {31,63,108,204,204,108,63,31,0}, {63,108,204,204,108,63,31,0,0},
  {108,204,204,108,63,31,0,0,0}, {204,204,108,63,31,0,0,31,0},
  {204,108,63,31,0,0,31,63,0}, {108,63,31,0,0,31,63,108,0},
  {63,31,0,0,31,63,108,204,0}, {31,0,0,31,63,108,204,204,0},
  {0,0,31,63,108,204,204,108,0}, {0,31,63,108,204,204,108,63,0},

  {31,63,108,204,204,108,63,31,0}, {63,108,204,204,108,63,31,0,0},
  {108,204,204,108,63,31,0,0,0}, {204,204,108,63,31,0,0,31,0},
  {204,108,63,31,0,0,31,63,0}, {108,63,31,0,0,31,63,108,0},
  {63,31,0,0,31,63,108,204,0}, {31,0,0,31,63,108,204,204,0},
  {0,0,31,63,108,204,204,108,0}, {0,31,63,108,204,204,108,63,0}
  
};
//int gdataset[10][8] = { {114,251,219,219,219,219,255,126},
//{110,254,219,219,219,219,254,110},
//{192,193,195,198,204,216,240,224},
//{126,255,219,219,219,219,223,78},
//{114,251,219,219,219,219,223,78},
//{240,248,24,24,24,255,255,24},
//{66,195,219,219,219,219,255,126},
//{78,223,219,219,219,219,219,114},
//{19,51,99,255,255,3,3,3},
//{126,255,193,193,193,193,255,126} 
//};
int data7seg[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 103};
int led[10] = {1, 2, 4, 8, 16, 32, 64, 128,0,0};
//int led[10] = {128, 64, 32, 16, 8, 4, 2, 1, 0,128};

int servopin=4;
int trigpin=2;
int echopin=3;
float distance;
float duration;

// INITIALIZATION:
int MOTOR_1_DIRECTION_A =  A3;
int MOTOR_1_DIRECTION_B =  8;                // Motor control HIGH = FWD, LOW = BWD
int MOTOR_1_SPEED =      9;                // Speed input ( digitalWrite  LOW or 0 ) means fullspeed.
int MOTOR_2_SPEED =      10;               // Speed input ( digitalWrite  HIGH or 1 ) means fullstop.
int MOTOR_2_DIRECTION_A =  11;               // Motor control HIGH = FWD, LOW = BWD
int MOTOR_2_DIRECTION_B =  A4;

int NORMAL_SPEED = 0;                    // 255 means fullstop on analog read,0 means fullspeed,feel free to play analog values from 0-255
int NORMAL_SPEED2 = 255;
int FULL_STOP = 255;


// INPUTS AND OUTPUTS
void setup() 
{                
  Serial.begin(9600);

  // DEFAULT PINS OF THE MOTOR DRIVER (8,9,10,11)
  pinMode(MOTOR_1_DIRECTION_A, OUTPUT);
  pinMode(MOTOR_1_DIRECTION_B, OUTPUT);       
  pinMode(MOTOR_1_SPEED, OUTPUT);
  pinMode(MOTOR_2_SPEED, OUTPUT);
  pinMode(MOTOR_2_DIRECTION_A, OUTPUT);
  pinMode(MOTOR_2_DIRECTION_B, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);  
  pinMode(clockPin2, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(servopin,OUTPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  myservo.attach(servopin); 
}
int ping()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  duration= pulseIn(echopin,HIGH);
  distance= duration*0.034/2;
  return(distance);
}
int off=0;
int l = 0;
// MAIN PROGRAM
void loop()                     
{
  if(off==1){
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin2, clockPin2, MSBFIRST, 0);
    digitalWrite(latchPin2, HIGH);
    digitalWrite(latchPin2, LOW);
    STOP();
    delay(100);}
  else{
  for(int i=0;i<=9;i++){
    for(int j=0;j<=9;j++){
      //for(int k=0; k<=7; k++){
                     
          myservo.write(90);
          float value;
          value=ping();
          Serial.println(value);
          delay(10);
          
          if(value>=35)
          {
            GO_FORWARD();
            delay(100);
            int l = (10*i) + j;
             if(l<=29){displayPixels(l,30);}
             else if(l<=59){displayPixels(l-30,30);}
             else if(l<=89){displayPixels(l-60,30);}
             else if(l<=99){displayPixels(l-90,40);}
             
             disp7segled(i,j,j);
          }
          else if(value<35 )
          {
            STOP();
            //delay(100);
            GO_BACKWARD();
            //delay(50);
            DO_OBSTACLE_AVOIDING();
            delay(400);
            int l = (10*i) + j;
             if(l<=29){displayPixels(l,30);}
             else if(l<=59){displayPixels(l-30,30);}
             else if(l<=89){displayPixels(l-60,30);}
             else if(l<=99){displayPixels(l-90,40);}
             
             disp7segled(i,j,j);
          }
          myservo.write(90);
      //}
     }
     if(i>=9){off=1;}
  }
  }

  
}

void disp7segled(int val1,int val2,int val3){
   int digit_tens = data7seg[val1];
   int digit_ones = data7seg[val2];
   int ledcur = led[val3];
    shiftOut(dataPin, clockPin, MSBFIRST, ledcur);
    shiftOut(dataPin, clockPin, MSBFIRST, digit_tens);
    shiftOut(dataPin, clockPin, MSBFIRST, digit_ones);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    //delayMicroseconds(10);    
}

void displayPixels(int val,int pdelay){
 for(int m=0; m<pdelay; m++){
   for(int row=0; row<NUM_ROWS; row++){
   int gcur = gdataset[val][row];
    shiftOut(dataPin2, clockPin2, MSBFIRST, 255-gcur);
    shiftOut(dataPin2, clockPin2, MSBFIRST, B00000001 << row  );
    digitalWrite(latchPin2, HIGH);
    digitalWrite(latchPin2, LOW);
    delayMicroseconds(1000);    
    }
 }
}
void DO_OBSTACLE_AVOIDING ()
{
  int OBSTACLE_ON_LEFT;
  int OBSTACLE_ON_RIGHT;
  myservo.write(10);
  delay(500);
  OBSTACLE_ON_LEFT = ping();
  myservo.write(170);
  delay(500);
  OBSTACLE_ON_RIGHT = ping();
  if(OBSTACLE_ON_LEFT > OBSTACLE_ON_RIGHT)
  {
    SPIN_RIGHT();
    //delay(100);     
  }
  else if(OBSTACLE_ON_LEFT < OBSTACLE_ON_RIGHT)
  {
    SPIN_LEFT();
    //delay(100);    
  }
  else if(OBSTACLE_ON_LEFT = OBSTACLE_ON_RIGHT)
  {
    GO_BACKWARD();
    //delay(100);
    SPIN_RIGHT();
    //delay(100);
  }
}
// MOTOR CONTROL FUNCTION
void GO_BACKWARD()    
{
  digitalWrite(MOTOR_1_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_1_DIRECTION_B,LOW);
  digitalWrite(MOTOR_2_DIRECTION_B,LOW);
  analogWrite(MOTOR_1_SPEED,NORMAL_SPEED2);
  analogWrite(MOTOR_2_SPEED,NORMAL_SPEED2);
}

void STOP()    
{
  analogWrite(MOTOR_1_SPEED,0);
  analogWrite(MOTOR_2_SPEED,0);
}

void GO_FORWARD()    
{
  digitalWrite(MOTOR_1_DIRECTION_A,LOW);
  digitalWrite(MOTOR_2_DIRECTION_A,LOW);
  digitalWrite(MOTOR_1_DIRECTION_B,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_B,HIGH);
  analogWrite(MOTOR_1_SPEED,NORMAL_SPEED2);
  analogWrite(MOTOR_2_SPEED,NORMAL_SPEED2);
}

void SPIN_RIGHT()    
{
  digitalWrite(MOTOR_1_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_A,LOW);
  digitalWrite(MOTOR_1_DIRECTION_B,LOW);
  digitalWrite(MOTOR_2_DIRECTION_B,HIGH);
  analogWrite(MOTOR_1_SPEED,0);
  analogWrite(MOTOR_2_SPEED,NORMAL_SPEED2);
}

void SPIN_LEFT()    
{
  digitalWrite(MOTOR_1_DIRECTION_A,LOW);
  digitalWrite(MOTOR_2_DIRECTION_A,HIGH);
  digitalWrite(MOTOR_1_DIRECTION_B,HIGH);
  digitalWrite(MOTOR_2_DIRECTION_B,LOW);
  analogWrite(MOTOR_1_SPEED,NORMAL_SPEED2);
  analogWrite(MOTOR_2_SPEED,0);
}
