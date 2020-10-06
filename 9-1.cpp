#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h> // for atoi
#include <signal.h>

#include <rc/time.h>
#include <rc/adc.h>
#include <rc/dsm.h>
#include <rc/servo.h>

using namespace std ;

int main(int argc, char* [])
{
    int ch = 1 ;
    int status ;
    status = rc_adc_init() ;
    cout << "adc_init " << status << endl ;
    
    status = rc_adc_batt() ;
    cout << "adc batt " << status << endl ;
    
    rc_adc_cleanup() ;
    
    status = rc_servo_init() ;
    cout << "servo init " << status << endl ;
    
    rc_servo_power_rail_en(1) ; // power enable
    
    rc_servo_send_pulse_us(ch, 1300) ;
    rc_usleep(1000 * 1000) ;
    
    rc_servo_send_pulse_us(ch, 1500) ;
    rc_usleep(1000 * 1000) ;
    
    rc_servo_send_pulse_us(ch, 1800) ;
    rc_usleep(1000 * 1000) ;
    
    rc_servo_power_rail_en(0) ;
    rc_servo_cleanup() ;
    
    return 0 ;
}