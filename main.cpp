#include "Escultor.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main(){
    Sculptor scul(100,100,100);




    scul.setColor(0.57,0.3,0,0.5);
    scul.putBox(30,60,30,40,40,60);
    scul.cutBox(32,58,31,40,42,58);

    scul.setColor(0.5,1,1,1);
    scul.putSphere(35,30,42,4);

    scul.setColor(0,0,0,0);
    scul.putSphere(55,30,42,4);

    scul.setColor(0,0,0,0);
    scul.putSphere(35,30,58,4);

    scul.setColor(0,0,0,0);
    scul.putSphere(55,30,58,4);


    scul.writeOFF((char*)"objeto.off");
    return 0;
}
