//
// Created by luis on 11/3/24.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "funcoes.h"
#include "Ray.h"



class Ray;


class Sphere{
public:
    Ponto3D center;
    double radius;
    Ponto3D k_d; //material difuso
    Ponto3D k_e; //material especular
    Ponto3D k_a; //luz ambiente
    double alpha;
    Sphere(Ponto3D center_=0, double radius_=0, Ponto3D k_d_=0, Ponto3D k_e_=0, Ponto3D k_a_=0, double alpha_=0);
    bool intersecao(const Ray& raio, double& t);
    Ponto3D iluminacao(Ponto3D Pt, Ponto3D dr, Ponto3D P_F, Ponto3D I_F, Ponto3D I_A) const;


};



#endif //SPHERE_H
