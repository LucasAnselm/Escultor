#include "Escultor.hpp"
#include <iostream>

Sculptor::Sculptor(int _nx,int _ny,int _nz){

    int nx = _nx;
    int ny = _ny;
    int nz = _nz;

    if(nx<0){

        std::cout<<"erro";

    }else if (ny<0){

        std::cout<<"erro";

    }else if(nz<0){

        std::cout<<"erro";

    }

};
