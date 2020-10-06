#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>

using namespace std ;

#define GPIO_PATH "/sys/class/gpio/gpio"
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"

int main(int argc, char* [])
{
    int f_export, f_unexport, status ;
    string echo = "113" ;
    string trig = "116" ;
    f_export = open(GPIO_EXPORT, O_WRONLY  | O_CLOEXEC) ;
    cout << f_export << endl ;
    if (f_export < 0) {
        return -1 ;
    }
    status = write(f_export, echo.c_str(), echo.length()) ;
    cout << status << endl ;
    status = write(f_export, trig.c_str(), trig.length()) ;
    cout << status << endl ;
    
    close(f_export) ;
    
    return 0 ;
}



// 113 - echo

// 116 - trig

// export로 경로 추가
// trig direction 바꾸기

// trig에 10us high

// echo 시간값으로 읽기