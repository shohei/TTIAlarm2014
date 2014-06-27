/*
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Keypad.h>
#include <avr/pgmspace.h>

//function prototype
void StartLesson();
void BreakTime();
void BreakOver();
void Closing();
void SilenceHour();
void digitalClockDisplay();
void mainMenu();
void printDigits(int digits);
void editClock();
void alarmSetup();
void disableAllAlarms();
void enableAllAlarms();

AlarmID_t mon0 = 0;
AlarmID_t tue0 = 0;
AlarmID_t wed0 = 0;
AlarmID_t thu0 = 0;
AlarmID_t fri0 = 0;
AlarmID_t mon1 = 1;
AlarmID_t tue1 = 1;
AlarmID_t wed1 = 1;
AlarmID_t thu1 = 1;
AlarmID_t fri1 = 1;
AlarmID_t mon2 = 2;
AlarmID_t tue2 = 2;
AlarmID_t wed2 = 2;
AlarmID_t thu2 = 2;
AlarmID_t fri2 = 2;
AlarmID_t mon3 = 3;
AlarmID_t tue3 = 3;
AlarmID_t wed3 = 3;
AlarmID_t thu3 = 3;
AlarmID_t fri3 = 3;
AlarmID_t mon4 = 4;
AlarmID_t tue4 = 4;
AlarmID_t wed4 = 4;
AlarmID_t thu4 = 4;
AlarmID_t fri4 = 4;

// A fun sketch to demonstrate the use of the Tone library.

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

// You can get more RTTTL (RingTone Text Transfer Language) songs from
// http://code.google.com/p/rogue-code/wiki/ToneLibraryDocumentation

#include <Tone.h>

Tone tone1;

#define OCTAVE_OFFSET 0

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

//char *song = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
//prog_char indianna[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//prog_char ateam[] PROGMEM = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//prog_char flintstones[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//prog_char jeopardy[] PROGMEM = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//prog_char entertainer[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//
//char *indianna = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//char *entertainer = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
char *ateam = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//char *flintstones = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//char *jeopardy = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//
//char *song = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//char *song = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//char *song = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
//char *song = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *fox = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
//char *song = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *song = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
//char *song = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
//char *song = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
//char *song = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
//char *song = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
//char *song = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
//char *song = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
//char *song = "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#";
// char *song2  = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";

//initialize
//int silenpin = 0;
uint8_t hr;
uint8_t mint;
uint8_t dy;
uint8_t mnth;
uint8_t yr;
uint8_t keynumber;
uint8_t keynumber1;
uint8_t keynumber2;

boolean invalid = false;

/*
timeDayOfWeek_t dayOfWeeks[]={
  dowMonday,  dowTuesday,
  dowWednesday,  dowThursday,
  dowFriday, dowSaturday,
  dowSunday
};
*/

