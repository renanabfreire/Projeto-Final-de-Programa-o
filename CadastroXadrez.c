#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "registro.h"

#define LIMITE_JOGADORES 8

struct player {
    char nome[20];
    int idade;
};

char nomes[8][30];
  char idades;
  int numjogadores;
  int i = 0;
  int k = 0;

 typedef struct
  {
    char jogador_a[30];
    char jogador_b[30]
  } Partida;

  


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

void criararray(){
    FILE *arq;
    int positions = 0;
    char *temp = 0;
    char *result;
    char line[30];

    arq = fopen("jogadores.txt", "r");

    if (arq == NULL)
    {
      printf("Falha ao abrir o arquivo");
    }
    else
    {
      while (!feof(arq))
      {
        result = fgets(line, 30, arq);
        if (result)
        {
          temp = strtok(line, " ");
          strcpy(nomes[positions], temp);
        }
        positions++;
      }
    }
    numjogadores = positions;
    fclose(arq);
  }

  int numerodepartidas()
  {
    int iteracoes = 0;

    for (int i = 0; i < numjogadores - 1; i++)
    {
      for (int j = 0; j < numjogadores - 1; j++)
      {
        if (i != j && j >= i)
        {
          iteracoes++;
        }
      }
    }
    return iteracoes;
  }

int main() {
    int numpartidas;
    int l = 0;
    char ganhadores[8][30];
    char perdedores[8][30];
    int resultado;
    int jogosregistrados=0;
    int partatual = 0;

    srand(time(NULL));

    char opcao;
    struct player novoCadastro;
    struct player cadastro[8];
    int numCadastros = 0;

    carregarJogadores(cadastro, &numCadastros);

    while (1) {
        printf("\n____Seja Bem vindo ao Xadrez virtual! O que deseja fazer?____\n\n");
        puts("1. Cadastrar novo player\n2. Jogar\n3. Listar jogadores cadastrados\n 4.Gerar tabelas\n");
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

            criararray();

            numpartidas = numerodepartidas();
            Partida partidas[numpartidas];
            int iteracoes = 0;

            for (int i = 0; i < numjogadores - 1; i++)
            {
              for (int j = 0; j < numjogadores - 1; j++)
              {
                if (i != j && j >= i)
                {
                  strcpy(partidas[iteracoes].jogador_a, nomes[i]);
                  strcpy(partidas[iteracoes].jogador_b, nomes[j]);
                  iteracoes++;
                }
              }
            }

            FILE* arquivodapartida;

            arquivodapartida = fopen("partidas.txt", "r+");
            if(arquivodapartida == NULL)
            {
              arquivodapartida = fopen("partidas.txt", "w+");
              if(arquivodapartida == NULL)
              {
                perror("Erro ao abrir arquivo de partidas");
                exit(1);
              }
            }

            criararray();

            numpartidas = numerodepartidas();
            Partida part[numpartidas];
            int iterac = 0;

            for (int i = 0; i < numjogadores - 1; i++)
            {
              for (int j = 0; j < numjogadores - 1; j++)
              {
                if (i != j && j >= i)
                {
                  strcpy(part[iterac].jogador_a, nomes[i]);
                  strcpy(part[iterac].jogador_b, nomes[j]);
                  iteracoes++;
                }
              }
            }

            partatual += jogosregistrados;

            fseek(arquivodapartida, 0, SEEK_END);

            printf("\nTornei número: ");

            for (int i = 0; i < numpartidas; i++)
            {
              fprintf(arquivodapartida, "\nRodada %d", i + 1);
              fprintf(arquivodapartida, "\npartidas: %s x %s \n", partidas[i].jogador_a, partidas[i].jogador_b);
              printf("\nRodada %d", i + 1);
              printf("\npartidas: %s x %s \n", partidas[i].jogador_a, partidas[i].jogador_b);

              fprintf(arquivodapartida, registroDeJogadas());
              printf("-----------------------------------");
            }
            jogosregistrados +=1;

            puts("Para voltar ao inicio, pressione 4");

            char opcaoJogar;
            scanf(" %c", &opcaoJogar);

            fclose(arquivodapartida);

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
        }else if(opcao == '4'){
 
  
    criararray();

    numpartidas = numerodepartidas();
    Partida partidas[numpartidas];
    int iteracoes = 0;

    for (int i = 0; i < numjogadores - 1; i++)
    {
      for (int j = 0; j < numjogadores - 1; j++)
      {
        if (i != j && j >= i)
        {
          strcpy(partidas[iteracoes].jogador_a, nomes[i]);
          strcpy(partidas[iteracoes].jogador_b, nomes[j]);
          iteracoes++;
        }
      }
    }
     for (int i = 0; i < (numpartidas / 2); i++)
    {
      printf("\nRodada %d", i + 1);
      printf("\npartidas: %s x %s \n", partidas[i].jogador_a, partidas[i].jogador_b);
      printf("partidas: %s x %s \n", partidas[numpartidas - (1 + i)].jogador_a, partidas[numpartidas - (1 + i)].jogador_b);
      printf("-----------------------------------");
    }
  }

        }
        return 0;
    }
    

