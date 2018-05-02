#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarNumerosAleatorios(int, int *);

int main (int argc, char *argv[]){
    FILE *fp;
    char nomeArquivo[33] = "asphalt_01.txt", guardarPonto;
    int *imagem, linha=0, coluna=0, tempVar, numAleatorios[25], random=49, cont = 0;
    gerarNumerosAleatorios(random,numAleatorios);
    imagem = (int *) malloc(sizeof(int));
    for(cont = 0; cont < 25; cont++){
        if(numAleatorios[cont]<10){
            sprintf(nomeArquivo,"./DataSet/asphalt/asphalt_0%d.txt", numAleatorios[cont]);
        }else{
            sprintf(nomeArquivo,"./DataSet/asphalt/asphalt_%d.txt", numAleatorios[cont]);
        }
        printf("%s", nomeArquivo);
        fp = fopen(nomeArquivo,"r");
        do{
            fscanf(fp,"%d%c", &tempVar, &guardarPonto);
            if(guardarPonto == ';'){
                coluna++;
                imagem = (int *) realloc(imagem, coluna*sizeof (int));
                imagem[coluna-1] = tempVar;
            }
        }while(!feof(fp));
        fclose(fp);
        free(imagem);
    }
    
return 0;
}

void gerarNumerosAleatorios(int random, int *numAleatorios){
    int i, j, tempComp;
    srand((unsigned)time(NULL));
    for(i=0 ; i < 25 ; i++){
        tempComp = (rand()%random) + 1;
        for(j=0 ; j < i; j++){
            if(tempComp == numAleatorios[j]){
                i--;
                break;
            }
        }
        numAleatorios[j] = tempComp;
    }        
}