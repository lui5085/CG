#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>


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

int main() {

    double wJanela = 4.0, hJanela = 4.0, dJanela = 20, zEsfera = 10.0;

    double rEsfera = 1.0;
    Ponto3D centroEsfera(0, 0, -zEsfera);

    // Cores
    Cor esfColor(255, 0, 0);
    Cor bgColor(100, 100, 100);


    int nCol = 800, nLin = 800;


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

    std::ofstream img("esfera.ppm");
    img << "P3\n" << nCol << " " << nLin << "\n255\n";
    for (int l = 0; l < nLin; ++l) {
        for (int c = 0; c < nCol; ++c) {
            img << canvas[l][c].r << " " << canvas[l][c].g << " " << canvas[l][c].b << " ";
        }
        img << "\n";
    }
    img.close();

    std::cout << "Imagem gerada: esfera.ppm" << std::endl;

    return 0;
}
