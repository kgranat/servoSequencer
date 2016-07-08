#include <ServoEx.h>
#include <Adafruit_NeoPixel.h> //neopixel library for neopixel ring


#define BASE_MIN      600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400    //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN  600
#define SHOULDER_MAX  2400
#define ELBOW_MIN     600
#define ELBOW_MAX     2400
#define WRIST_MIN     600
#define WRIST_MAX     2400 
//mins and maxes depending on gripper type
#if GRIPPER_TYPE == ROBOT_GEEK_9G_GRIPPER
  #define GRIPPER_MIN   900    //full counterclockwise for 9g servo
  #define GRIPPER_MAX   2100   //full clockwise for 9g servo
#elif GRIPPER_TYPE == ROBOT_GEEK_PARALLEL_GRIPPER
  #define GRIPPER_MIN   750    //fully closed
  #define GRIPPER_MAX   2400   //fully open
#endif


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


int neoPixelOn = -1;
int lastNeoPixelOn = -1;
//int sequencePositions[NUM_SEQEUENCES][NUM_SERVOS]  = {
//
//  //bad dxl
////{672,2357,1393,1583,1719,1286,1539},
////{673,2359,1393,1573,878,2070,1474},
////{651,2400,1034,1960,1161,1801,1543},
////{647,2400,1036,1960,1161,1801,944},
////{647,2400,1252,1766,1163,1801,946},
////{645,2396,1490,1565,1388,1564,918},
////{649,2400,1492,1564,1388,1564,1467},
////{753,2287,1161,1792,2132,895,1467},
////{753,2280,1159,1792,2134,890,1467},
////{753,2278,1161,1792,2134,888,1467},
////{744,2276,1161,1792,2130,890,1467}
//
//
//{666,2350,997,1968,2236,804,1474},
//{666,2350,997,1968,2232,809,1200},
//{1075,2398,1379,1722,2398,921,1200},
//
//{666,2350,997,1968,2236,804,1474},
//{666,2350,997,1968,2232,809,1200},
//{1075,2398,1379,1722,2398,921,1200},
//
//{666,2350,997,1968,2236,804,1474},
//{666,2350,997,1968,2232,809,1200},
//{1075,2398,1379,1722,2398,921,1200},
//
//{666,2350,997,1968,2236,804,1474},
//{666,2350,997,1968,2232,809,1200},
//
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0},
////{0,0,0,0,0,0,0}
//
//  
//};





int sequencePositions[NUM_SEQEUENCES][NUM_SERVOS] =
{
{700,2368,1060,1928,2127,870,1476},
{702,2368,1060,1914,2129,870,939},
{758,2398,1096,2400,2292,885,937},
{983,2333,1314,1771,2294,886,939},
{981,2334,1310,1768,2290,885,2031},
{600,2310,615,1768,2290,886,2031},
{600,2308,1231,1768,1914,881,2031},
{700,2368,1060,1928,2127,870,1476},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0}

};

//turn
int sequencePositionsBack[NUM_SEQEUENCES][NUM_SERVOS] ;

//int sequencePositionsBack[NUM_SEQEUENCES][NUM_SERVOS] =
//{
//  
//{700,2368,1060,1928,2127,870,1476},
//{600,2308,1231,1768,1914,881,2031},
//{600,2310,615,1768,2290,886,2031},
//{981,2334,1310,1768,2290,885,2031},
//{983,2333,1314,1771,2294,886,939},
//{758,2398,1096,2400,2292,885,937},
//{702,2368,1060,1914,2129,870,939},
//
//{700,2368,1060,1928,2127,870,1476},
//{0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0}
//
//};





int deltaTime = 250;

int deltaTimeTurn = 1000;

//int sequencesSpeeds[NUM_SEQEUENCES]  = {deltaTimeTurn, deltaTimeTurn , deltaTimeTurn, deltaTimeTurn, deltaTimeTurn , deltaTimeTurn, deltaTimeTurn, deltaTimeTurn,     deltaTimeTurn, deltaTimeTurn, deltaTimeTurn};

//walk forward
int sequencesSpeeds[NUM_SEQEUENCES]  = {deltaTime, (deltaTime + 1000)/2, deltaTime, deltaTime, deltaTime + 1000, deltaTime, deltaTime, deltaTime,     deltaTime, deltaTime, deltaTime/2};

//walk back
int sequencesSpeedsBack[NUM_SEQEUENCES]  = {deltaTime,  (deltaTime + 1000)/2 ,deltaTime,deltaTime,  (deltaTime + 1000) , deltaTime, deltaTime, (deltaTime + 1000)/2,    deltaTime, deltaTime, deltaTime};

int pixelColor[12];

ServoEx    gerwalkServo[7];

int currentSequence = 0;



const int NEOPIXEL_PIN  = 8; // neopixel pin
const int NUMPIXELS = 12;   //number of pixels on neopixel ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //start neopixel ring

void setup() {
  // put your setup code here, to run once:

  
  // Attach servo and set limits

  for (int i = 0; i<NUM_SERVOS; i++)
  {
    gerwalkServo[i].attach(servoPins[i]);

  }

  pinMode(2, INPUT);
  pinMode(4, INPUT);
  
reportValues();
Serial.begin(9600);

  pixels.begin(); // This initializes the NeoPixel library.
    pixels.setPixelColor(0, pixels.Color(127,127,127));
    pixels.show();
    delay(2000);

    
  SetServo(1000);

//  delay(5000);
//  while(1);
  
}

