#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "lib/funcoes.h"




int main() {
    //teste caso o opengl não inicialize
    if (!glfwInit()) {
        std::cerr << "Falha ao iniciar o GLFW" << std::endl;
        return -1;
    }

    int nCol = 800, nLin = 800;

    //cria a janela e testa se foi criada com sucesso
    GLFWwindow* window = glfwCreateWindow(nCol, nLin, "Esfera", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, nCol, 0, nLin, -1, 1);

    double wJanela = 4.0, hJanela = 4.0, dJanela = 20   , zEsfera = 20.0;
    double rEsfera = 1.0;
    Ponto3D centroEsfera(0, 0, -zEsfera);
    



    Cor bgColor(100, 100, 100);
    
    Ponto3D k_d = Ponto3D(1.0, 0.0, 0.0);
    Ponto3D k_e = Ponto3D(1.0, 1.0, 1.0);


    Ponto3D I_F = Ponto3D(0.7, 0.7, 0.7);
    Ponto3D P_F = Ponto3D(0.0, 0.5, 0.0);


    double alpha = 50.0;


    double Dx = wJanela / nCol;
    double Dy = hJanela / nLin;
    Ponto3D origem(0, 0, 0);

    while (!glfwWindowShouldClose(window)) {
        glBegin(GL_POINTS);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int l = 0; l < nLin; l++) {
            double y = hJanela / 2.0 - Dy / 2.0 - l * Dy;
            for (int c = 0; c < nCol; c++) {
                double x = -wJanela / 2.0 + Dx / 2.0 + c * Dx;

                Ponto3D direcao(x, y, -dJanela);

                direcao = funcoes::Ponto3D_Normalizado(direcao);



                double t;




                if (funcoes::intersecaoEsfera(origem, direcao, centroEsfera, rEsfera, t)) {
                    Ponto3D PI = funcoes::Ponto3D_escalar(direcao, t);
                    Ponto3D normal = funcoes::Ponto3D_subtrai(PI, centroEsfera);
                    normal = funcoes::Ponto3D_Normalizado(normal);

                    Ponto3D v_inverso = funcoes::Ponto3D_escalar(direcao, -1);

                    Ponto3D vetor_luminoso = funcoes::Ponto3D_subtrai(P_F, PI);
                    vetor_luminoso = funcoes::Ponto3D_Normalizado(vetor_luminoso);

                    Ponto3D r = funcoes::Ponto3D_subtrai(funcoes::Ponto3D_escalar(normal, 2 * funcoes::Ponto3D_produtoEscalar(normal, vetor_luminoso)), vetor_luminoso);




                    Ponto3D I_d = funcoes::Ponto3D_escalar(funcoes::Ponto3D_multiplica(k_d, I_F),funcoes::max(funcoes::Ponto3D_produtoEscalar(normal, vetor_luminoso), 0));

                    Ponto3D I_e = funcoes::Ponto3D_escalar(funcoes::Ponto3D_multiplica(k_e, I_F),funcoes::max(pow(funcoes::Ponto3D_produtoEscalar(v_inverso, r),alpha), 0));

                    Ponto3D I = funcoes::Ponto3D_soma(I_d, I_e);

                    Cor cor = Cor(funcoes::min(255, funcoes::max(0, (I.x * 255))),funcoes::min(255, funcoes::max(0, (I.y * 255))),funcoes::min(255, funcoes::max(0, (I.z * 255))));

                    glColor3ub(cor.r, cor.g, cor.b); // Define a cor do pixel
                    glVertex2i(l, c);

                }
                else {
                    glColor3ub(bgColor.r, bgColor.g, bgColor.b); // Define a cor do pixel
                    glVertex2i(l, c);
                }
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
