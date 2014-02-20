#include <HX711.h> // 包含库的头文件
 
 
#define datapin 8
#define clockpin 9


HX711 hx(clockpin, datapin,128); // 数据接脚定义
// HX711 hx(Clock, Datain); // 数据接脚定义
 

void setup() {
 
  Serial.begin(9600);
 
}
 

void loop()
 
{
 
  double sum = 0;    // 为了减小误差，一次取出10个值后求平均值。
 
  for (int i = 0; i < 10; i++) // 循环的越多精度越高，当然耗费的时间也越多
 
    sum += hx.read();  // 累加
 
  Serial.println(sum/10); // 求平均值进行均差
 
}
