#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include <rc/time.h>
#include <rc/encoder.h>
#include <rc/motor.h>

using namespace std ;

int main(int argc, char* [])
{
    int ch_encoder = 2 ;
    int ch_motor = 1 ;
    int pos = 0 ;
    int status ;
    double speed = 0.0 ;
    int single_round = 3840 ;
    
    status = rc_encoder_init() ;
    cout << status << endl ;
    if (status < 0) return -1 ;
    
    status = rc_motor_init() ;
    cout << status << endl ;
    if (status < 0) return -1 ;
    
    rc_encoder_write(ch_encoder, pos) ;
    
    cout << "input speed : " ;
    cin >> speed ;
    
    rc_motor_set(ch_motor, speed) ;
    
    while (1) {
        pos = rc_encoder_read(ch_encoder) ;
        // printf("\r%5d", pos) ;
        // fflush(stdout) ;
        // rc_usleep(1000 * 100) ;
        if (abs(pos) > single_round) {
            break ;
        }
    }
    
    rc_encoder_cleanup() ;
    rc_motor_cleanup() ;
    return 0 ;
}
