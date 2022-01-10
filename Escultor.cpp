#include <fstream>
#include "Escultor.hpp"
#include <iostream>




Sculptor::Sculptor(int _nx,int _ny,int _nz){

     nx = _nx;
     ny = _ny;
     nz = _nz;

     v = new Voxel**[nx];
         for(int i=0; i<nx; i++){
             v[i] = new Voxel*[ny];
             for(int j=0; j<ny; j++){
                v[i][j] = new Voxel[nz];
             }
         }

         for(int i = 0; i<nx; i++){
             for(int j = 0; j<ny; j++){
                 for(int k = 0; k<nz; k++){
                     v[i][j][k].r = 0;
                     v[i][j][k].g = 0;
                     v[i][j][k].b = 0;
                     v[i][j][k].a = 0;
                     v[i][j][k].isOn = false;
                 }
             }
         }

     }

Sculptor::~Sculptor(){
    std::cout << "Objeto destruido\n";
    if(nx == 0 || ny == 0 || nz ==0){
            return;
     }

    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
               delete [] v[i][j];
         }
                 delete [] v[i];
     }
                 delete [] v;
};





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

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = alpha;
    v[x][y][z].isOn = true;
}

void Sculptor::writeOFF(char* filename){

    std::ofstream exit;
    exit.open(filename);
    int i, j, k, total=0;

    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn==true){
                    total++;
                }
            }
        }
    }

    exit << "OFF\n";
    exit << total*8 << " " << total*6 << " " << "0\n";
    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn == true){
                    exit << i-0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    exit << i-0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    exit << i+0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    exit << i+0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    exit << i-0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                    exit << i-0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    exit << i+0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    exit << i+0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                }
            }
        }
    }
    total=0;
    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn==true){
                    int aux = 8*total;
                    exit << "4 " << aux << " " << aux+3 << " " << aux+2 << " " << aux+1 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    exit << "4 " << aux+4 << " " << aux+5 << " " << aux+6 << " " << aux+7 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    exit << "4 " << aux << " " << aux+1 << " " << aux+5 << " " << aux+4 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    exit << "4 " << aux << " " << aux+4 << " " << aux+7 << " " << aux+3 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    exit << "4 " << aux+3 << " " << aux+7 << " " << aux+6 << " " << aux+2 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    exit << "4 " << aux+1 << " " << aux+2 << " " << aux+6 << " " << aux+5 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    aux++;
                }
            }
        }
    }
    exit.close();
}

