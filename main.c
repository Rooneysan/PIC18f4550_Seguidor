#include <pic_libs.h>

void main ( ){
	ADCON1=0x0f;
	MOTOR2_config();
	PWM_MOTOR2_write(0x399);
	delay_1000ms();
	PWM_MOTOR2_write(0x0);
	

}