#define SCHEDULE_SIZE  5
int schedule[SCHEDULE_SIZE][2] = {
  {7,15},{8,0},
  {10,40},{11,20},
  {14,30}
};

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {3, 2, A0, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void alarmSetup(){
//     for(int i=0;i<SCHEDULE_SIZE;i++){
//       Alarm.alarmRepeat(dowMonday,schedule[i][0],schedule[i][1],10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowTuesday,schedule[i][0],schedule[i][1],10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowWednesday,schedule[i][0],schedule[i][1],10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowThursday,schedule[i][0],schedule[i][1],10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowFriday,schedule[i][0],schedule[i][1],10,SilenceHour);  // Monday to Friday every week  
     
//       Alarm.alarmRepeat(dowMonday,7,15,10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowTuesday,7,15,10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowWednesday,7,15,10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowThursday,7,15,10,SilenceHour);  // Monday to Friday every week
//       Alarm.alarmRepeat(dowFriday,7,15,10,SilenceHour);  // Monday to Friday every week  

       mon1 = Alarm.alarmRepeat(dowMonday,8,0,10,StartLesson);  // Monday to Friday every week
       tue1 = Alarm.alarmRepeat(dowTuesday,8,0,10,StartLesson);  // Monday to Friday every week
       wed1 = Alarm.alarmRepeat(dowWednesday,8,0,10,StartLesson);  // Monday to Friday every week
       thu1= Alarm.alarmRepeat(dowThursday,8,0,10,StartLesson);  // Monday to Friday every week
       fri1 = Alarm.alarmRepeat(dowFriday,8,0,10,StartLesson);  // Monday to Friday every week

       mon2 = Alarm.alarmRepeat(dowMonday,10,40,10,BreakTime);  // Monday to Friday every week
       tue2 = Alarm.alarmRepeat(dowTuesday,10,40,10,BreakTime);  // Monday to Friday every week
       wed2 = Alarm.alarmRepeat(dowWednesday,10,40,10,BreakTime);  // Monday to Friday every week
       thu2 = Alarm.alarmRepeat(dowThursday,10,40,10,BreakTime);  // Monday to Friday every week
       fri2 = Alarm.alarmRepeat(dowFriday,10,40,10,BreakTime);  // Monday to Friday every week

       mon3 = Alarm.alarmRepeat(dowMonday,11,20,10,BreakOver);  // Monday to Friday every week
       tue3 = Alarm.alarmRepeat(dowTuesday,11,20,10,BreakOver);  // Monday to Friday every week
       wed3 = Alarm.alarmRepeat(dowWednesday,11,20,10,BreakOver);  // Monday to Friday every week
       thu3 = Alarm.alarmRepeat(dowThursday,11,20,10,BreakOver);  // Monday to Friday every week
       fri3 = Alarm.alarmRepeat(dowFriday,11,20,10,BreakOver);  // Monday to Friday every week

       mon4 = Alarm.alarmRepeat(dowMonday,14,30,10,Closing);  // Monday to Friday every week
       tue4 = Alarm.alarmRepeat(dowTuesday,14,30,10,Closing);  // Monday to Friday every week
       wed4 = Alarm.alarmRepeat(dowWednesday,14,30,10,Closing);  // Monday to Friday every week
       thu4 = Alarm.alarmRepeat(dowThursday,14,30,10,Closing);  // Monday to Friday every week
       fri4 = Alarm.alarmRepeat(dowFriday,14,30,10,Closing);  // Monday to Friday every week
 //    }
}

//prog_char string_0[] PROGMEM = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//prog_char string_1[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//prog_char string_2[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//prog_char string_3[] PROGMEM = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//prog_char string_4[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//// Then set up a table to refer to your strings.
//PROGMEM const char *string_table[] = 	   // change "string_table" name to suit
//{   
//  string_0,
//  string_1,
//  string_2,
//  string_3,
//  string_4 };
//char buffer[430];    // make sure this is large enough for the largest string it must hold

void setup() {
  Serial.begin(9600);
  tone1.begin(13);

  //Serial.begin(9600);
  lcd.begin(16, 2);
  //lcd.print("Push the number");
  
  setTime(10,40,5,3,1,11); // set time to Saturday 8:29:00am Jan 1 2011  
  //setTime(10,40,5,23,6,14); // set time to Saturday 8:29:00am Jan 1 2011  
  //Calendar are included in the library, 
  // so that u don't have to set the day(ex.Saturday) manually, yay!
  //create the alarms 

  //1st class start
  //Alarm.alarmRepeat(8,30,0, Silen);  // 8:30am every day
  
  //Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 
  //Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  //Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
  //alarmSetup();
//   Alarm.alarmRepeat(dowMonday,7,15,10,SilenceHour);  // Monday to Friday every week
//   Alarm.alarmRepeat(dowTuesday,7,15,10,SilenceHour);  // Monday to Friday every week
//   Alarm.alarmRepeat(dowWednesday,7,15,10,SilenceHour);  // Monday to Friday every week
//   Alarm.alarmRepeat(dowThursday,7,15,10,SilenceHour);  // Monday to Friday every week
//   Alarm.alarmRepeat(dowFriday,7,15,10,SilenceHour);  // Monday to Friday every week  
   alarmSetup();
  
  //for (int i = 0; i < 5; i++){
  //  for(int j =0; j < SCHEDULE_SIZE; j++){  
//     Alarm.alarmRepeat(dowMonday,schedule[j][0],schedule[j][1],10,Silen);  // Monday to Friday every week
//     Alarm.alarmRepeat(dowTuesday,schedule[j][0],schedule[j][1],10,Silen);  // Monday to Friday every week
//     Alarm.alarmRepeat(dowWednesday,schedule[j][0],schedule[j][1],10,Silen);  // Monday to Friday every week
//     Alarm.alarmRepeat(dowThursday,schedule[j][0],schedule[j][1],10,Silen);  // Monday to Friday every week
//     Alarm.alarmRepeat(dowFriday,schedule[j][0],schedule[j][1],10,Silen);  // Monday to Friday every week
     //Alarm.alarmRepeat(dayOfWeeks[i],schedule[0][0],schedule[0][1],0,Silen);  // Monday to Friday every week 
     //Alarm.alarmRepeat(dayOfWeeks[i],schedule[1][0],schedule[1][1],30,Silen2);  // Monday to Friday every week 
  //  }
  //}
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

//  Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

//  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

//  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

 // Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
//      Serial.print("Playing: ");
//      Serial.print(scale, 10); Serial.print(' ');
//      Serial.print(note, 10); Serial.print(" (");
//      Serial.print(notes[(scale - 4) * 12 + note], 10);
//      Serial.print(") ");
//      Serial.println(duration, 10);
      tone1.play(notes[(scale - 4) * 12 + note]);
      Alarm.delay(duration);
      tone1.stop();
    }
    else
    {
//      Serial.print("Pausing: ");
//      Serial.println(duration, 10);
      Alarm.delay(duration);
    }
  }
}


