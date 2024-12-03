

/////////////////////
/*
GYTOF10M----MINI
VCC----VCC
GND----GND
1:GYtof_TX---10
2:GYtof_RX---11
*/
//////////////////
#include <SoftwareSerial.h>
typedef struct
{
    float distance;
    uint16_t amp;
    int8_t temp;
} gytof;
SoftwareSerial mySerial(10, 11); // RX, TX
byte add=0xa4;
byte len=0,start_reg=0;
unsigned char Re_buf[30],counter=0;
unsigned char sign=0;
gytof my_tof;
void setup() {
   Serial.begin(115200);
   mySerial.begin(9600);
   mySerial.listen();      
} 

void loop() {
  unsigned char i=0,sum=0;
  while (mySerial.available()) {   
    Re_buf[counter]=(unsigned char)mySerial.read();
    switch(counter)
    {
      case 0:
      if(Re_buf[0]!=add)
      return;
      break;
      case 1:
    
      if(Re_buf[1]!=0x03)
        { 
          counter=0;
          return;
      }
      break;
      case 2:
        if(Re_buf[2]<16)
         start_reg=Re_buf[2];
         else
            { 
          counter=0;
          return;
         }
      break;
      case 3:
         if((start_reg+Re_buf[3])<16)
            len=Re_buf[3];
            else
            { 
              counter=0;
             return;
         }
            
      break;
      default:
         if(len+5==counter)
         {  
            sign=1;
         }
      break;
    }
    
  if(sign)
  {   
     sign=0;
     for(i=0;i<counter-1;i++)
      sum+=Re_buf[i]; 
       counter=0;
     if(sum==Re_buf[i] )        //检查帧头，帧尾
     {  	       
        if(start_reg==0x08)
        {
         my_tof.distance=(Re_buf[4]<<8)|Re_buf[5];
	 my_tof.amp=(Re_buf[6]<<8)|Re_buf[7];
	 my_tof.temp=Re_buf[8];
	
        }
//      	 Serial.print("distance:");
         Serial.print((float)my_tof.distance/10);
//         Serial.print("，");
//	 Serial.print("cm,amp:");
//         Serial.print(my_tof.amp);
//	 Serial.print(",temp:");
//         Serial.println(my_tof.temp);
        Serial.print("\n");      
       
           
     }
//     else
//        {
//          Serial.print(" sum ");
//          Serial.println(sum);
//      } 
   }
   else
   counter++; 
//   Serial.print("cont:");
//   Serial.println(counter);
  }
   
}

