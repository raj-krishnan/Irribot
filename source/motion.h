void timer5_init()
{
    TCCR5B = 0x00;  
    TCNT5H = 0xFF;  
    TCNT5L = 0x01;  
    OCR5AH = 0x00;  
    OCR5AL = 0xFF;  
    OCR5BH = 0x00;  
    OCR5BL = 0xFF;  
    OCR5CH = 0x00;  
    OCR5CL = 0xFF;  
    TCCR5A = 0xA9;  
    
    TCCR5B = 0x0B;  
}


void motion_set (unsigned char Direction)  //Function used for setting motor's direction
{
	unsigned char PortATemp = 0;

	Direction &= 0x0F;
	PortATemp = PORTA;
	PortATemp &= 0xF0;
	PortATemp |= Direction;
	PORTA = PortATemp;
}


void motion_pin_config (void) 
{
	DDRA = DDRA | 0x0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;   
	PORTL = PORTL | 0x18; 
}


void buzzer_pin_config(void)
{
	DDRC = DDRC | 0x08;
	PORTC = PORTC & 0xF7;
}


void velocity (unsigned char left_motor, unsigned char right_motor)
{
	//Function for velocity control

	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}


void forward (void) //both wheels forward
{
	motion_set(0x06);
}


void back (void) //both wheels backward
{
	motion_set(0x09);
}


void left (void) //Left wheel backward, Right wheel forward
{
	motion_set(0x05);
}


void right (void) //Left wheel forward, Right wheel backward
{
	motion_set(0x0A);
}


void soft_left (void) //Left wheel stationary, Right wheel forward
{	
	motion_set(0x04);
}


void soft_right (void) //Left wheel forward, Right wheel is stationary
{	
	motion_set(0x02);
}


void soft_left_2 (void) //Left wheel backward, right wheel stationary
{	
	motion_set(0x01);
}


void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
	motion_set(0x08);
}


void stop (void) //hard stop
{
	motion_set(0x00);
}


void buzzer_on(void)
{
	PORTC = PORTC | 0x08;
}


void buzzer_off(void)
{
	PORTC = PORTC & ~(0x08);
}