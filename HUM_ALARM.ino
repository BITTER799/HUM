#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "I2Cdev.h"
#include <SHT2x.h>
#define hum 50          //定义预设湿度值为50%
#include <U8glib.h>
#define INTERVAL_LCD   20             //定义OLED刷新时间间隔  
unsigned long lcd_time = millis();  
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_osb21)
#define setFont_SS u8g.setFont(u8g_font_fub25n)
  
  int sensor_hum; 
  int sensor_tem;
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(A0,OUTPUT);
}

void loop()
{
  read();
  if(sensor_hum<=hum)
  {   
    digitalWrite(A0,HIGH);  //接通工作电路，让加湿器开始工作
    delay(10000);    
    digitalWrite(A0,LOW);  //关闭工作电路
  }                      
  Serial.print("hum(%RH):");                
  Serial.println(SHT2x.GetHumidity());
  Serial.print("tem(C):");
  Serial.println(SHT2x.GetTemperature());
  delay(1000);
  u8g.firstPage();     //从这开始下面十行是让OLED显示温湿度
    do {
        setFont_S;
        u8g.setPrintPos(4, 32);
        u8g.print("H/%: ");
        u8g.print(sensor_hum);
        u8g.setPrintPos(4, 64);
        u8g.print("T/C: ");
        u8g.print(sensor_tem);
    }while( u8g.nextPage() );
}
void read()   //自定义一个read函数
{
  sensor_hum = SHT2x.GetHumidity() ;
  sensor_tem = SHT2x.GetTemperature();
}

