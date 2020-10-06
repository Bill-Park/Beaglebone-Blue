#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std ;

#define GET_PATH "i2cget -y 2"
#define SET_PATH "i2cset -y 2"

string deviceAddr = " 0x68" ;
string ACC_X_H = " 0x3B" ;
string ACC_X_L = " 0x3C" ;
string ACC_Y_H = " 0x3D" ;
string ACC_Y_L = " 0x3E" ;
string ACC_Z_H = " 0x3F" ;
string ACC_Z_L = " 0x40" ;

string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "fail" ;
    
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    
    pclose(pipe);
    return result;
}

int main(int argc, char* [])
{
    string h_str, l_str ;
    int16_t x_value, y_value, z_value ;
    
    while (1) {
        h_str = exec((GET_PATH + deviceAddr + ACC_X_H).c_str()) ;
        l_str = exec((GET_PATH + deviceAddr + ACC_X_L).c_str()) ;
        x_value = stoi(h_str, nullptr, 16) << 8 | stoi(l_str, nullptr, 16) ;
        
        h_str = exec((GET_PATH + deviceAddr + ACC_Y_H).c_str()) ;
        l_str = exec((GET_PATH + deviceAddr + ACC_Y_L).c_str()) ;
        y_value = stoi(h_str, nullptr, 16) << 8 | stoi(l_str, nullptr, 16) ;
        
        h_str = exec((GET_PATH + deviceAddr + ACC_Z_H).c_str()) ;
        l_str = exec((GET_PATH + deviceAddr + ACC_Z_L).c_str()) ;
        z_value = stoi(h_str, nullptr, 16) << 8 | stoi(l_str, nullptr, 16) ;
        
        cout << x_value << " " << y_value << " " << z_value << endl ;
        usleep(1000 * 500) ;
    }
    
    return 0 ;
}