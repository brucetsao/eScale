
// Hx711.DOUT - pin #A1
// Hx711.SCK - pin #A0
#include <EEPROM.h>
#include <Hx711.h>
#define datapin 8
#define clockpin 9
 
//HX711 hx(9, 10, 128, 0.00087305);
Hx711 hx(datapin, clockpin );
 
int i=0;
 

// 用于在 EEPROM 中储存 double 类型数据的共用体
 
unsigned char *dpointer;
 
union data {
 
  double v;
 
  unsigned char dchar[8];
 
} dvalue;
 

void setup() {
 
  Serial.begin(9600);
 
  for(i = 0; i < 8; i++) dvalue.dchar[i] = EEPROM.read(i); // 从 EEPROM 读取偏移量
 
  hx.set_offset(dvalue.v);                                 // 设置已读取的偏移量
 
}
 
void loop() {
 
  if(digitalRead(4) == LOW) {
 
    dvalue.v = hx.tare();     // 去皮重并读取偏移量
 
    hx.set_offset(dvalue.v);  // 设置已读取的偏移量
 
    dpointer = dvalue.dchar;  // 以下程序将偏移量分解并储存到 EEPROM
 
    for(i = 0; i < 8; i++) {
 
      EEPROM.write(i,*dpointer);
 
      dpointer++;
 
    }
 
  }
 
  double sum = 0;
 
  for (i = 0; i < 10; i++) {
 
    sum += hx.bias_read();
 
  }
 
  Serial.println(sum/10);
 
  //Serial.println(sum / 10 * (1 + (20 - temprature) / 10 * 0.02)）; // 带线性温度补偿的输出，注意temprature单位为摄氏度。
 
}
 
