//
// Created by luis on 11/3/24.
//

#include "Plane.h"

#include <complex>

Plane::Plane(Ponto3D floor_, Ponto3D normal_, Ponto3D k_d_, Ponto3D k_e_, Ponto3D k_a_, double alpha_){
    floor = floor_;
    normal = normal_;
    k_d = k_d_;
    k_e = k_e_;
    k_a = k_a_;
    alpha = alpha_;
}

bool Plane::intersecao(const Ray& raio, double& t){
    Ponto3D dirV = funcoes::Ponto3D_subtrai(floor, raio.origem);
    double dirDotNormal = funcoes::Ponto3D_produtoEscalar(raio.direcao, normal);
    if (dirDotNormal == 0.0) {
        return false;
    }
    t = funcoes::Ponto3D_produtoEscalar(dirV, normal);
    t = t / dirDotNormal;
    if (t < 0) {
        return false;
    }
    return true;
}

Ponto3D Plane::iluminacao(Ponto3D Pt, Ponto3D dr, Ponto3D P_F, Ponto3D I_F, Ponto3D I_A) const{
    Ponto3D v = funcoes::Ponto3D_escalar(dr, -1);
    Ponto3D l = funcoes::Ponto3D_Normalizado(funcoes::Ponto3D_subtrai(P_F, Pt));
    Ponto3D r = funcoes::Ponto3D_subtrai(funcoes::Ponto3D_escalar(normal, 2 * funcoes::Ponto3D_produtoEscalar(normal, l)), l);

    Ponto3D I_d = funcoes::Ponto3D_escalar(funcoes::Ponto3D_multiplica(k_d, I_F), funcoes::max(funcoes::Ponto3D_produtoEscalar(normal, l), 0));
    Ponto3D I_e = funcoes::Ponto3D_escalar(funcoes::Ponto3D_multiplica(k_e, I_F), funcoes::max(pow(funcoes::Ponto3D_produtoEscalar(v, r), alpha), 0));
    Ponto3D I_a = funcoes::Ponto3D_multiplica(k_a, I_A);

    Ponto3D I_total = funcoes::Ponto3D_soma(I_d, funcoes::Ponto3D_soma(I_e, I_a));
    return I_total;

}
