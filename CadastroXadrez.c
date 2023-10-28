#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LIMITE_JOGADORES 8

struct player {
    char nome[20];
    int idade;
};

void salvarJogadores(struct player* cadastros, int numCadastros) {
    FILE* arquivo = fopen("jogadores.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de jogadores");
        exit(1);
    }

    for (int i = 0; i < numCadastros; i++) {
        fprintf(arquivo, "%s %d\n", cadastros[i].nome, cadastros[i].idade);
    }

    fclose(arquivo);
}

void carregarJogadores(struct player* cadastros, int* numCadastros) {
    FILE* arquivo = fopen("jogadores.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    *numCadastros = 0;
    while (fscanf(arquivo, "%s %d", cadastros[*numCadastros].nome, &cadastros[*numCadastros].idade) == 2) {
        (*numCadastros)++;
    }

    fclose(arquivo);
}

void listarNomesEIdades(struct player* cadastros, int numCadastros) {
    printf("Lista de jogadores cadastrados:\n");
    for (int i = 0; i < numCadastros; i++) {
        printf("Nome: %s, Idade: %d\n", cadastros[i].nome, cadastros[i].idade);
    }
}

int main() {
    srand(time(NULL));

    char opcao;
    struct player novoCadastro;
    struct player cadastro[8];
    int numCadastros = 0;

    carregarJogadores(cadastro, &numCadastros);

    while (1) {
        printf("\n____Seja Bem vindo ao Xadrez virtual! O que deseja fazer?____\n\n");
        puts("1. Cadastrar novo player\n2. Jogar\n3. Listar jogadores cadastrados\n");
        scanf(" %c", &opcao);

        if (opcao == '1') {
            if (numCadastros >= LIMITE_JOGADORES) {
                printf("Limite de %d jogadores atingido. Nao e possivel criar mais cadastros.\n", LIMITE_JOGADORES);
                sleep(5);
            } else {
                printf("Vamos iniciar seu cadastro, qual o seu nickname?\n");
                scanf(" %[^\n]", novoCadastro.nome);

                printf("Digite sua idade:\n");
                scanf(" %d", &novoCadastro.idade);

                printf("Cadastrado com sucesso\n");

                cadastro[numCadastros] = novoCadastro;
                numCadastros++;

                salvarJogadores(cadastro, numCadastros);
                sleep(5);
            }
        } else if (opcao == '2') {
            printf("Procurando partida...\n");
            puts("Para voltar ao inicio, pressione 4");

            char opcaoJogar;
            scanf(" %c", &opcaoJogar);

            if (opcaoJogar == '4') {
                printf("Voltando ao menu principal, aguarde...\n");
            }
        } else if (opcao == '3') {
            listarNomesEIdades(cadastro, numCadastros);
            printf("\nPara voltar ao inicio, pressione 4: ");

            char opcaoLista;
            scanf(" %c", &opcaoLista);

            if (opcaoLista == '4') {
                printf("Voltando, aguarde...\n");
            }
        }
    }
    return 0;
}
