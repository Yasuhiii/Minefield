#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define MINES 5

// Função para inicializar o tabuleiro
void inicializarTabuleiro(char tabuleiro[SIZE][SIZE], char simbolo) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tabuleiro[i][j] = simbolo;
        }
    }
}

// Função para colocar minas aleatórias
void colocarMinas(char minas[SIZE][SIZE]) {
    int count = 0;
    while (count < MINES) {
        int linha = rand() % SIZE;
        int coluna = rand() % SIZE;
        if (minas[linha][coluna] != '*') {
            minas[linha][coluna] = '*';
            count++;
        }
    }
}

// Função para contar minas vizinhas
int contarMinasProximas(char minas[SIZE][SIZE], int linha, int coluna) {
    int count = 0;
    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                if (minas[i][j] == '*') {
                    count++;
                }
            }
        }
    }
    return count;
}

// Função para mostrar o tabuleiro visível
void mostrarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    printf("\n   ");
    for (int j = 0; j < SIZE; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char minas[SIZE][SIZE];
    char visivel[SIZE][SIZE];
    int linha, coluna;
    int jogadasRestantes = SIZE * SIZE - MINES;
    int fimDeJogo = 0;

    srand(time(NULL));

    inicializarTabuleiro(minas, '-');
    inicializarTabuleiro(visivel, '#');
    colocarMinas(minas);

    printf("=== CAMPO MINADO 5x5 ===\n");
    printf("Tenta limpar todas as casas sem pisar numa mina!\n");

    while (!fimDeJogo) {
        mostrarTabuleiro(visivel);

        printf("\nEscolhe uma posicao (linha e coluna): ");
        scanf("%d %d", &linha, &coluna);

        if (linha < 0 || linha >= SIZE || coluna < 0 || coluna >= SIZE) {
            printf("Posicao invalida! Tenta novamente.\n");
            continue;
        }

        if (visivel[linha][coluna] != '#') {
            printf("Ja escolheste essa posicao!\n");
            continue;
        }

        if (minas[linha][coluna] == '*') {
            printf("\n BOOM! Pisaste numa mina! \n");
            fimDeJogo = 1;
        } else {
            int minasProximas = contarMinasProximas(minas, linha, coluna);
            visivel[linha][coluna] = '0' + minasProximas;
            jogadasRestantes--;

            if (jogadasRestantes == 0) {
                printf("\n Parabens! Limpaste todas as casas seguras! \n");
                fimDeJogo = 1;
            }
        }
    }

    // Mostrar o tabuleiro completo no final
    printf("\nTabuleiro completo:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", minas[i][j]);
        }
        printf("\n");
    }

    return 0;
}

