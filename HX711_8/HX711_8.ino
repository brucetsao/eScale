#include <HX711.h> // HX711rduino library
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"

#define datapin 10    
#define clockpin 11  
#define RXPin 2   // Rx pin
#define TXPin 3   // Tx pin
//------define key button ------ 
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
//------define key button ------ 

int lcd_key = 0 ;
int adc_key_in = 0 ;
double sum0 = 0 ;
double sum1 = 0 ;
int newflag  = 0 ;
int oldWht = 0 ;
char datetimestr1[24];

HX711 hx(clockpin, datapin,128,0.0031977841); 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SoftwareSerial mySerial(RXPin, TXPin); // RX, TX
RTC_DS1307 RTC;   //init RTC
   
void setup() {
 //  int   oldWht;
  hx.set_offset(-13117.91613);

  Serial.begin(9600);
  mySerial.begin(9600);
 Wire.begin();    　//　連接ds1307　　必用的函式
  RTC.begin();    // 　lauch RTC
   hx.tare(50);  
   lcd.begin(16, 2); // start the library
  lcd.setCursor(0,0);
   sum0 = 0;
   sum1 = 0;
  oldWht = 0 ;    　// 　開始初重　為零
  newflag = 0 ;    　//　不輸出　序列資料
}

void loop() {
  int tmpno = 0 ;
  int key ;
   key = checkkey();
 if (key == 11)
{
    lcd.clear();
    lcd.setCursor(0,0); // move cursor to second line "1" and 9 spaces over
    lcd.print("tare .........");
    hx.tare(50);  
     oldWht = 0 ;
    newflag = 0 ;
    delay(200);
} 
   sum0 = 0;
   sum1 = 0;
  for (int i = 0; i < 10; i++)
  {
     sum0 += hx.read();
     sum1 += hx.bias_read();
   }
     tmpno = (int)sum1/10 ;
       
   lcd.clear();
    lcd.setCursor(0,0); 
  lcd.print("ADC :"); 
  lcd.print((int)sum0/10); 
  lcd.print("  "); 
  lcd.print(key); 
  lcd.setCursor(0,1); 
 lcd.print((int)sum1/10);  \
 lcd.print("  g ");  
 lcd.print(sum1/10);  
 lcd.print("  g");  
    Serial.print(getdatetime()) ;
    Serial.print(sum0/10);  
    Serial.print(" ");
   Serial.println((int)sum1/10);  
   if( (tmpno> 0) && (tmpno != oldWht) )
    { 
      newflag = 1 ;
    } 
    else
    { 
      newflag = 0 ;
    } 
    if ( newflag == 1)
    {
     mySerial.print(getdatetime()) ;
      mySerial.print(tmpno) ;  
      mySerial.println("g") ;  
      oldWht = tmpno ;
    }
  
// checkkey();
    delay(500);
}

int read_LCD_buttons()
{
  adc_key_in = analogRead(0); // read the value from the sensor 
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50) return btnRIGHT; 
  if (adc_key_in < 250) return btnUP; 
  if (adc_key_in < 450) return btnDOWN; 
  if (adc_key_in < 650) return btnLEFT; 
  if (adc_key_in < 850) return btnSELECT; 
  // For V1.0 comment the other threshold and use the one below:
  return btnNONE; // when all others fail, return this...
}


int checkkey()
{
  lcd_key = read_LCD_buttons(); // read the buttons
  switch (lcd_key) // depending on which button was pushed, we perform an action
  {
  case btnRIGHT:
    {
      return 1 ;
      break;
    }
  case btnLEFT:
    {
        return 2 ;
      break;
    }
  case btnUP:
    {
        return 3 ;
      break;
    }
  case btnDOWN:
    {
        return 4 ;
      break;
    }
  case btnSELECT:
    {
        return 11 ;
      break;
    }
  case btnNONE:
    {
        return 0 ;
      break;
    }
  } 
} 

String getdatetime()
{
  //　　此函式　輸出ds1307　的時間資料
   DateTime now = RTC.now();
    String tmp ="";
    tmp.concat(now.year()) ;
      tmp.concat('/') ;
    tmp.concat(now.month());
    tmp.concat('/');
    tmp.concat(now.day());
    tmp.concat(' ');
    tmp.concat(now.hour());
    tmp.concat(':');
    tmp.concat(now.minute());
    tmp.concat(':');
    tmp.concat(now.second());
    tmp.concat("   ");
    return   tmp ;
} 


