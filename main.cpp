#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

struct Cor {
    int r, g, b;
    Cor(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
};

struct Ponto3D {
    double x, y, z;
    Ponto3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

bool intersecaoEsfera(const Ponto3D& origem, const Ponto3D& direcao, const Ponto3D& centroEsfera, double rEsfera, double& t) {
    Ponto3D oc = {origem.x - centroEsfera.x, origem.y - centroEsfera.y, origem.z - centroEsfera.z};
    double a = direcao.x * direcao.x + direcao.y * direcao.y + direcao.z * direcao.z;
    double b = 2.0 * (oc.x * direcao.x + oc.y * direcao.y + oc.z * direcao.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - rEsfera * rEsfera;

    double delta = b * b - 4 * a * c;

    if (delta < 0) return false;

    t = (-b - std::sqrt(delta)) / (2.0 * a);
    return true;
}

void desenhaEsfera(int nCol, int nLin, const std::vector<std::vector<Cor>>& canvas) {
    glBegin(GL_POINTS);
    for (int l = 0; l < nLin; ++l) {
        for (int c = 0; c < nCol; ++c) {
            const Cor& cor = canvas[l][c];
            glColor3ub(cor.r, cor.g, cor.b); // Define a cor do pixel
            glVertex2i(c, l); // Desenha o pixel na posição (c, l)
        }
    }
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao iniciar o GLFW" << std::endl;
        return -1;
    }

    int nCol = 800, nLin = 800;
    GLFWwindow* window = glfwCreateWindow(nCol, nLin, "Esfera", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, nCol, 0, nLin, -1, 1); // Define a projeção ortográfica

    double wJanela = 4.0, hJanela = 4.0, dJanela = 20, zEsfera = 10.0;
    double rEsfera = 1.0;
    Ponto3D centroEsfera(0, 0, -zEsfera);

    // Cores
    Cor esfColor(255, 0, 0);
    Cor bgColor(100, 100, 100);

    std::vector<std::vector<Cor>> canvas(nLin, std::vector<Cor>(nCol, bgColor));

    double Dx = wJanela / nCol;
    double Dy = hJanela / nLin;

    for (int l = 0; l < nLin; l++) {
        for (int c = 0; c < nCol; c++) {
            double x = -wJanela / 2.0 + Dx / 2.0 + c * Dx;
            double y = hJanela / 2.0 - Dy / 2.0 - l * Dy;

            Ponto3D origem(0, 0, 0);
            Ponto3D direcao(x, y, -dJanela);

            double magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y + direcao.z * direcao.z);
            direcao.x /= magnitude;
            direcao.y /= magnitude;
            direcao.z /= magnitude;

            double t;
            if (intersecaoEsfera(origem, direcao, centroEsfera, rEsfera, t)) {
                canvas[l][c] = esfColor;
            }
        }
    }

    // Loop de renderização
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        desenhaEsfera(nCol, nLin, canvas);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
