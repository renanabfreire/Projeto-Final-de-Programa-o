#ifndef REGISTRO_DE_JOGADAS_H
#define REGISTRO_DE_JOGADAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* registroDeJogadas() {
    char jogada[10];
    char c=' ';
    char *jogadas = NULL;
    int i = 1;
    int rodada = 1;
    int tam = 0;

    printf("===REGISTRO DE JOGADAS===\n");

    do {
        if (i % 2 != 0) {
            printf("Jogada %d das brancas: ", rodada);
        }
        else {
            printf("Jogada %d das pretas: ", rodada);
            rodada++;
        }

        scanf("%9s", jogada);

        if (jogadas == NULL) {
            jogadas = strdup(jogada);
            tam = 9;
        } else {
            tam += 9;
            jogadas = (char *)realloc(jogadas, tam + 1);
            strcat(jogadas, " ");
            strcat(jogadas, jogada);
        }

        i++;

    } while (strchr(jogada, '#') == NULL);

    return jogadas;
}

#endif