//
// Created by luis on 11/3/24.
//
#include "Sphere.h"
#include <cmath>
#include "Ray.h"

Sphere::Sphere(Ponto3D center_, double radius_, Ponto3D k_d_, Ponto3D k_e_, Ponto3D k_a_, double alpha_){
    center = center_;
    radius = radius_;
    k_d = k_d_;
    k_e = k_e_;
    k_a = k_a_;
    alpha = alpha_;
}

bool Sphere::intersecao(const Ray& raio, double& t) {


    Ponto3D oc = funcoes::Ponto3D_subtrai(raio.origem, center);
    double a = funcoes::Ponto3D_produtoEscalar(raio.direcao, raio.direcao);
    double b = 2.0 * funcoes::Ponto3D_produtoEscalar(raio.direcao, oc);
    double c = funcoes::Ponto3D_produtoEscalar(oc, oc) - radius * radius;

    double delta = b * b - 4 * a * c;


    if (delta < 0) return false;

    double sqrtDelta = std::sqrt(delta);
    double t1 = (-b - sqrtDelta) / (2.0 * a);
    double t2 = (-b + sqrtDelta) / (2.0 * a);

    t = funcoes::min(t1, t2);

    if (t == t1 && t2 < 0)
    {
        return false;
    }
    return true;





}

Ponto3D Sphere::iluminacao(Ponto3D Pt, Ponto3D dr, Ponto3D P_F, Ponto3D I_F, Ponto3D I_A) const{



    Ponto3D v = funcoes::Ponto3D_escalar(funcoes::Ponto3D_Normalizado(dr), -1);
    Ponto3D l = funcoes::Ponto3D_Normalizado(funcoes::Ponto3D_subtrai(P_F, Pt));
    Ponto3D n = funcoes::Ponto3D_Normalizado(funcoes::Ponto3D_subtrai(Pt, center));
    float dotproduct_nl = funcoes::Ponto3D_produtoEscalar(n, l);
    Ponto3D r = funcoes::Ponto3D_Normalizado(funcoes::Ponto3D_subtrai(funcoes::Ponto3D_escalar(n, 2 * dotproduct_nl), l));
    float dotproduct_vr = funcoes::Ponto3D_produtoEscalar(v, r);
    dotproduct_nl = funcoes::max(dotproduct_nl, 0);
    dotproduct_vr = funcoes::max(dotproduct_vr, 0);


    Ponto3D I_d = funcoes::Ponto3D_escalar(funcoes::Ponto3D_multiplica(k_d, I_F), funcoes::max(dotproduct_nl, 0));
    Ponto3D I_e = funcoes::Ponto3D_escalar(funcoes::Ponto3D_multiplica(k_e, I_F), funcoes::max(pow(dotproduct_vr, alpha), 0));
    Ponto3D I_a = funcoes::Ponto3D_multiplica(k_a, I_A);

    Ponto3D I_total = funcoes::Ponto3D_soma(I_d, funcoes::Ponto3D_soma(I_e, I_a));
    return I_total;


}

