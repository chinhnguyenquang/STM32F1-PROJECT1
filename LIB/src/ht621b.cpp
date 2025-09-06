#include "ht621b.h"

 /* @brief DISPLAY HARDWARE DEFINES BLOCK*/
#define  BIAS     0x52             //0b1000 0101 0010  1/3duty 4com
#define  SYSDIS   0x00             //0b1000 0000 0000  Turn off both system oscillator and LCD bias generator
#define  SYSEN    0x02             //0b1000 0000 0010  Turn on system oscillator
#define  LCDOFF   0x04             //0b1000 0000 0100  Turn off LCD bias generator
#define  LCDON    0x06             //0b1000 0000 0110  Turn on LCD bias generator
#define  XTAL     0x28             //0b1000 0010 1000  System clock source, crystal oscillator
#define  RC256    0x30             //0b1000 0011 0000  System clock source, on-chip RC oscillator
#define  TONEON   0x12             //0b1000 0001 0010  Turn on tone outputs
#define  TONEOFF  0x10             //0b1000 0001 0000  Turn off tone outputs
#define  WDTDIS1  0x0A             //0b1000 0000 1010  Disable WDT time-out flag output

#define MODE_CMD  0x08
#define MODE_DATA 0x05

#define BATTERY_SEG 0x80
#define DOT_SEG     0x80



#define CS1 (GPIOC->BSRR = (1 << 15))
#define CS0 (GPIOC->BSRR = (1 << (15 + 16)))
#define WR1 (GPIOC->BSRR = (1 << 14))
#define WR0 (GPIOC->BSRR = (1 << (14 + 16)))
#define DATA1 (GPIOC->BSRR = (1 << 13))
#define DATA0 (GPIOC->BSRR = (1 << (13 + 16)))


HT1621::HT1621(){
	GPIOx_Init(GPIOC, 13,OUTPUT_PP,NOPULL,MODE_OUTPUT_50MHZ);
	GPIOx_Init(GPIOC, 14,OUTPUT_PP,NOPULL,MODE_OUTPUT_50MHZ);
	GPIOx_Init(GPIOC, 15,OUTPUT_PP,NOPULL,MODE_OUTPUT_50MHZ);
	wrCmd(BIAS);
	wrCmd(RC256);
	wrCmd(SYSDIS);
	wrCmd(WDTDIS1);
	wrCmd(SYSEN);
	wrCmd(LCDON);

	clearAll();
	ValuesConstructor();
}

void HT1621::wrBytes(uint8_t addr,uint8_t sdata){
	  addr<<=2;
	  CS0;
	  sendBits(0xa0,3);     //Write following to data memory
	  sendBits(addr,6);     // at address addr
	  sendBits(sdata,8);    // this is the data to be written.
	  CS1;
}




void HT1621::wrCmd(uint8_t cmd){
	  CS0;
	  sendBits(0x80,4);
	  sendBits(cmd,8);
	  CS1;
}


