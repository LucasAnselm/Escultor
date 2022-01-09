#include "Escultor.hpp"
#include <iostream>

Sculptor::Sculptor(int _nx,int _ny,int _nz){

     nx = _nx;
     ny = _ny;
     nz = _nz;



};

Sculptor::~Sculptor(){


}

void Sculptor::setColor(float _r, float _g, float _b, float _alpha){

    if(_r>1){

        r = 1;

    }else if (_r<1){

        r = 0;

    }else{

        r = _r;

    }
    if(_g>1){

        g = 1;

    }else if (_g<1){

        g = 0;

    }else{

        g = _g;

    }
    if(_b>1){

        b = 1;

    }else if (_b<1){

        b = 0;

    }else{

        b = _b;

    }
    if(_alpha>1){

        alpha = 1;

    }else if (_alpha<1){

        alpha = 0;

    }else{

        alpha = _alpha;

    }

};

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){




};
