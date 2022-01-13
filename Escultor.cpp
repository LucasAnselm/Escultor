#include "Escultor.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>



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
void  Sculptor :: cutVoxel ( int x, int y, int z){
    v[x][y][z].isOn = false ;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
               putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int x2, int y2, int z2, int r1){
    for ( int i = 0 ; i <(2*x2); i ++)
    {
        for ( int j = 0 ; j < (2*y2); j ++)
        {
            for ( int k = 0 ; k < (2*z2); k ++)
            {
                if (((i-x2) * (i-x2) + (j-y2) * (j-y2) + (k-z2) * (k-z2)) <= (r1*r1))
                {
                   putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int x2, int y2, int z2, int r1){
    for ( int i = 0 ; i <(2*x2); i ++)
    {
        for ( int j = 0 ; j < (2*y2); j ++)
        {
            for ( int k = 0 ; k < (2*z2); k ++)
            {
                // formula do circulo a^2+b^2+c^2 = r^2
                if (((i-x2) * (i-x2) + (j-y2) * (j-y2) + (k-z2) * (k-z2)) <= (r1*r1))
                {
                   cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int x2, int y2, int z2, int rx, int ry, int rz){

    for(int i=x2-rx; i< x2+rx; i++)
    {
        for(int j=y2-ry; j<y2 + ry; j++)
        {
            for(int k=z2-rz; k< z2+rz; k++)
            {
                if ((pow(i-x2,2)/pow(rx,2)) + (pow(j-y2,2)/pow(ry,2)) + (pow(k-z2,2)/pow(rz,2)) <= 1)
                {
                   putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int x2, int y2, int z2, int rx, int ry, int rz){
    for(int i=x2-rx; i< x2+rx; i++)
    {
        for(int j=y2-ry; j<y2 + ry; j++)
        {
            for(int k=z2-rz; k< z2+rz; k++)
            {
                if ((pow(i-x2,2)/pow(rx,2)) + (pow(j-y2,2)/pow(ry,2)) + (pow(k-z2,2)/pow(rz,2)) <= 1)
                {
                   cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char *nome){
    std::string str;
    std::ofstream f_out;
    f_out.open(nome);

    std::cout<<"Entrou\n";

    if(! f_out.good())
    {
        std::cout << "Falha ao criar arquivo\n";
    }
    else
        std::cout << "Arquivo criado!\n";


    int totalDeElementos = nx*ny*nz;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == false)
                {
                    totalDeElementos--;
                }
            }
        }
    }

    str += "OFF\n";
    str += std::to_string(totalDeElementos*8) + " " + std::to_string(totalDeElementos*6) + " " + "0\n";

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    str += std::to_string(k-0.5) + " " + std::to_string(j+0.5) + " " + std::to_string(i-0.5) + "\n";
                    str += std::to_string(k-0.5) + " " + std::to_string(j-0.5) + " " + std::to_string(i-0.5) + "\n";
                    str += std::to_string(k+0.5) + " " + std::to_string(j-0.5) + " " + std::to_string(i-0.5) + "\n";
                    str += std::to_string(k+0.5) + " " + std::to_string(j+0.5) + " " + std::to_string(i-0.5) + "\n";
                    str += std::to_string(k-0.5) + " " + std::to_string(j+0.5) + " " + std::to_string(i+0.5) + "\n";
                    str += std::to_string(k-0.5) + " " + std::to_string(j-0.5) + " " + std::to_string(i+0.5) + "\n";
                    str += std::to_string(k+0.5) + " " + std::to_string(j-0.5) + " " + std::to_string(i+0.5) + "\n";
                    str += std::to_string(k+0.5) + " " + std::to_string(j+0.5) + " " + std::to_string(i+0.5) + "\n";
                }
            }
        }
    }

    int cont = 0;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    int pos = 8*cont;
                    str += "4 " + std::to_string(pos) + " " + std::to_string(pos+3) + " " + std::to_string(pos+2) + " " + std::to_string(pos+1) + " " + std::to_string(v[i][j][k].r) + " " + std::to_string(v[i][j][k].g) + " " + std::to_string(v[i][j][k].b) + " " + std::to_string(v[i][j][k].a) + "\n";
                    str += "4 " + std::to_string(pos+4) + " " + std::to_string(pos+5) + " " + std::to_string(pos+6) + " " + std::to_string(pos+7) + " " + std::to_string(v[i][j][k].r) + " " + std::to_string(v[i][j][k].g) + " " + std::to_string(v[i][j][k].b) + " " + std::to_string(v[i][j][k].a) + "\n";
                    str += "4 " + std::to_string(pos) + " " + std::to_string(pos+1) + " " +std::to_string(pos+5) + " " + std::to_string(pos+4) + " " + std::to_string(v[i][j][k].r) + " " + std::to_string(v[i][j][k].g) + " " + std::to_string(v[i][j][k].b) + " " + std::to_string(v[i][j][k].a) + "\n";
                    str += "4 " + std::to_string(pos) + " " + std::to_string(pos+4) + " " + std::to_string(pos+7) + " " + std::to_string(pos+3) + " " + std::to_string(v[i][j][k].r) + " " + std::to_string(v[i][j][k].g) + " " + std::to_string(v[i][j][k].b) + " " + std::to_string(v[i][j][k].a) + "\n";
                    str +="4 " + std::to_string(pos+3) + " " + std::to_string(pos+7) + " " + std::to_string(pos+6) + " " + std::to_string(pos+2) + " " + std::to_string(v[i][j][k].r) + " " + std::to_string(v[i][j][k].g) + " " + std::to_string(v[i][j][k].b) + " " + std::to_string(v[i][j][k].a) + "\n";
                    str += "4 " + std::to_string(pos+1) + " " + std::to_string(pos+2) + " " + std::to_string(pos+6) + " " + std::to_string(pos+5) + " " + std::to_string(v[i][j][k].r) + " " + std::to_string(v[i][j][k].g) + " " + std::to_string(v[i][j][k].b) + " " + std::to_string(v[i][j][k].a) + "\n";
                    cont++;
                }
            }
        }
    }

    f_out << str;
    f_out.close();
}
