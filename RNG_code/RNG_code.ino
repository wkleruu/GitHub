
/*
The Super Three: 
CS 697AN
Fall 2017

Members: Willhelmi, Chazni,and Anju

*/


//#include <DS3231.h>  //for RTC - Real Time Clock
//#include <pcmConfig.h>
//#include <pcmRF.h>
//#include <TMRpcm.h> //for Audio play
#include <SD.h>  //for communication with SD shield
#include <SPI.h>  //for SD shield
#define SD_ChipSelectPin 8

//Function prototypes
void produce_rn(int num_pulses);
void saveData();  // write data to SD card

const int inputPin = 7;
const int ledPin = 6;
const int buzzPin = 5;


//String dataString ="";
//String  dataString1 = "";


int i  = 0;
int numPulses = 0;
const int numBits = 64;
int rn[numBits];

File sensorData;
//const int chipSelect = 4;  //Chip Select pin (CS)
 
//Time since the program started
//unsigned long time;

//int pulse_counter = 0;
//int num_loops = 0;


void setup() //runs only once
{
  Serial.begin(9600);  // Open serial communications and wait for port to open:
 // rtc.begin();  // Initialize the rtc object (the clock module)
  
  // ******************Uncommented the following thee lines to Set the Date and Time********************
  
  //rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(1, 6, 00);     // Set the time to 12:00:00 (24hr format)
 // rtc.setDate(13, 10 , 2017);   // Set the date to January 1st, 2014
  
  
  Serial.println("Initializing SD card...");
  // see if the card is present and can be initialized:
 if (!SD.begin(SD_ChipSelectPin)) 
 {
   Serial.println("Card failed, or not present");
   // don't do anything more:
   return;
  }
 Serial.println("    .......Card initialized successfuly.");
 Serial.println();
 Serial.println();
 Serial.println();
 Serial.println();


pinMode(7,INPUT);
pinMode(6,OUTPUT);
pinMode(5,OUTPUT);
}




//BEGINING OF THE  INFINIT LOOP **********************************************************************************
//****************************************************************************************************************
void loop()
{
if(i < numBits){
  if (digitalRead(inputPin) == HIGH){ //fill the array
       rn[i] = 1;
       i++;
    }else{
      rn[i] = 0;
      i++;
      }
    }else{  //write to SD card and print in the serial terminal
      i = 0;
      int j = 0;
      
      digitalWrite(ledPin, HIGH);  //turn On the LED to indicate generation of one random number
      Serial.println("Generating a random number, please wait...");  //announce the generation 
      delay(1000);   
      sensorData = SD.open("rn_data.csv", FILE_WRITE);  //open the file for writing
      while( j < numBits){        
        if (sensorData){
            sensorData.print(rn[j]);
            //sensorData.print(",");                 

             Serial.print(rn[j]); 
             Serial.print(" ");
             //Serial.println(); 
        }else{
          Serial.println("Error writing to file !");    
        }

        j++;
      }
      sensorData.println();
      Serial.println();
      sensorData.close(); // close the file
      digitalWrite(ledPin, LOW);  //turn off the LED to indicate complition 
      Serial.println();
      Serial.println();
      digitalWrite(buzzPin, HIGH);
      delay(80) ;  
      digitalWrite(buzzPin, LOW);   
      delay(1000) ;
    }
 delay(5);

}//End of the Main LOOP

//******************************************************************************************************************************


void produce_rn(int num_pulses)
{
Serial.println(num_pulses);
//Serial.println ("testing...");
//delay(1000);

}

//******************************************************************************************************************************

//write to the log file
void saveData() 
{

// now append new data file
File sensorData = SD.open("data.csv", FILE_WRITE);
if (sensorData)
  {
    int j = 0;
    while (j < numBits){
      sensorData.print("fdsfsfsdf");
      sensorData.print(",");      
    }
    sensorData.println();
    sensorData.close(); // close the file
  }   
 
else 
{
  
   Serial.println("Error writing to file !"); 
}

}


