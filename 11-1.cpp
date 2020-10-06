#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include <rc/time.h>
#include <rc/encoder.h>

using namespace std ;

int main(int argc, char* [])
{
    int ch = 2 ;
    int pos = 0 ;
    int status ;
    
    status = rc_encoder_init() ;
    cout << status << endl ;
    if (status < 0) return -1 ;
    
    rc_encoder_write(ch, pos) ;
    
    while (1) {
        pos = rc_encoder_read(ch) ;
        cout << pos << endl ;
        rc_usleep(1000 * 100) ;
    }
    
    rc_encoder_cleanup() ;
    return 0 ;
}