void loop() {  
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display

  mainMenu();

}

void digitalClockDisplay()
{
  lcd.setCursor(0,0);
  // digital clock display of the time
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
}

void printDigits(int digits)
{
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void Silen(){
  //digitalWrite(silenpin,HIGH); 
  //Beep the silen for 10 seconds
  //delay(10000);
  //digitalWrite(silenpin,LOW);
  //play_rtttl(song);
}

void Silen2(){
  //digitalWrite(silenpin,HIGH); 
  //Beep the silen for 10 seconds
  //delay(10000);
  //digitalWrite(silenpin,LOW);
  //play_rtttl(song2);
}

void SilenceHour(){
//  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0])));
//  Serial.println(F("jeopardy"));
//  Serial.println(buffer);
//  play_rtttl(buffer);
  //  char buffer[430];
//  strcpy_P(buffer, (char*)pgm_read_word(&jeopardy));
//  play_rtttl(buffer);  
//play_rtttl(jeopardy);
   play_rtttl(ateam);
}

void StartLesson(){ 
//  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[1])));
//  Serial.println(F("entertainer"));
//  Serial.println(buffer);
//  play_rtttl(buffer);    
//  char buffer[430];
//  strcpy_P(buffer, (char*)pgm_read_word(&entertainer));
//  play_rtttl(buffer);  
//  play_rtttl(entertainer);
   play_rtttl(ateam);
}

void BreakTime(){
//  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[2])));
//  Serial.println(F("indianna"));
//  Serial.println(buffer);
//  play_rtttl(buffer);    
//  char buffer[430];
//  strcpy_P(buffer, (char*)pgm_read_word(&indianna));
//  play_rtttl(buffer);  
//  play_rtttl(indianna);
   play_rtttl(ateam);
}

void BreakOver(){
//  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[3])));
//  Serial.println(F("ateam"));
//  Serial.println(buffer);
//  play_rtttl(buffer);    
  //  char buffer[430];
//  strcpy_P(buffer, (char*)pgm_read_word(&ateam));
//  play_rtttl(buffer);  
//  play_rtttl(ateam);
   play_rtttl(ateam);
}

void Closing(){
//  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[4])));
//  Serial.println(F("flintstones"));
//  Serial.println(buffer);
//  play_rtttl(buffer);    
//  char buffer[430];
//  strcpy_P(buffer, (char*)pgm_read_word(&flintstones));
//  play_rtttl(buffer);  
//  play_rtttl(flintstones);
   play_rtttl(ateam);
}


uint8_t keyboardInput(){
 //wait for input
   char key;
   key = NO_KEY;
   while(key == NO_KEY){
     key = keypad.getKey();
   }

    lcd.setCursor(0,1);
    switch(key){
      case '1':
        lcd.print("1");
        keynumber1 = 1;
        break;

      case '2':
        lcd.print("2");
        keynumber1 = 2;
        break;

      case '3':
        lcd.print("3"); 
        keynumber1 = 3;
        break;

      case '4':
        lcd.print("4"); 
        keynumber1 = 4;
        break;

      case '5':
        lcd.print("5");
        keynumber1 = 5;
        break;

      case '6':
        lcd.print("6");
        keynumber1 = 6;
        break;

      case '7':
        lcd.print("7");
        keynumber1 = 7;
        break;

      case '8':
        lcd.print("8");
        keynumber1 = 8;
        break;

      case '9':
        lcd.print("9");
        keynumber1 = 9;
        break;

      //CANCEL button
      //you can edit here to implementate the cancel button
      case '*':
        //lcd.print("*");
        //homeScreen();
        break;

      case '0':
        lcd.print("0");
        keynumber1 = 0;
        break;
      
      //Enter button
      //case 780:
      //case 779:
        //lcd.print("#");
        //break;
    }  

   key = NO_KEY;
   while(key==NO_KEY){
     key = keypad.getKey(); 
   }
   
    lcd.setCursor(1,1);   
    switch(key){      
      
      case '1':
        lcd.print("1");
        keynumber2 = 1;
        delay(1000);
        break;

      case '2':
        lcd.print("2");
        keynumber2 = 2;
        delay(1000);
        break;

      case '3':
        lcd.print("3"); 
        keynumber2 = 3;
        delay(1000);
        break;

      case '4':
        lcd.print("4"); 
        keynumber2 = 4;
        delay(1000);
        break;

      case '5':
        lcd.print("5");
        keynumber2 = 5;
        delay(1000);
        break;

      case '6':
        lcd.print("6");
        keynumber2 = 6;
        delay(1000);
        break;

      case '7':
        lcd.print("7");
        keynumber2 = 7;
        delay(1000);
        break;

      case '8':
        lcd.print("8");
        keynumber2 = 8;
        delay(1000);
        break;

      case '9':
        lcd.print("9");
        keynumber2 = 9;
        delay(1000);
        break;

      //CANCEL button
      //you can edit here to implemente the cancel button
      case '*':
        //Serial.print("*"); 
        //lcd.print("*");
        //homeScreen();
        break;

      case '0':
        lcd.print("0");
        keynumber2 = 0;
        delay(1000);
        break;
      
      //Enter button
      case '#':
        //lcd.print("#");
        keynumber2 = 100;
        break;
    }  

    //Reading of 2nd number finish
  
  if(keynumber2 == 100){
    //Return only 1st number
    keynumber = keynumber1; 
  } else {
    keynumber = keynumber1 * 10 + keynumber2; 
  }
  
  return keynumber;   
 }

void mainMenu(){   
  char key;
  key = keypad.getKey();
  if(key != NO_KEY){
    if(key == '#'){
      //Menu button
        lcd.setCursor(0, 1);
        lcd.print(F("Edit the clock"));
        delay(2000);
        lcd.clear();
        editClock();
    }  
  }
}

void editClock(){
  //initialize
  invalid = false;

  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print(F("Year? 0 to 99"));
  yr = keyboardInput();
  
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print(F("Month? 1 to 12"));
  mnth = keyboardInput();
 if(mnth > 12){
    lcd.setCursor(0,1);
    lcd.print(F("invalid input")); 
    delay(1000);
    invalid = 1;
  }  

  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print(F("Day? 1 to 31"));
  dy = keyboardInput();
  if(dy > 31){
    lcd.setCursor(0,1);
    lcd.print(F("invalid input")); 
    delay(1000);
    invalid = 1;
  }  
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Hour? 0 to 23"));
  hr = keyboardInput();
  if( hr > 23){
    lcd.setCursor(0,1);
    lcd.print(F("invalid input")); 
    delay(1000);
    invalid = true;
  }  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Minute? 0 to 59"));
  mint = keyboardInput();
  if( mint > 59 ){
    lcd.setCursor(0,1);
    lcd.print(F("invalid input")); 
    delay(1000);
    invalid = true;
  }  

  if(invalid == false){
    Serial.println(hr);
    Serial.println(mint);
    Serial.println(dy);
    Serial.println(mnth);
    Serial.println(yr);  
    setTime(hr,mint,0,dy,mnth,yr);
    disableAllAlarms();
    enableAllAlarms();
    //alarmSetup();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Time uploaded!"));
    delay(2000);
    lcd.clear();
  } else {
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print(F("Sorry, try again!"));
   delay(2000);
   lcd.clear();
  }
  
}

void disableAllAlarms(){
  Alarm.disable(mon1);
  Alarm.disable(tue1);
  Alarm.disable(wed1);
  Alarm.disable(thu1);
  Alarm.disable(fri1);
  Alarm.disable(mon2);
  Alarm.disable(tue2);
  Alarm.disable(wed2);
  Alarm.disable(thu2);
  Alarm.disable(mon2);
  Alarm.disable(tue3);
  Alarm.disable(wed3);
  Alarm.disable(thu3);
  Alarm.disable(fri3);
  Alarm.disable(mon3);
  Alarm.disable(tue4);
  Alarm.disable(wed4);
  Alarm.disable(thu4);
  Alarm.disable(fri4);
}

void enableAllAlarms(){
  Alarm.enable(mon1);
  Alarm.enable(tue1);
  Alarm.enable(wed1);
  Alarm.enable(thu1);
  Alarm.enable(fri1);
  Alarm.enable(mon2);
  Alarm.enable(tue2);
  Alarm.enable(wed2);
  Alarm.enable(thu2);
  Alarm.enable(mon2);
  Alarm.enable(tue3);
  Alarm.enable(wed3);
  Alarm.enable(thu3);
  Alarm.enable(fri3);
  Alarm.enable(mon3);
  Alarm.enable(tue4);
  Alarm.enable(wed4);
  Alarm.enable(thu4);
  Alarm.enable(fri4);
}
