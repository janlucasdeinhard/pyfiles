// Test
#include <iostream>
#include <dos.h>

using namespace std;

int main(){

    cout<<"Ringing..."<<endl;
    sound(500);
    delay(2);
    cout<<"Should be done now"<<endl;
    return 0;
}
