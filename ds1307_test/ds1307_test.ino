// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
/*
    Serial.print("System Date Time:(");
    Serial.print(__DATE__);
    Serial.print("^");
    Serial.print(__TIME__);
    Serial.println(")");

    //RTC.adjust(DateTime(2013,7,11,12,59,22));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    Serial.print("(");
    Serial.print(__DATE__);
    Serial.print("^");
    Serial.print(__TIME__);
    Serial.println(")");
    
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
*/
}

void loop () {
    DateTime now = RTC.now();
    Serial.println(getdatetime());
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now.unixtime() + 7 * 86400L + 30);
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(1000);
}

String getdatetime()
{
    String tmp ="";
      DateTime now = RTC.now();
      tmp.concat(now.year()) ;
      tmp.concat('@') ;
    tmp.concat(now.month());
    tmp.concat('@');
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
