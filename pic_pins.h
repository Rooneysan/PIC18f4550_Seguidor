
// Portas para o L293D
#define MOTOR1EN    	PORTCbits.RC1
#define MOTOR1EN_DIR 	TRISCbits.RC1
#define MOTOR1S1   		PORTBbits.RB4
#define MOTOR1S1_DIR	TRISBbits.RB4
#define MOTOR1S2   		PORTBbits.RB5
#define MOTOR1S2_DIR	TRISBbits.RB5
#define MOTOR2EN    	PORTCbits.RC2
#define MOTOR2EN_DIR 	TRISCbits.RC2
#define MOTOR2S1   		PORTBbits.RB6
#define MOTOR2S1_DIR	TRISBbits.RB6
#define MOTOR2S2   		PORTBbits.RB7
#define MOTOR2S2_DIR	TRISBbits.RB7

// Definições para IO
#define a_ON 1
#define a_OFF 0
#define PORT_ON 0
#define PORT_OFF 1
#define ON 1
#define OFF 0
#define OUTPUT 0
#define INPUT 1
#define OUTPUT_BYTE 	0x00
#define INPUT_BYTE 		0xFF
//Variável Global utilizada nas funções de botão para evitar oscilamento
