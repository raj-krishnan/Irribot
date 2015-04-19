volatile unsigned long int ShaftCountLeft = 0; //to keep track of left position encoder
volatile unsigned long int ShaftCountRight = 0; //to keep track of right position encoder
volatile unsigned int Degrees; //to accept angle in degrees for turning

void left_encoder_pin_config (void)
{
	//Function to configure INT4 (PORTE 4) pin as input for the left position encoder	

	DDRE  = DDRE & 0xEF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x10; //Enable internal pull-up for PORTE 4 pin
}

void right_encoder_pin_config (void)
{
	//Function to configure INT5 (PORTE 5) pin as input for the right position encoder

	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 4 pin
}

void encoder_port_init()
{
	//Function to initialize ports

	left_encoder_pin_config(); //left encoder pin config
	right_encoder_pin_config(); //right encoder pin config
}

void left_position_encoder_interrupt_init (void) //Enables Interrupt 4
{
	cli(); 
	EICRB = EICRB | 0x02; 
	EIMSK = EIMSK | 0x10; 
	sei();   
}

void right_position_encoder_interrupt_init (void) //Enables Interrupt 5
{
	cli(); 
	EICRB = EICRB | 0x08; 
	EIMSK = EIMSK | 0x20; 
	sei();
}

ISR(INT5_vect)
{
	//ISR for right position encoder

	ShaftCountRight++;  
}

ISR(INT4_vect)
{
	//ISR for left position encoder

	ShaftCountLeft++;  
}

unsigned long int distance(void)
{
	float distance = 0;
	unsigned long int distanceInt = 0;

	distance = (ShaftCountRight + ShaftCountLeft) * 5.338 / 2.0; 
	distanceInt = (unsigned long int) distance;
	
	return distanceInt;
}


//Function used for turning robot by specified degrees
void angle_rotate(unsigned int Degrees)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt))
		break;
	}
	stop();
}

//Function used for moving robot forward by specified distance

void linear_distance_mm(unsigned int DistanceInMM)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = DistanceInMM / 5.338; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
	
	ShaftCountRight = 0;
	while(1)
	{
		if(ShaftCountRight > ReqdShaftCountInt)
		{
			break;
		}
	}
	stop();
}

void forward_mm(unsigned int DistanceInMM)
{
	forward();
	linear_distance_mm(DistanceInMM);
}

void back_mm(unsigned int DistanceInMM)
{
	back();
	linear_distance_mm(DistanceInMM);
}

void left_degrees(unsigned int Degrees)
{
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	left();
	angle_rotate(Degrees);
}

void right_degrees(unsigned int Degrees)
{
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	right();
	angle_rotate(Degrees);
}


void soft_left_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left();
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

void soft_right_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right();
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

void soft_left_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left_2();
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}

void soft_right_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right_2();
	Degrees=Degrees*2;
	angle_rotate(Degrees);
}