void HT1621::All_on(){
		uint8_t addr=0;
//		for (uint8_t i=0;i<=0x32;++i){
//			  wrBytes(addr,0xff);
//		      addr+=2;
//		      HAL_Delay(1000);
//		      clearAll();
//		}

		// wrBytes(0x0E,0xff);
		uint8_t tmp[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
		 		for (uint8_t i=0;i<8;++i){
		 			  wrBytes(16,tmp[i]);
		 		      //addr+=2;
		 		      HAL_Delay(1000);
		 		      clearAll();
		 		}
}

void HT1621::sendBits(uint8_t sdata,uint8_t size){
	uint8_t i;
	for (i=0;i<size;i++){
		WR0;
		//delay_us(1);
		if (sdata & 0x80) DATA1;
		else DATA0;
		//delay_us(1);
		WR1;
		//delay_us(1);
		sdata <<= 1;
	}
}

void HT1621::displayOn()
{
	wrBytes(0x0E,0x01<<3);
	wrBytes(0x30,0x8C);
	wrBytes(0x0A,0x01);
	wrBytes(0x0E,0x80);
	//wrBytes(0x18,0x80);
	//wrBytes(0x06,0x10);


}


void HT1621::clearAll(){
	uint8_t addr=0;
	for (uint8_t i=0;i<32;++i){
		  wrBytes(addr,0x00);
	      addr+=2;
	}
}

void HT1621::ValuesConstructor(){
  this->HT1621_data.map2[0]= 0x5F;  //'0'
  this->HT1621_data.map2[1]= 0x06;  //'1'
  this->HT1621_data.map2[2]= 0x6B;  //'2'
  this->HT1621_data.map2[3]= 0x2F;  //'3'
  this->HT1621_data.map2[4]= 0x36;  //'4'
  this->HT1621_data.map2[5]= 0x3D;  //'5'
  this->HT1621_data.map2[6]= 0x7D;  //'6'
  this->HT1621_data.map2[7]= 0x27;  //'7'
  this->HT1621_data.map2[8]= 0x7F;  //'8'
  this->HT1621_data.map2[9]= 0x3F;  //'9'


  this->HT1621_data.map1[0]= 0xAF;  //'0'
  this->HT1621_data.map1[1]= 0x06;  //'1'
  this->HT1621_data.map1[2]= 0x6D;  //'2'
  this->HT1621_data.map1[3]= 0x4F;  //'3'
  this->HT1621_data.map1[4]= 0xC6;  //'4'
  this->HT1621_data.map1[5]= 0xCB;  //'5'
  this->HT1621_data.map1[6]= 0xEB;  //'6'
  this->HT1621_data.map1[7]= 0x4E;  //'7'
  this->HT1621_data.map1[8]= 0xEF;  //'8'
  this->HT1621_data.map1[9]= 0xCF;  //'9'

  this->HT1621_data.map[0]= 0x20;  //'-'
  this->HT1621_data.map[1]= 0x00;  //' '

  this->HT1621_data.digit[0]=0x00;
  this->HT1621_data.digit[1]=0x00;
  this->HT1621_data.digit[2]=0x00;
  this->HT1621_data.digit[3]=0x00;
  this->HT1621_data.digit[4]=0x00;
  this->HT1621_data.digit[5]=0x00;
}
//convert -> blacking -> refresh.

void HT1621::Convert(uint8_t a,uint8_t line,uint8_t tmp){
	uint8_t Current_Digit;
	if ((a > 1000) || (a < 0)) {
		for (uint8_t i=0;i<5;++i) {
			this->HT1621_data.digit[i] =this->HT1621_data.map[10];
		}
		return;
	}
    for(Current_Digit = tmp;a>0; ++Current_Digit){
      if (line==1) this->HT1621_data.digit[Current_Digit]=this->HT1621_data.map1[a%10];
      else this->HT1621_data.digit[Current_Digit]=this->HT1621_data.map2[a%10];
      a/=10;
    }
}


void HT1621::Write_Float_Linex(float a,uint8_t line){
	uint8_t h1[4]={0x08,0x06,0x04,0x02};
	uint8_t h2[4]={0x1A,0x18,0x16,0x14};
	for (uint8_t i=0;i<6;++i) this->HT1621_data.digit[i]=0x00;
	if (line ==1 ) {
		for (uint8_t i=0;i<4;++i) wrBytes(h1[i],0x00);
	}
	else {
		for (uint8_t i=0;i<4;++i) wrBytes(h2[i],0x00);
	}

	uint8_t x=(a-(uint8_t)a)*10;
	if (line==1){
		this->HT1621_data.digit[0]=this->HT1621_data.map1[x];
	}
	else {
		this->HT1621_data.digit[0]=this->HT1621_data.map2[x];
	}
	Convert((uint8_t)a,line,1);
	for(uint8_t i=0;this->HT1621_data.digit[i]!=0x00;++i){
		if (i==1) {
			if (line==1){
				this->HT1621_data.digit[i] |= 0x10;
			}
			else {
				this->HT1621_data.digit[i] |= 0x80;
			}
		}
		if (line==1){
			wrBytes(h1[i],this->HT1621_data.digit[i]);
		}
		else {
			wrBytes(h2[i],this->HT1621_data.digit[i]);
		}

	}
}


void HT1621::Write_Id(uint8_t a){
	uint8_t h1[4]={0x08,0x06,0x04,0x02};
	uint8_t h2[4]={0x1A,0x18,0x16,0x14};
	for (uint8_t i=0;i<6;++i) this->HT1621_data.digit[i]=0x00;
	for (uint8_t i=0;i<4;++i) wrBytes(h1[i],0x00);
	for (uint8_t i=0;i<4;++i) wrBytes(h2[i],0x00);
	/////phu

	wrBytes(16,0x0C);
	wrBytes(14,0x80);
	wrBytes(h1[3],0x06);
	wrBytes(h1[2],0x67);
	/////////////////////
	Convert((uint8_t)a,2,0);
	for(uint8_t i=0;this->HT1621_data.digit[i]!=0x00;++i){
		wrBytes(h2[i],this->HT1621_data.digit[i]);
	}
}