void loop() {
  // put your main code here, to run repeatedly:


  

  //map from the knob value (0-1023) to the number of total pixels
  neoPixelOn = map(analogRead(7), 0 , 1023, 2, NUMPIXELS+1) ;

  neoPixelOn = neoPixelOn;

  if(neoPixelOn >= NUMPIXELS +1)
  {
    neoPixelOn;
  }

  setNeoPixel();


  if(digitalRead(2) == HIGH)
  {
    saveSequence();

    //readAnalogs();
    reportValues();
      
    //delay(1000);
  }


  if(digitalRead(4) == HIGH)
  {
//    playSequence();
//    Serial.println("1");
//    playSequence();
//    Serial.println("2");
//    playSequence();
//    Serial.println("3");
//    playSequence();
//    Serial.println("4");
//    playSequence();
//    Serial.println("5");
    playSequence();
    Serial.println("1");
    playSequence();
    Serial.println("2");
//    playSequenceBack();
//    Serial.println("3");
//    playSequenceBack();
//    Serial.println("4");
//    playSequenceBack();
//    Serial.println("5");

    //readAnalogs();
   // reportValues();
      
    delay(1000);
  }



  readAnalogs();
  setServoAnalog();
  delay(10);
  
}



void playSequenceBack()
{
  Serial.println("PLAY");
   //for(int i = 0; i <NUM_SEQEUENCES ; i++)
   for(int i = 0; i < 3 ; i++)
    {

    pixels.setPixelColor(i + 2, Wheel(128));
    pixels.show(); // This sends the updated pixel color to the hardware.



    
     ServoGroupMove.start();
       for(int j = 0; j < NUM_SERVOS; j++)
      {
        if(sequencePositionsBack[i][j] == 0)
        {
          Serial.println("ERROR");
          return;
            
        }
        
        gerwalkServo[j].writeMicroseconds(sequencePositionsBack[i][j] + servoErrors[j]);
      } 
      int DeltaTime = 750;
      ServoGroupMove.commit(sequencesSpeedsBack[i]);
      delay(sequencesSpeedsBack[i]);
      
    pixels.setPixelColor(i + 2, Wheel(pixelColor[i + 2]));
    pixels.show(); // This sends the updated pixel color to the hardware.

   
    }
}




void playSequence()
{
  Serial.println("PLAY");
   //for(int i = 0; i <NUM_SEQEUENCES ; i++)
   for(int i = 0; i <8 ; i++)
    {

    pixels.setPixelColor(i + 2, Wheel(128));
    pixels.show(); // This sends the updated pixel color to the hardware.



    
     ServoGroupMove.start();
       for(int j = 0; j < NUM_SERVOS; j++)
      {
        if(sequencePositions[i][j] == 0)
        {
          Serial.println("ERROR");
          return;
            
        }
        else 
        {
          Serial.print(" PLAY");
          Serial.print(j);
          Serial.print(":");
          Serial.print(sequencePositions[i][j] + servoErrors[j]);
        }
        
        gerwalkServo[j].writeMicroseconds(sequencePositions[i][j] + servoErrors[j]);
      } 
      Serial.println(" ");
      int DeltaTime = 750;
      ServoGroupMove.commit(sequencesSpeeds[i]);
      delay(sequencesSpeeds[i]);
      
    pixels.setPixelColor(i + 2, Wheel(pixelColor[i + 2]));
    pixels.show(); // This sends the updated pixel color to the hardware.

   
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



void reportValues()
{

    for(int i = 0; i <NUM_SEQEUENCES ; i++)
    {
        Serial.print("{");
        for(int j = 0; j < NUM_SERVOS;j++)
        {
          Serial.print(sequencePositions[i][j]);
          if(j < NUM_SERVOS -1)
          {
           Serial.print(",");
          }
        }
           Serial.print("}");
           
          if(i < NUM_SEQEUENCES -1)
          {
           Serial.println(",");
          }
    }
    
  

}




void readAnalogs()
{
  for(int i = 0; i< NUM_SERVOS; i++)
  {
    servoValues[i] =  map(analogRead(i), 0, 1023, 600, 2400);
  }
}


void setNeoPixel()
{
   //go through each pixel
   for(int i=2;i<NUMPIXELS+1;i++)
   {
    //turn pixels on if they are lower than the 'neopixelon'
    if(i == neoPixelOn)
    {
      pixels.setPixelColor(i, Wheel(128)); // set color using the Wheel function based on the analog sensor
     }
    else
    {
      //pixels.setPixelColor(i, pixels.Color(0,0,0)); // rgb color 0,0,0 is off
      if(pixelColor[i] == 0)
      {
          pixels.setPixelColor(i, pixels.Color(0,0,0)); // rgb color 0,0,0 is off
      }
      else
      {
      pixels.setPixelColor(i, Wheel(pixelColor[i])); // rgb color 0,0,0 is off
      }
       
    }
   }

   if(neoPixelOn >= NUMPIXELS )
   {
    pixels.setPixelColor(0, Wheel(128));
   }
   else
   {
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    
   }

  if(lastNeoPixelOn != neoPixelOn)
  {
    
    pixels.show(); // This sends the updated pixel color to the hardware.
    lastNeoPixelOn = neoPixelOn;
  }



   
    
}





// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}





void setServoAnalog()
{
  for(int i = 0; i < NUM_SERVOS; i++)
    {
      gerwalkServo[i].writeMicroseconds(servoValues[i] + servoErrors[i]);
      //gerwalkServo[i].writeMicroseconds(sequencePositions[neoPixelOn-2][i] + servoErrors[i]);
      

    
    }
}

void saveSequence()
{
   for(int i = 0; i < NUM_SERVOS; i++)
    {
      
     sequencePositions[neoPixelOn-2][i] = servoValues[i] ;
      

    
    }

    pixels.setPixelColor(neoPixelOn, Wheel(2));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500);
    pixels.setPixelColor(neoPixelOn, Wheel(128));
    pixels.show(); // This sends the updated pixel color to the hardware.
    pixelColor[neoPixelOn] = 64;
}



