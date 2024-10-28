//
// Created by luis on 10/27/24.
//

#ifndef FUNCOES_H
#define FUNCOES_H
#include <vector>


class Cor {
public:
    int r, g, b;
    Cor(int r_=0, int g_=0, int b_=0);
};

class Ponto3D {
public:
    double x, y, z;
    Ponto3D(double x_=0, double y_=0, double z_=0);
};


class funcoes {
public:

    static Ponto3D Ponto3D_escalar(Ponto3D p, double escalar);
    static Ponto3D Ponto3D_soma(Ponto3D p1, Ponto3D p2);
    static Ponto3D Ponto3D_subtrai(Ponto3D p1, Ponto3D p2);
    static double Ponto3D_produtoEscalar(Ponto3D p1, Ponto3D p2);
    static Ponto3D Ponto3D_normaliza(Ponto3D p);
    static Ponto3D Ponto3D_multiplica(Ponto3D p1, Ponto3D p2);
    static Ponto3D Ponto3D_reflete(Ponto3D p, Ponto3D normal);
    static Ponto3D Ponto3D_refrata(Ponto3D p, Ponto3D normal, double n1, double n2);
    static Ponto3D Ponto3D_rotaciona(Ponto3D p, Ponto3D normal, double angulo);
    static bool intersecaoEsfera(const Ponto3D& origem, const Ponto3D& direcao, const Ponto3D& centroEsfera, double rEsfera);
    static double max (double a, double b);
    static double min(double a, double b);
    static Ponto3D Ponto3D_Normalizado(Ponto3D v);



};



#endif //FUNCOES_H
