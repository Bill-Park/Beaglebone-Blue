#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>

using namespace std ;
using namespace std::chrono ;

#define GPIO_PATH "/sys/class/gpio/gpio"
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"

int write_to_path(const char* path, string value)
{
    int f ;
    f = open(path, O_WRONLY | O_CLOEXEC) ;
    if (f < 0) {
        return -1 ;
    }
    write(f, value.c_str(), value.length()) ;
    close(f) ;
    return 0 ;
}

void read_from_path(const char* path, char* buffer, int length)
{
    int f ;
    f = open(path, O_RDONLY | O_CLOEXEC) ;
    read(f, buffer, length) ;
    close(f) ;
}

int main(int argc, char* [])
{
    int f_export, f_unexport, status ;
    string echo = "113" ; // 제일 밖
    string trig = "116" ;
    
    f_export = open(GPIO_EXPORT, O_WRONLY | O_CLOEXEC) ;
    cout << f_export << endl ;
    if (f_export < 0) {
        return -1 ;
    }
    status = write(f_export, echo.c_str(), echo.length()) ;
    status = write(f_export, trig.c_str(), trig.length()) ;
    
    close(f_export) ;
    
    status = write_to_path((GPIO_PATH + trig + "/direction").c_str(), "out") ;
    cout << "function " << status << endl ;
    if (status < 0) {
        return -1 ;
    }
    
    write_to_path((GPIO_PATH + trig + "/value").c_str(), "1") ;
    usleep(10) ;
    
    write_to_path((GPIO_PATH + trig + "/value").c_str(), "0") ;
    
    // read_from_path
    int f_echo ;
    char buf[5] = "" ;
    system_clock::time_point start, end ;
    system_clock::time_point timeout = system_clock::now() ;
    microseconds micro ;
    
    while (1) { // High까지 대기, 타이머시작
        // f_echo = open((GPIO_PATH + echo + "/value").c_str(), O_RDONLY | O_CLOEXEC) ;
        // read(f_echo, buf, 1) ;
        // close(f_echo) ;
        read_from_path((GPIO_PATH + echo + "/value").c_str(), buf, 1) ;
        if (buf[0] == '1') {
            start = system_clock::now() ;
            break ;
        } else {
            micro = duration_cast<microseconds>(system_clock::now() - timeout) ;
            if (micro.count() > 3000) {
                return -1 ;
            }
        }
    }
    
    while (1) { // LOW 까지 대기, 타이머 종료
        // f_echo = open((GPIO_PATH + echo + "/value").c_str(), O_RDONLY | O_CLOEXEC) ;
        // read(f_echo, buf, 1) ;
        // close(f_echo) ;
        read_from_path((GPIO_PATH + echo + "/value").c_str(), buf, 1) ;
        if (buf[0] == '0') {
            end = system_clock::now() ;
            break ;
        }
    }
    
    micro = duration_cast<microseconds>(end - start) ;
    
    cout << "length " << micro.count() / 58 << " cm" << endl ;
    
    f_unexport = open(GPIO_UNEXPORT, O_WRONLY  | O_CLOEXEC) ;
    cout << "unexport " << f_unexport << endl ;
    if (f_export < 0) {
        return -1 ;
    }
    write(f_unexport, echo.c_str(), echo.length()) ;
    write(f_unexport, trig.c_str(), trig.length()) ;
    
    close(f_unexport) ;
    
    return 0 ;
}



// 113 - echo

// 116 - trig

// export로 경로 추가
// trig direction 바꾸기

// trig에 10us high

// echo 시간값으로 읽기