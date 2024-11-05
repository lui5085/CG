//
// Created by luis on 11/3/24.
//

#ifndef RAY_H
#define RAY_H
#include "funcoes.h"
#include "Plane.h"
#include "Sphere.h"


class Ray{
public:
    Ponto3D origem;
    Ponto3D direcao;

    Ray(Ponto3D origem_=0, Ponto3D direcao_=0);

};



#endif //RAY_H
