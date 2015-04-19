/********************************************************************************
 
 Written by: Mahen Kinnur    140040024
         Jagesh Golwala  14D070005
             Shivank Kumar   140010024
             Raj Krishnan    140010007
             
 

 Written On: AVR Studio Version 6

 
 This project aims to make an autonomous bot which follows a given white line
 and stops at constant distances as defined below in the constants section.

 On stopping the bot will dip the moisture sensor into the soil and check the
 moisture content three times takes their mean.

 Then, comparing with a predefined optimum value, we will decide whether to water
 the patch and if yes also the amount of water to be dispersed.

 The bot will then continue on its path taking turns at corners as necessary.

*********************************************************************************/

#define F_CPU 14745600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <math.h>

unsigned int water_used = 0; // Change to float if more accuracy is required

unsigned char ADC_Conversion(unsigned char);
void port_init();
void timer5_init();
void motors_delay();

#include "lcd.h"
#include "servo.h"
#include "moistureSensor.h"
#include "motion.h"
#include "shaftcount.h"

unsigned char ADC_Value;
unsigned char Left_white_line = 0;
unsigned char Center_white_line = 0;
unsigned char Right_white_line = 0;
unsigned char Front_Sharp_Sensor=0;
unsigned char Front_IR_Sensor=0;
unsigned char Right_IR_Sensor = 0;
unsigned char Right_Sharp_Sensor = 0;


void lcd_port_config (void)
{
    DDRC = DDRC | 0xF7; //set the LCD pin's direction as output
    PORTC = PORTC & 0x80; // set LCD pins are set to logic 0 except PORTC 7
}

void adc_pin_config (void)
{
    DDRF = 0x00; 
    PORTF = 0x00;
    DDRK = 0x00;
    PORTK = 0x00;
}


void port_init()
{
    lcd_port_config();
    adc_pin_config();
    motion_pin_config();    
    servoPinConfig();
    buzzer_pin_config();
    encoder_port_init();
}

void adc_init()
{
    ADCSRA = 0x00;
    ADCSRB = 0x00;
    ADMUX = 0x20;
    ACSR = 0x80;
    ADCSRA = 0x86;
}

//Function For ADC Conversion
unsigned char ADC_Conversion(unsigned char Ch) 
{
    unsigned char a;

    if(Ch>7)
    {
        ADCSRB = 0x08;
    }

    Ch = Ch & 0x07;             
    ADMUX= 0x20| Ch;            
    ADCSRA = ADCSRA | 0x40;

    while((ADCSRA & 0x10) == 0);

    a=ADCH;
    ADCSRA = ADCSRA|0x10;
    ADCSRB = 0x00;

    return a;
}

void print_sensor(char row, char coloumn,unsigned char channel)
{
    //Function To Print Sesor Values At Desired Row And Coloumn Location on LCD

    ADC_Value = ADC_Conversion(channel);
    lcd_print(row, coloumn, ADC_Value, 3);
}

void init_devices (void)
{
    cli(); //Clears the global interrupts
    port_init();
    adc_init();
    timer1_init();
    timer5_init();
    sei();   //Enables the global interrupts
}

int main()
{

    init_devices();
    lcd_set_4bit();
    lcd_init();
    //int check = 0;
    servo_dig_out();
    water_arm_dig_out();
    buzzer_on();
    _delay_ms(100);
    buzzer_off();
    while(1)
    {

        Left_white_line = ADC_Conversion(3);    //Getting data of Left WL Sensor
        Center_white_line = ADC_Conversion(2);  //Getting data of Center WL Sensor
        Right_white_line = ADC_Conversion(1);   //Getting data of Right WL Sensor
        Right_IR_Sensor = ADC_Conversion(8);
        Right_Sharp_Sensor = ADC_Conversion(13);
        Front_Sharp_Sensor = ADC_Conversion(11);
        Front_IR_Sensor = ADC_Conversion(6);

        //print_sensor(1,1,3);    // Prints value of White Line Sensor1
        //  print_sensor(1,5,2);  // Prints Value of White Line Sensor2
        // print_sensor(1,9,1);   // Prints Value of White Line Sensor3
        lcd_clear();


        if((Left_white_line>0x10) && (Center_white_line>0x10))
        {
            forward();
            velocity(130,50);
            
            lcd_clear();
            print_sensor(1,1,3);    // Prints value of White Line Sensor1
            print_sensor(1,5,2);    // Prints Value of White Line Sensor2
            print_sensor(1,9,1);    // Prints Value of White Line Sensor3
    
        
            lcd_cursor(2,3);
            lcd_string("Moving Right");
        }

        if((Right_white_line>0x10) && (Center_white_line>0x10))
        {
            forward();
            velocity(50,130);
            
            lcd_clear();
            print_sensor(1,1,3);    // Prints value of White Line Sensor1
            print_sensor(1,5,2);    // Prints Value of White Line Sensor2
            print_sensor(1,9,1);    // Prints Value of White Line Sensor3
            lcd_cursor(2,3);
            lcd_string("Moving Left");
        }
        
        if(Center_white_line<0x10)
        {
            forward();
            velocity(200,200);
            print_sensor(1,1,3);    // Prints value of White Line Sensor1
            print_sensor(1,5,2);    // Prints Value of White Line Sensor2
            print_sensor(1,9,1);    // Prints Value of White Line Sensor3
            
            
            lcd_cursor(2,2);
            lcd_string("Moving Forward");
            
            //_delay_ms(100);
            //check += 1;
        }
   
        if(Front_IR_Sensor < 70)
        {
            stop();
			lcd_cursor(2,2);
			lcd_string("Obstacle Ahead");

            // print_sensor(1, 3, 6);   // Front IR Sensor
            // print_sensor(1, 10, 11); // Front Sharp Sensor
			
            buzzer_on();
            _delay_ms(500);
            buzzer_off();
            
            // Takes a U-turn

            soft_right_2_degrees(90);
            soft_right_degrees(90);
        }
        

        if(Center_white_line>0x10 && Left_white_line>0x10 && Right_white_line>0x10)
        {
            stop();
            forward();
            velocity(150,30);
			_delay_ms(300);
        }
        
        if((Right_IR_Sensor<160 && Right_IR_Sensor > 140 && Right_Sharp_Sensor > 60 && Right_Sharp_Sensor < 120))
        {
			back();
            _delay_ms(500);
            stop();
    
            lcd_clear();
            lcd_cursor(1,7);
            lcd_string("Stop");
            lcd_cursor(2,2);
            lcd_string("Pot Obstacle");
            _delay_ms(2000);
            
            lcd_clear();
            lcd_cursor(1,3);
            lcd_string("Measuring the");
            lcd_cursor(2,2);
            lcd_string("moisture level");

            unsigned int moisture = sense();
            forward();
            velocity(200,200);
            _delay_ms(150);
            stop();
            lcd_clear();
            waterPump(moisture);
            _delay_ms(1000);

            servo_dig_out();
            water_arm_dig_out();
            
            lcd_clear();
            lcd_cursor(1,3);
            lcd_string("Moving ahead");
            lcd_cursor(2,6);
            lcd_string("of pot");
            forward();
            velocity(200,200);
            _delay_ms(1000);
            lcd_clear();
        }
    
        if(water_used >= 24) // To make sure bot does not run when tank is empty
                             // (Assuming tank was initially half filled)
            break;
    }

    // Alerts user that tank is empty. Reset bot to stop
    while (1)
    {
        lcd_cursor(1,4);
            lcd_string("Tank Empty");
        stop();
        buzzer_on();
        _delay_ms(400);
        buzzer_off();
        _delay_ms(1600);

    }
}