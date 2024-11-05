//
// Created by luis on 11/3/24.
//

#include "Ray.h"

Ray::Ray(Ponto3D origem_, Ponto3D direcao_) {
    origem = origem_;
    direcao = funcoes::Ponto3D_Normalizado(direcao_);
}




