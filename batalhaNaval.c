#include <stdio.h>

#define N 10   // tamanho do tabuleiro
#define M 5    // tamanho fixo das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabuleiro[i][j] == 0) printf(" ~ ");  // água
            else if (tabuleiro[i][j] == 3) printf(" N "); // navio
            else if (tabuleiro[i][j] == 5) printf(" * "); // habilidade
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar a matriz de habilidade em forma de cone
void criarCone(int habilidade[M][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            habilidade[i][j] = 0; // inicia com 0
        }
    }
    // Cone com vértice no topo e expandindo para baixo
    for (int i = 0; i < M; i++) {
        for (int j = M/2 - i; j <= M/2 + i; j++) {
            if (j >= 0 && j < M) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de cruz
void criarCruz(int habilidade[M][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            habilidade[i][j] = 0;
        }
    }
    for (int i = 0; i < M; i++) {
        habilidade[i][M/2] = 1;  // coluna do meio
        habilidade[M/2][i] = 1;  // linha do meio
    }
}

// Função para criar a matriz de habilidade em forma de octaedro (losango)
void criarOctaedro(int habilidade[M][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            habilidade[i][j] = 0;
        }
    }
    int centro = M/2;
    for (int i = 0; i < M; i++) {
        int alcance = centro - abs(i - centro);
        for (int j = centro - alcance; j <= centro + alcance; j++) {
            habilidade[i][j] = 1;
        }
    }
}

// Função para aplicar a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[N][N], int habilidade[M][M], int origemX, int origemY) {
    int centro = M/2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemX + (i - centro);
                int y = origemY + (j - centro);

                // valida se está dentro dos limites do tabuleiro
                if (x >= 0 && x < N && y >= 0 && y < N) {
                    if (tabuleiro[x][y] == 0) { // só marca se for água
                        tabuleiro[x][y] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[N][N];
    int cone[M][M], cruz[M][M], octaedro[M][M];

    inicializarTabuleiro(tabuleiro);

    // adicionando alguns navios manualmente
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[8][8] = 3;

    // criar habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // aplicar no tabuleiro em diferentes posições
    aplicarHabilidade(tabuleiro, cone, 1, 5);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);

    // mostrar o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}