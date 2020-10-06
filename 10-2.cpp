#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include <rc/motor.h>
#include <rc/time.h>

using namespace std ;

int main(int argc, char* [])
{
    int ch = 1 ;
    int status ;
    int freq = RC_MOTOR_DEFAULT_PWM_FREQ ;
    
    rc_motor_init_freq(freq) ;

    rc_motor_set(ch, 0.5) ;
    rc_usleep(1000 * 3000) ;
    
    rc_motor_set(ch, -0.5) ;
    rc_usleep(1000 * 3000) ;
    
    rc_motor_cleanup() ;
    
    return 0 ;
}

