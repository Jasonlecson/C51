#include <reg52.h>
#include <math.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit key1=P3^1;
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
sbit PWM_OUT=P2^7;

uint PWM_Value;
uchar order=0;

void Delay(unsigned int s);
void Init_Timer0();
uchar flag;

void Delay(unsigned int s)
{
unsigned int i;
for(i=0; i<s; i++);
for(i=0; i<s; i++);
}


void Init_Timer0()        
{
TMOD=0x11;
TH0=(65536-1500)/256;
TL0=(65536-1500)%256;
EA = 1;
ET0 = 1;
TR0 = 1;
PT0=1;
}


int main(void)
{
	PWM_Value = 1500;
	Init_Timer0();
	
	while(1)
	{
		if((key1==0)|key2==0)
		{
			if(key1==0)
			{
				flag = 1;
			}
			if(key2==0)
			{
				flag = 2;
			}
		}
		else
		{
				flag=0;
		}
		Delay(20);
	}
}

void timer0(void) interrupt 1
{
if(flag == 1)
		PWM_Value = 1000;
else if(flag == 2)
		PWM_Value = 2000;
else PWM_Value = 1500;
//if(PWM_Value >= 2500)
//	PWM_Value = 2500;
//if(PWM_Value <= 500)
//	PWM_Value = 500;


switch(order)
{
	case 1:PWM_OUT=1;
		   TH0=(65536-PWM_Value)>>8; 
		   TL0=(uchar)(65536-PWM_Value);
		   break;                          
	case 2:PWM_OUT=0;
		   TH0=(65536-(5000-PWM_Value))>>8;    
		   TL0=(uchar)(65536-(5000-PWM_Value));
		   break;                          
	case 3:
		   TH0=60536>>8;   
		   TL0=(uchar)60536;
		   break;
	case 4:
		   TH0=60536>>8;   
		   TL0=(uchar)60536;
		   order=0;
		   break;
default: order=0; 
		   break;
} 
       order++;
}