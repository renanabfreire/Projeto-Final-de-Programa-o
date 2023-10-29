#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *partidas = fopen("partidas.txt", "r"); 
    FILE *campeonato = fopen("campeonato.txt", "a+"); 
    if(partidas == NULL) {
        perror("Nao foi possivel acessar o arquivo A");
        return 0;
}
    if(campeonato == NULL) {
        perror("Nao foi possivel acessar o arquivo B"); 
        return 0;
}
     char vencedor[30];
     char perdedor[30];
     int numptda;

     while(fscanf(partidas, "%d, %[^,], %[^.]", &numptda, vencedor, perdedor) == 3){
        fprintf(campeonato, "Na partida %d, %s venceu e %s perdeu. %s continua no campeonato.\n", numptda, vencedor, perdedor, vencedor);
     } 

     fclose(partidas);
     fclose(campeonato);
     return 0;
}