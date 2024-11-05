//
// Created by luis on 11/3/24.
//

#ifndef PLANE_H
#define PLANE_H
#include "funcoes.h"
#include "Ray.h"


class Ray;


class Plane{
public:
    Ponto3D floor;
    Ponto3D normal;
    Ponto3D k_d; //material difuso
    Ponto3D k_e; //material especular
    Ponto3D k_a; //luz ambiente
    double alpha;

    Plane(Ponto3D floor_=0, Ponto3D normal_=0, Ponto3D k_d_=0, Ponto3D k_e_=0, Ponto3D k_a_=0, double alpha_=0);
    bool intersecao(const Ray& raio, double& t);
    Ponto3D iluminacao(Ponto3D Pt, Ponto3D dr, Ponto3D P_F, Ponto3D I_F, Ponto3D I_A) const;


};



#endif //PLANE_H
