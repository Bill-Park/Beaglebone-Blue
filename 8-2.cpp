#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>

using namespace std ;

#define GPIO_PATH "/sys/class/gpio/gpio"
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"

int write_to_path(const char* path, string value)
{
    int f ;
    cout << path << endl ;
    f = open(path, O_WRONLY | O_CLOEXEC) ;
    if (f < 0) {
        return -1 ;
    }
    write(f, value.c_str(), value.length()) ;
    close(f) ;
    return 0 ;
}

int main(int argc, char* [])
{
    int f_export, f_unexport, status ;
    string echo = "113" ;
    string trig = "116" ;
    
    f_export = open(GPIO_EXPORT, O_WRONLY | O_CLOEXEC) ;
    cout << f_export << endl ;
    if (f_export < 0) {
        return -1 ;
    }
    status = write(f_export, echo.c_str(), echo.length()) ;
    cout << "echo set " << status << endl ;
    status = write(f_export, trig.c_str(), trig.length()) ;
    cout << "trig set " << status << endl ;
    
    close(f_export) ;
    
    status = write_to_path((GPIO_PATH + trig + "/direction").c_str(), "out") ;
    cout << "function " << status << endl ;
    
    status = write_to_path((GPIO_PATH + trig + "/value").c_str(), "1") ;
    cout << "trig " << status << endl ;
    usleep(10) ;
    
    status = write_to_path((GPIO_PATH + trig + "/value").c_str(), "0") ;
    cout << "trig " << status << endl ;
    
    // read_from_path
    int f_trig ;
    char buf[5] = "" ;
    f_trig = open((GPIO_PATH + echo + "/value").c_str(), O_RDONLY | O_CLOEXEC) ;
    if (f_trig < 0) {
        return f_trig ;
    }
    while (1) {
        read(f_trig, buf, 1) ;
        cout << buf << endl ;
        if (buf[0] == '1') {
            break ;
        }
    }
    
    // status = read(f_trig, buf, 1) ;
    // cout << "read " << status << " " << buf << endl ;
    // High까지 대기, 타이머시작
    
    // LOW 까지 대기, 타이머 종료
    
    
    
    
    // f_unexport = open(GPIO_UNEXPORT, O_WRONLY  | O_CLOEXEC) ;
    // cout << f_unexport << endl ;
    // if (f_export < 0) {
    //     return -1 ;
    // }
    // status = write(f_unexport, echo.c_str(), echo.length()) ;
    // cout << status << endl ;
    // status = write(f_unexportf_export, trig.c_str(), trig.length()) ;
    // cout << status << endl ;
    
    // close(f_unexport) ;
    
    
    return 0 ;
}



// 113 - echo

// 116 - trig

// export로 경로 추가
// trig direction 바꾸기

// trig에 10us high

// echo 시간값으로 읽기