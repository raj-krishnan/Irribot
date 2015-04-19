unsigned char getMoisture()
{
	unsigned char val = ADC_Conversion(14);
	// lcd_print(2,1,val,3); Uncomment if testing moisture sensed
	
	return val;
}

void water_arm_dig_in()
{
	rotateWaterArm(60); // Values based of angle at which arm is initially attached
						// May vary with differing setup
}

void servo_dig_out()
{
	rotateServo(60); 	// Values based of angle at which arm is initially attached
						// May vary with differing setup
}

void servo_dig_in()
{
	rotateServo(120); 	// Values based of angle at which arm is initially attached
						// May vary with differing setup
}

void water_arm_dig_out()
{
	rotateWaterArm(120); // Values based of angle at which arm is initially attached
						 // May vary with differing setup
}


unsigned int sense()
{
	// Takes three readings of the soil moisture content and returns the average

	unsigned int total = 0;
	
	for(int qqq = 0; qqq<3; qqq++)
	{
		servo_dig_in();
		_delay_ms(4500);
		lcd_clear();
		total += (unsigned int)getMoisture();
		_delay_ms(1000);
		servo_dig_out();
		_delay_ms(1000);
	}

	unsigned int average = (int)round(total/3.0);
	return average;
}

void waterPump(unsigned int observedLevel)
{
	//Turns on the motor pump(time duration decided by the soil moisture level)

	if (observedLevel <= 140)
	{
		lcd_clear();
        lcd_cursor(1,5);
        lcd_string("No need");
        lcd_cursor(2,5);
        lcd_string("to water");
        _delay_ms(1000);
		return; //no need to water
	}
	else
	{	
		lcd_clear();
        lcd_cursor(1,5);
        lcd_string("Watering");
        
        if (observedLevel > 190)
	    {
	    	lcd_cursor(2,3);
        	lcd_string("Low Moisture");
			int time = 3000; // Change to adjust watering time
			water_arm_dig_in();
			_delay_ms(time);
			water_arm_dig_out();
			water_used += 2 * time / 1000; 
		}
		else
		{
			lcd_cursor(2,1);
        	lcd_string("Medium Moisture");
			int time = 1500; // Change to adjust watering time
			water_arm_dig_in();
			_delay_ms(time);
			water_arm_dig_out();
			water_used += 2 * time / 1000;
		}

		return;
	}
}