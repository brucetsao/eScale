/* sample for digital weight scale of hx711, display with a HD44780 liquid crtstal monitor
 *
 * hardware design: syyyd
 * available at http://syyyd.taobao.com
 *
 * library design: Weihong Guan (@aguegu)
 * http://aguegu.net
 *
 * library host on
 * https://github.com/aguegu/Arduino
 */

// Hx711.DOUT - pin #A1
// Hx711.SCK - pin #A0

#include <Hx711A.h>
#define datapin 8
#define clockpin 9




Hx711 scale(datapin, clockpin );

void setup() {

  Serial.begin(9600);
scale.setScale(320) ;
}

void loop() {

  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  delay(1000);
}
/*
HX711(byte sck, byte dout, byte amp = 128, double co = 1); // 定义 sck、dout 接脚，增益倍数（默认128）和修正系数（默认1）
 
void set_amp(byte amp); // 改变增益倍数和对应的通道，至少调用一次 read() 后起作用
 
bool is_ready(); // 返回 hx711 是否可用，在 read() 函数中会被调用
 
long read(); // 返回传感器电压值，如果 hx711 不可用则程序会暂停在此函数
 
double bias_read(); // 返回：(read() - 偏移值) * 修正系数
 
void tare(int t = 10); // 将皮重添加到偏移值，影响每次 read(); 的调用
 
void set_co(double co = 1); // 修改修正系数（默认为1）
 
void set_offset(long offset = 0); // 修改偏移值（默认为0）
*/

