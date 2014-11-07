#include <pic_delays.h>

void delay_1ms() {
  char i;
  for (i = 0; i < 69; i++);
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
}

void delay_5ms() {
  char i;
  for (i = 0; i < 5; i++) delay_1ms();
}

void delay_10ms() {
  char i;
  for (i = 0; i < 9; i++) delay_1ms();
  for (i = 0; i < 59; i++);
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
}

void delay_20ms (){
	delay_10ms ();
	delay_10ms ();
}

void delay_25ms (){
	char i;
	delay_10ms ();
	delay_10ms ();
	for(i=0;i<5;i++)
		delay_1ms ();
}

void delay_100ms() {
  char i;
  for (i = 0; i < 9; i++) delay_10ms();
  for (i = 0; i < 9; i++) delay_1ms();
  for (i = 0; i < 49; i++);
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
}

void delay_1000ms(){
	char i;
	for ( i = 0 ; i < 9 ; i++) delay_100ms ( ) ;
	for ( i = 0 ; i < 9 ; i++) delay_10ms ( ) ;
	for ( i = 0 ; i < 9 ; i++) delay_1ms () ;
	for ( i = 0 ; i < 36 ; i++);
	Nop ( ) ;
	Nop ( ) ;
	Nop ( ) ;
	Nop ( ) ;
	Nop ( ) ;

	
}
