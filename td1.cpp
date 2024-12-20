#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "lib/funcoes.h"

//Função que pinta um pixel na tela utilizando o opengl
void paintPixel(int nCol, int nLin, std::vector<std::vector<Cor>>& canvas, Cor cor) {
    canvas[nCol][nLin] = cor;
    glColor3ub(cor.r, cor.g, cor.b); // Define a cor do pixel
    glVertex2i(nCol, nLin);

}


int main() {
    //teste caso o opengl não inicialize
    if (!glfwInit()) {
        std::cerr << "Falha ao iniciar o GLFW" << std::endl;
        return -1;
    }

    int nCol = 800, nLin = 800;

    //cria a janela e testa se foi criada com sucesso
    GLFWwindow* window = glfwCreateWindow(800, 800, "Esfera", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, nCol, 0, nLin, -1, 1);

    double wJanela = 4.0, hJanela = 4.0, dJanela = 20, zEsfera = 30.0;
    double rEsfera = 2.0;
    Ponto3D centroEsfera(0, 0, -zEsfera);

    Cor esfColor(255, 0, 0);
    Cor bgColor(100, 100, 100);

    std::vector<std::vector<Cor>> canvas(nLin, std::vector<Cor>(nCol, bgColor));//vetor que armazena a cor de cada pixel

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
                    paintPixel(l, c, canvas, esfColor);

                }
                else {
                    paintPixel(l, c, canvas, bgColor);
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
