#include <p18f4550.h>
#include <pic_libs.h>
#include <pic_delays.h>

unsigned char read_EEPROM (unsigned char address){
	unsigned char ret;
	EEADR = address;
	
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
	ret = EEDATA;
	return ret;
	}

void write_EEPROM (unsigned char address, unsigned char data){
	EEADR = address;
	EEDATA = data;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	EECON2 = 0x55;
	EECON2 = 0x0AA;
	EECON1bits.WR = 1;
	EECON1bits.WREN = 0;
	}	

void ADCON_config (int port){//Configura com 0 para ventilador, 1 para LED
	if (port==0)
		ADCON1=0x0e;
	else
		ADCON1=0x0f;

	ADCON2 =0b10001000; //Justificado na direita, 2Tad
	ADCON0 =1; //Liga adcon, channel 00 AN0
	}

unsigned char ADCON_read() {
	int result;
	ADCON0 = ADCON0 | 0b10; // Liga a conversao AD
	while (ADCON0bits.GO); // pool p/ Conversor AD
	delay_100ms();
	result =  ADRESL; // Lꡯ resultado da convers䯍
	return result;
}

//NAO ESQUECER DO PRAGMA (#pragma config CCP2MX = ON PARA MOTOR2)
void PWM_MOTOR2_config (){
	MOTOR2_EN_DIR = 1;
	PR2 = 0xff;
	TMR2 = 0; 				//Contador do pwm
	CCPR2L = 0x00;			// Duty Cycle do pwm (MSB)
	CCP2CON &= 0xFFCF; 		// Duty Cycle do pwm (LSB)
	T2CON = 0b0000100; 		//Enable do timer p/ pwm + Prescale = 1
}
void MOTOR2_config(){
	PWM_MOTOR2_config();
	MOTOR2S1_DIR = OUTPUT;
	MOTOR2S2_DIR = OUTPUT;
}

void PWM_MOTOR2_write(unsigned int pwm){
	if (pwm < 0x400){
		CCPR2L = (pwm & 0x3FC)>>2;
		CCP2CON &=0xFFCF+(pwm & 0x3)<<4;
		}
	else
		{
		CCPR2L = (0 & 0x3FC)>>2;
		CCP2CON &= 0xFFCF+((0 & 0x3)<<4);
		}
}

void SERIAL_Config(){
  	RCSTAbits.SPEN = 1;
  	TRISCbits.RC7 = 1;
  	TRISCbits.RC6 = 1;
	SPBRG=25;
	SPBRGH = 0;
}

void SERIAL_Transmit(char c){
//1. Initialize the SPBRGH:SPBRG registers for the
//appropriate baud rate. Set or clear the BRGH
//and BRG16 bits, as required, to achieve the
//desired baud rate.

  BAUDCONbits.BRG16 = 0;
  TXSTAbits.BRGH = 1;
/*
2. Enable the asynchronous serial port by clearing
bit, SYNC, and setting bit, SPEN.
*/
  TXSTAbits.SYNC = 0;
  RCSTAbits.SPEN = 1;
/*
3. If the signal from the TX pin is to be inverted, set
the TXCKP bit.
*/
  BAUDCONbits.TXCKP = 0;
//4. If interrupts are desired, set enable bit, TXIE.
  PIE1bits.TXIE = 0;
/*
5. If 9-bit transmission is desired, set transmit bit,
TX9. Can be used as address/data bit.
*/
  TXSTAbits.TX9 = 0;
/*6. Enable the transmission by setting bit, TXEN,
which will also set bit, TXIF.
*/
  TXSTAbits.TXEN = 1;
/*
7. If 9-bit transmission is selected, the ninth bit
should be loaded in bit, TX9D.
*/
  TXSTAbits.TX9D = 0;
/*
8. Load data to the TXREG register (starts
transmission).
*/
  TXREG = c;
/*
9. If using interrupts, ensure that the GIE and PEIE
bits in the INTCON register (INTCON<7:6>) are
set.
*/ 
  INTCONbits.GIE = 0;
  INTCONbits.PEIE = 0;
}

char SERIAL_Receive(){
  char received=0, temp=0;
//1. Initialize the SPBRGH:SPBRG registers for the
//appropriate baud rate. Set or clear the BRGH
//and BRG16 bits, as required, to achieve the
//desired baud rate.

  SPBRG=25;
  SPBRGH = 0;
  BAUDCONbits.BRG16 = 0;
  TXSTAbits.BRGH = 1;
/*
2. Enable the asynchronous serial port by clearing
bit, SYNC, and setting bit, SPEN.
*/
  TXSTAbits.SYNC = 0;
  RCSTAbits.SPEN = 1;
/*
3. If the signal at the RX pin is to be inverted, set
the RXDTP bit.
*/
  BAUDCONbits.RXDTP = 0;
//4. If interrupts are desired, set enable bit, RCIE.
  PIE1bits.RCIE = 0;
/*
5. If 9-bit reception is desired, set bit, RX9.
*/
  RCSTAbits.RX9 = 0;
/*6. Enable the reception by setting bit, CREN.
*/
  RCSTAbits.CREN   = 1;
/*
7. Flag bit, RCIF, will be set when reception is
complete and an interrupt will be generated if
enable bit, RCIE, was set.
*/
	do {
	temp = PIR1bits.RCIF;
	} while(!temp);
	
/*
8. Read the RCSTA register to get the 9th bit (if
enabled) and determine if any error occurred
during reception.
*/
/*
9. Read the 8-bit received data by reading the
RCREG register.
*/ 

  received = RCREG;
	Nop();
/*

10. If any error occurred, clear the error by clearing
enable bit, CREN.
*/
  RCSTAbits.CREN = 0;
/*
11. If using interrupts, ensure that the GIE and PEIE
bits in the INTCON register (INTCON<7:6>) are
set.
*/
	INTCONbits.GIE = 0;
	INTCONbits.PEIE = 0;
	return received;
}

void SERIAL_StringTransmit(char *word){
	int i = 0;
	while (word[i]!=0){
		SERIAL_Transmit(word[i]);
		delay_10ms();
		i++;
	}
}

char *SERIAL_StringReceive(){
	char received[100], i=-1; 
	do {
		i++;
		received[i]=SERIAL_Receive();
	} while (received[i]!='\0');
	received[i+1] = 0;
	return received;
}
