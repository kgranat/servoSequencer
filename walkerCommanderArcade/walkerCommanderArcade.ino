#include <ServoEx.h>

#include <Commander.h>


#define BASE_MIN      600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400    //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN  600
#define SHOULDER_MAX  2400
#define ELBOW_MIN     600
#define ELBOW_MAX     2400
#define WRIST_MIN     600
#define WRIST_MAX     2400 
  #define GRIPPER_MIN   900    //full counterclockwise for 9g servo
  #define GRIPPER_MAX   2100   //full clockwise for 9g servo


const int L_LEG_ANKLE_INDEX = 0;
const int R_LEG_ANKLE_INDEX = 1;
const int L_LEG_KNEE_INDEX = 2;
const int R_LEG_KNEE_INDEX = 3;
const int L_LEG_HIP_INDEX = 4;
const int R_LEG_HIP_INDEX = 5;
const int MIDDLE_SERVO_INDEX = 6;


const int NUM_SERVOS = 7;
const int NUM_SEQEUENCES = 11;

int servoPins[NUM_SERVOS] = {6,11,5,10,3,9,12};

//int servoErrors[NUM_SERVOS] = {0,0,0,0,00,00,00};
int servoErrors[NUM_SERVOS] = {27,-12,122,29,-100,62,30}; //drnk brd
//int servoErrors[NUM_SERVOS] = {0,-200,-100,-100,-100,100,-100};
//int servoValues[NUM_SERVOS] = {900,2100,1300,1700,2100,900,1500};
int servoValues[NUM_SERVOS] = {700,2368,1060,1928,2127,870,1476};
//int servoValuesIdeal[NUM_SERVOS] = {900,2100,1300,1700,2100,900,1500};



const int deltaTimeTurn = 250;

const int turnSpeeds[NUM_SEQEUENCES]  = {deltaTimeTurn, (deltaTimeTurn), deltaTimeTurn, deltaTimeTurn, 5 * deltaTimeTurn , 2 * deltaTimeTurn, 2 * deltaTimeTurn};

const int turnLeft[7][NUM_SERVOS] =
{
  {929,2157,1296,1662,2144,895,1472},
  {652,2400,1337,1675,1573,1437,978},
  {656,2400,1124,1828,1009,1928,1082},
  {656,2400,1126,1826,1009,1926,2019},
  {656,2400,1124,1826,2065,932,1458},
  {834,2283,1164,1773,2141,835,1472},
  {929,2157,1296,1662,2144,895,1472}
};

const int turnRight[7][NUM_SERVOS] =
{
  {929,2157,1296,1662,2144,895,1472},
  {652,2400,1337,1675,1573,1437,2019},
  {656,2400,1124,1828,1009,1928,2019},
  {656,2400,1126,1826,1009,1926,978},
  {656,2400,1124,1826,2065,932,1458},
  {834,2283,1164,1773,2141,835,1472},
  {929,2157,1296,1662,2144,895,1472}
};


const int deltaTime = 200;
//walk forward
const int forwardSpeed[NUM_SEQEUENCES]  = {deltaTime, (deltaTime + 1000)/2, deltaTime, deltaTime, deltaTime + 1000, deltaTime, deltaTime, deltaTime,     deltaTime, deltaTime, deltaTime/2};

//walk back
const int backSpeed[NUM_SEQEUENCES]  = {deltaTime,  (deltaTime + 1000)/2 ,deltaTime,deltaTime,  (deltaTime + 1000) , deltaTime, deltaTime, (deltaTime + 1000)/2,    deltaTime, deltaTime, deltaTime};


const int walkForward[8][NUM_SERVOS] =
{
  {700,2368,1060,1928,2127,870,1476},
  {702,2368,1060,1914,2129,870,939},
  {758,2398,1096,2400,2292,885,937},
  {983,2333,1314,1771,2294,886,939},
  {981,2334,1310,1768,2290,885,2031},
  {600,2310,615,1768,2290,886,2031},
  {600,2308,1231,1768,1914,881,2031},
  {700,2368,1060,1928,2127,870,1476}
};


const int walkBackward[8][NUM_SERVOS] =
{
  {700,2368,1060,1928,2127,870,1476},
  {600,2308,1231,1768,1914,881,2031},
  {600,2310,615,1768,2290,886,2031},
  {981,2334,1310,1768,2290,885,2031},
  {983,2333,1314,1771,2294,886,939},
  {758,2398,1096,2400,2292,885,937},
  {702,2368,1060,1914,2129,870,939},  
  {700,2368,1060,1928,2127,870,1476}
};



ServoEx    gerwalkServo[7];

int currentSequence = 0;



Commander command = Commander();  //start commander object

void setup() {
  // put your setup code here, to run once:

  
  // Attach servo and set limits

  for (int i = 0; i<NUM_SERVOS; i++)
  {
    gerwalkServo[i].attach(servoPins[i]);

  }

  pinMode(2, INPUT);
  pinMode(4, INPUT);
  
Serial.begin(38400); 

    
  SetServo(1000);

//  delay(5000);
//  while(1);
  
}

void loop() {
  // put your main code here, to run repeatedly:

//
//  playSequence(walkForward, forwardSpeed, 8);
//
//  delay(2000);
//  playSequence(walkBackward, backSpeed, 8);
//
//  delay(2000);
//  playSequence(turnLeft, turnSpeeds, 7);
//
//  delay(2000);
//  playSequence(turnRight, turnSpeeds, 7);
//  delay(2000);
//
//  if(digitalRead(4) == HIGH)
//  {
//    playSequence
//  }


if(command.ReadMsgs() > 0)
   {
     
     if((command.lookV) > 25 )
      {
         playSequence(walkForward, forwardSpeed, 8);
        while(Serial.available())
        {
          Serial.read();
        }
      }
      else if( (command.lookV < -25) )
      {
         playSequence(walkBackward, backSpeed, 8);
        while(Serial.available())
        {
          Serial.read();
        }
      }


   if((command.lookV) > 25 )
      {
        playSequence(turnRight, turnSpeeds, 7);
        while(Serial.available())
        {
          Serial.read();
        }
      }
      else if( (command.lookV < -25) )
      {
        playSequence(turnLeft, turnSpeeds, 7);
        while(Serial.available())
        {
          Serial.read();
        }
      }


     if((command.buttons&BUT_LT) && (command.buttons&BUT_RT))
     {
      
     }

     else if(command.buttons&BUT_LT)
     { 
      
         playSequence(walkForward, forwardSpeed, 8);
    
     }


     else if(command.buttons&BUT_RT)
     { 
    

     }



    
   }


  
}






void playSequence(const int sequence[][NUM_SERVOS], const int speeds[],  int numSequence)
{
  //Serial.println("PLAY");
  for(int i = 0; i <numSequence ; i++)
  {
    ServoGroupMove.start();
    for(int j = 0; j < NUM_SERVOS; j++)
    {
      gerwalkServo[j].writeMicroseconds(sequence[i][j] + servoErrors[j]);
    } 
    ServoGroupMove.commit(speeds[i]);
    delay(speeds[i]);
      

   
    }
}

void SetServo(unsigned int DeltaTime)
{
  ServoGroupMove.start();
  for(int i = 0; i < NUM_SERVOS; i++)
    {
      gerwalkServo[i].writeMicroseconds(servoValues[i] + servoErrors[i]);
    }

  ServoGroupMove.commit(DeltaTime);
  delay(DeltaTime);
}







