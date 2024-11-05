#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include "lib/funcoes.h"
#include <GLFW/glfw3.h>
#include "lib/Ray.h"
#include "lib/Plane.h"
#include "lib/Sphere.h"

const double hJanela = 60.0;
const double wJanela = 60.0;
const double djanela = 30.0;

Ponto3D centroEsfera(0.0, 0.0, -100.0);
double raioEsfera = 40.0;
Ponto3D k_d_esfera(0.7, 0.2, 0.2);
Ponto3D k_e_esfera(0.7, 0.2, 0.2);
Ponto3D k_a_esfera(0.7, 0.2, 0.2);
double alpha_esfera = 10;
Sphere esfera(centroEsfera, raioEsfera, k_d_esfera, k_e_esfera, k_a_esfera, alpha_esfera);

Ponto3D pontoChao(0.0, -raioEsfera, 0.0);
Ponto3D normalChao(0.0, 1.0, 0.0);
Ponto3D k_d_chao(0.2, 0.7, 0.2);
Ponto3D k_e_chao(0.0, 0.0, 0.0);
Ponto3D k_a_chao(0.2, 0.7, 0.2);
double alpha_chao = 1.0;
Plane chao(pontoChao, normalChao, k_d_chao, k_e_chao, k_a_chao, alpha_chao);

Ponto3D pontoFundo(0.0, 0.0, -200.0);
Ponto3D normalFundo(0.0, 0.0, 1.0);
Ponto3D k_d_fundo(0.3, 0.3, 0.7);
Ponto3D k_e_fundo(0.0, 0.0, 0.0);
Ponto3D k_a_fundo(0.3, 0.3, 0.7);
double alpha_fundo = 1.0;
Plane fundo(pontoFundo, normalFundo, k_d_fundo, k_e_fundo, k_a_fundo, alpha_fundo);

Ponto3D posicaoLuz(0.0, 60.0, -30.0);
Ponto3D intensidadeLuz(0.7, 0.7, 0.7);
Ponto3D intensidadeAmbiente(0.3, 0.3, 0.3);

Ponto3D origemRaio(0.0, 0.0, 0.0);

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao iniciar o GLFW" << std::endl;
        return -1;
    }

    int nCol = 500, nLin = 500;

    GLFWwindow* window = glfwCreateWindow(500, 500, "Esfera", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, nCol, 0, nLin, -1, 1);;

    double Dx = wJanela / nCol;
    double Dy = hJanela / nLin;

    while (!glfwWindowShouldClose(window)) {
        glBegin(GL_POINTS);
        glClear(GL_COLOR_BUFFER_BIT);



        for (int l = 0; l < nLin; l++) {
            double y = hJanela / 2.0 - Dy / 2.0 - l * Dy;
            for (int c = 0; c < nCol; c++) {
                double x = -wJanela / 2.0 + Dx / 2.0 + c * Dx;

                Ponto3D dr = Ponto3D(x, y, -djanela);
                Ray raio = Ray(origemRaio, dr);

                double t_esfera  = std::numeric_limits<double>::max();
                double t_plano_chao = std::numeric_limits<double>::max();
                double t_plano_fundo = std::numeric_limits<double>::max();

                bool intersecaoEsfera = esfera.intersecao(raio, t_esfera);
                bool intersecaoChao = chao.intersecao(raio, t_plano_chao);
                bool intersecaoFundo = fundo.intersecao(raio, t_plano_fundo);








                Ponto3D I_total = intensidadeAmbiente;

                if (intersecaoEsfera && (t_esfera < std::fabs(t_plano_chao) &&  t_esfera < std::fabs(t_plano_fundo))) {

                    Ponto3D pt = funcoes::Ponto3D_soma(raio.origem, funcoes::Ponto3D_escalar(raio.direcao, t_esfera));
                    I_total = esfera.iluminacao(pt, raio.direcao, posicaoLuz, intensidadeLuz, intensidadeAmbiente);
                } else if (intersecaoChao && t_plano_chao < t_esfera && t_plano_chao < t_plano_fundo) {

                    Ponto3D pt = funcoes::Ponto3D_soma(raio.origem, funcoes::Ponto3D_escalar(raio.direcao, t_plano_chao));
                    Ponto3D luzdr = funcoes::Ponto3D_subtrai(posicaoLuz, pt);
                    Ray raioSombra(pt, luzdr);
                    if (!esfera.intersecao(raioSombra, t_esfera)) {
                        I_total = chao.iluminacao(pt, raio.direcao, posicaoLuz, intensidadeLuz, intensidadeAmbiente);
                    }
                    else {
                        Ponto3D sombra = Ponto3D(0.0, 0.0, 0.0);
                        I_total = chao.iluminacao(pt, raio.direcao, posicaoLuz, sombra, intensidadeAmbiente);
                    }
                } else if (intersecaoFundo && t_plano_fundo < t_esfera) {

                    Ponto3D pt = funcoes::Ponto3D_soma(raio.origem, funcoes::Ponto3D_escalar(raio.direcao, t_plano_fundo));
                    Ponto3D luzdr = funcoes::Ponto3D_Normalizado(funcoes::Ponto3D_subtrai(posicaoLuz, pt));
                    Ray raioSombra(pt, luzdr);
                    if (!esfera.intersecao(raioSombra, t_esfera)) {
                        I_total = fundo.iluminacao(pt, raio.direcao, posicaoLuz, intensidadeLuz, intensidadeAmbiente);
                    }
                    else {
                        Ponto3D sombra = Ponto3D(0.0, 0.0, 0.0);
                        I_total = fundo.iluminacao(pt, raio.direcao, posicaoLuz, sombra, intensidadeAmbiente);
                    }
                }

                Cor cor = Cor(funcoes::min(255, funcoes::max(0, I_total.x * 255)),
                              funcoes::min(255, funcoes::max(0, I_total.y * 255)),
                              funcoes::min(255, funcoes::max(0, I_total.z * 255)));



                glColor3ub(cor.r, cor.g, cor.b);
                glVertex2i(c, l);

            }
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
