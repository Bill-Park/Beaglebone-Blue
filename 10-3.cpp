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
    double speed = 0.0 ;
    int freq = RC_MOTOR_DEFAULT_PWM_FREQ ;
    
    rc_motor_init_freq(freq) ;

    rc_motor_set(ch, speed) ;
    
    cout << "input speed : " ;
    cin >> speed ;
    
    rc_motor_set(ch, speed) ;
    rc_usleep(1000 * 3000) ;
    
    rc_motor_cleanup() ;
    
    return 0 ;
}

