//
// Created by luis on 10/27/24.
//

#include "funcoes.h"
#include <cmath>


Cor::Cor(int r_, int g_, int b_)
{
    r = r_;
    g = g_;
    b = b_;
}

Ponto3D::Ponto3D(double x_, double y_, double z_)
{
    x = x_;
    y = y_;
    z = z_;
}

Ponto3D funcoes::Ponto3D_escalar(Ponto3D p, double escalar)
{
    return {p.x * escalar, p.y * escalar, p.z * escalar};
}

Ponto3D funcoes::Ponto3D_soma(Ponto3D p1, Ponto3D p2)
{
    return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}


Ponto3D funcoes::Ponto3D_subtrai(Ponto3D p1, Ponto3D p2)
{
    return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

double funcoes::Ponto3D_produtoEscalar(Ponto3D p1, Ponto3D p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}


Ponto3D funcoes::Ponto3D_normaliza(Ponto3D p)
{
    double norma = std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    return {p.x / norma, p.y / norma, p.z / norma};
}


Ponto3D funcoes::Ponto3D_multiplica(Ponto3D p1, Ponto3D p2)
{
    return {p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x};
}

Ponto3D funcoes::Ponto3D_reflete(Ponto3D p, Ponto3D normal)
{
    return Ponto3D_subtrai(p, Ponto3D_escalar(normal, 2 * Ponto3D_produtoEscalar(p, normal)));
}

Ponto3D funcoes::Ponto3D_refrata(Ponto3D p, Ponto3D normal, double n1, double n2)
{
    double n = n1 / n2;
    double cosI = -Ponto3D_produtoEscalar(p, normal);
    double cosT2 = 1 - n * n * (1 - cosI * cosI);
    if (cosT2 < 0) return {0, 0, 0};
    return Ponto3D_subtrai(Ponto3D_escalar(p, n), Ponto3D_escalar(normal, n * cosI + std::sqrt(cosT2)));
}

Ponto3D funcoes::Ponto3D_rotaciona(Ponto3D p, Ponto3D normal, double angulo)
{
    double c = std::cos(angulo);
    double s = std::sin(angulo);
    double t = 1 - c;
    double x = p.x * (t * normal.x * normal.x + c) + p.y * (t * normal.x * normal.y - s * normal.z) + p.z * (t * normal.x * normal.z + s * normal.y);
    double y = p.x * (t * normal.x * normal.y + s * normal.z) + p.y * (t * normal.y * normal.y + c) + p.z * (t * normal.y * normal.z - s * normal.x);
    double z = p.x * (t * normal.x * normal.z - s * normal.y) + p.y * (t * normal.y * normal.z + s * normal.x) + p.z * (t * normal.z * normal.z + c);
    return {x, y, z};
}

bool funcoes::intersecaoEsfera(const Ponto3D& origem, const Ponto3D& direcao, const Ponto3D& centroEsfera, double rEsfera, double& t) {
    Ponto3D oc = Ponto3D_subtrai(origem, centroEsfera);
    double a = Ponto3D_produtoEscalar(direcao, direcao);
    double b = 2.0 * Ponto3D_produtoEscalar(oc, direcao);
    double c = Ponto3D_produtoEscalar(oc, oc) - rEsfera * rEsfera;

    double delta = b * b - 4 * a * c;

    if (delta < 0) return false;

    t = (-b - std::sqrt(delta)) / (2.0 * a);
    return true;
}







