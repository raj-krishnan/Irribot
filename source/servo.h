void servo1_pin_config (void)
{
 DDRB  = DDRB | 0x20;  //making PORTB 5 pin output
 PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1
}

void servo2_pin_config (void)
{
 DDRB  = DDRB | 0x40;  //making PORTB 6 pin output
 PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1
}

void servoPinConfig (void)
{
	servo1_pin_config();
	servo2_pin_config();
}

void timer1_init(void)
{
	TCCR1B = 0x00;
	TCNT1H = 0xFC;
	TCNT1L = 0x01;	
	
	OCR1AH = 0x03;	
	OCR1AL = 0xFF;	
	OCR1BH = 0x03;	
	OCR1BL = 0xFF;	
	OCR1CH = 0x03;	
	OCR1CL = 0xFF;	
	
	ICR1H  = 0x03;	
	ICR1L  = 0xFF;
	
	TCCR1A = 0xAB; 

	TCCR1C = 0x00;
	TCCR1B = 0x0C;
}

void rotateServo(unsigned char degrees)  
{
	float PositionTiltServo = 0;
	PositionTiltServo = ((float)degrees / 1.86) + 35.0;
	OCR1AH = 0x00;
 	OCR1AL = (unsigned char) PositionTiltServo;
}

void rotateWaterArm(unsigned char degrees)
{
	float PositionTiltServo = 0;
	PositionTiltServo = ((float)degrees / 1.86) + 35.0;
	OCR1BH = 0x00;
	OCR1BL = (unsigned char) PositionTiltServo;
}

void servo_1_free (void) //makes servo 1 free rotating
{
 OCR1AH = 0x03; 
 OCR1AL = 0xFF; //Servo 1 off
}

void servo_2_free (void) //makes servo 2 free rotating
{
 OCR1BH = 0x03;
 OCR1BL = 0xFF; //Servo 2 off
}