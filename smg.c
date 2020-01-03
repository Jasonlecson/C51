#include "reg52.h"

typedef unsigned int uint;	  //对数据类型进行声明定义
typedef unsigned char uchar;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4

uchar code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar DisplayData[8];
char datnum1=0,datnum2=0,datnum3=0,datnum4=0;
uchar setflag=0;
uchar wei_change=0;

void delay10us(uint i)
{
	while(i--);
}

void DigDisplay()
{
	uchar i;
	for(i=0;i<4;i++)
	{
		switch(i)
	{
		case(0):
				LSA=1;LSB=1;LSC=1; break;
			case(1):
				LSA=0;LSB=1;LSC=1; break;
			case(2):
				LSA=1;LSB=0;LSC=1; break;
			case(3):
				LSA=0;LSB=0;LSC=1; break;
//			case(4):
//				LSA=1;LSB=1;LSC=0; break;
//			case(5):
//				LSA=0;LSB=1;LSC=0; break;
//			case(6):
//				LSA=1;LSB=0;LSC=0; break;
//			case(7):
//				LSA=0;LSB=0;LSC=0; break;
	}
	P0=DisplayData[i];//发送段码
	delay10us(100); //间隔一段时间扫描	
	P0=0x00;//消隐
	}
}

void smg(uint a)
{
	datnum4=a/1000;
	datnum3=(a-datnum4*1000)/100;
	datnum2=(a-datnum4*1000-datnum3*100)/10;
	datnum1=(a-datnum4*1000-datnum3*100-datnum2*10);
	DisplayData[0]=smgduan[datnum4];
	DisplayData[1]=smgduan[datnum3];
	DisplayData[2]=smgduan[datnum2];
	DisplayData[3]=smgduan[datnum1];
	DigDisplay();
}