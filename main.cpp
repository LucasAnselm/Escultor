#include <iostream>
#include <fstream>
#include "Escultor.hpp"

using namespace std;

int main(void){

    Sculptor scu(1.0,1.0,1.0);
    scu.setColor(2.0,1.0,1.0,1.0);
    scu.putVoxel(1,1,1);
    //scu.cutBox(1,8,1,8,1,8);
    scu.writeOFF((char*)"teste.off");

    return 0;

}
