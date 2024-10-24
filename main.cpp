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

// Função auxiliar para calcular a interseção de um raio com a esfera
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

    // Parâmetros da esfera
    double rEsfera = 1.0;
    Ponto3D centroEsfera(0, 0, -zEsfera); // Posicionando a esfera mais para trás

    // Cores
    Cor esfColor(255, 0, 0);     // Vermelho para a esfera
    Cor bgColor(100, 100, 100);  // Cinza para o background

    // Definindo a resolução da tela (mosquito/canvas)
    int nCol = 800, nLin = 800;

    // Criando a matriz de cores
    std::vector<std::vector<Cor>> canvas(nLin, std::vector<Cor>(nCol, bgColor));

    // Dimensões dos retângulos da tela de mosquito
    double Dx = wJanela / nCol;
    double Dy = hJanela / nLin;

    // Laço para percorrer cada linha e coluna da janela
    for (int l = 0; l < nLin; l++) {
        for (int c = 0; c < nCol; c++) {
            // Coordenadas do centro do retângulo na tela de mosquito
            double x = -wJanela / 2.0 + Dx / 2.0 + c * Dx;
            double y = hJanela / 2.0 - Dy / 2.0 - l * Dy;

            // Raio que parte do olho do pintor (0, 0, 0) e passa pelo ponto (x, y, -dJanela)
            Ponto3D origem(0, 0, 0);
            Ponto3D direcao(x, y, -dJanela);

            // Normalizar a direção do raio
            double magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y + direcao.z * direcao.z);
            direcao.x /= magnitude;
            direcao.y /= magnitude;
            direcao.z /= magnitude;

            // Testar interseção do raio com a esfera
            double t;
            if (intersecaoEsfera(origem, direcao, centroEsfera, rEsfera, t)) {
                // Se houver interseção, pintar com a cor da esfera
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
