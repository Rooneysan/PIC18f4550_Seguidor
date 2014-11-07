#include <p18f4550.h>
#include <pic_pins.h>
#include <pic_libs.c>
#include <pic_delays.h>

#pragma config WDT = OFF // Configura watchdog timer
#pragma config FOSC = HS // Configura oscilador
#pragma config LVP = OFF // Configura  low voltage
#pragma config CCP2MX = ON //PWM no VENTILADOR
/* Conversão hexadecimal para o display de 7 segmentos
*/
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

void ADCON_config (int port);//Configura com 0 para ventilador, 1 para LED

unsigned char ADCON_read();
//NAO ESQUCER DO PRAGMA (#pragma config CCP2MX = ON PARA VENTILADOR)
void MOTOR2_config();

void PWM_MOTOR2_write(unsigned int pwm);

void SERIAL_Config();

void SERIAL_Transmit(char c);

void SERIAL_StringTransmit(char *word);

