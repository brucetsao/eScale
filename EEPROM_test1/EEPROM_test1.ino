#include <EEPROM.h>

#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}

#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}

 

unsigned long incomingByte = 0;   // 定义无符号长整数型变量incomingByte初始值为0

 

void setup() {

  Serial.begin(9600);     // 打开串口，设置数据传输速率9600

}

 

void loop() {

 

 

  if (Serial.available() > 0) {

    incomingByte = Serial.parseInt();  //读取串口传入的下一个有效整数，把该整数赋值给incomingByte变量

    EEPROM_write(0,incomingByte)   //把incomingByte变量从0地址位开始写入EEPROM

 

  }

  EEPROM_read(0,incomingByte) //从0地址位开始读取EEPROM，把值写入变量incomingByte

  Serial.println(incomingByte); //通过串口输出

  delay(1000);

}
