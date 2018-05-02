#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarNumerosTreinamento(int, int *);
void gerarNumerosTeste(int *, int*);

int main (int argc, char *argv[]){

    FILE *fp;
    char nomeArquivo[33] = "asphalt_01.txt", guardarPonto;
    int *imagem, linha=0, coluna=0, tempVar, numTreinamento[25];
    int random=49, contAsphalt = 0, numTeste[25];

    gerarNumerosTreinamento( random, numTreinamento);
    gerarNumerosTeste(numTeste, numTreinamento);

    imagem = (int *) malloc(sizeof(int));
    for(contAsphalt = 0; contAsphalt < 25; contAsphalt++){
        if(numTreinamento[contAsphalt] < 10){
            sprintf(nomeArquivo,"./DataSet/asphalt/asphalt_0%d.txt", numTreinamento[contAsphalt]);
        }else{
            sprintf(nomeArquivo,"./DataSet/asphalt/asphalt_%d.txt", numTreinamento[contAsphalt]);
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

void gerarNumerosTreinamento(int random, int *numTreinamento){
    int i, j, tempComp;
    srand((unsigned)time(NULL));
    for(i=0 ; i < 25 ; i++){
        tempComp = (rand()%random) + 1;
        for(j=0 ; j < i; j++){
            if(tempComp == numTreinamento[j]){
                i--;
                break;
            }
        }
        numTreinamento[j] = tempComp;
    }        
}

void gerarNumerosTeste(int *numTeste, int *numTreinamento){
    int i, j, a=0;
    for(i=0 ; i < 50 ; i++){
        for(j=0 ; j < 25; j++){
            if(i == numTreinamento[j]){
                break;
            }   
        }  
        if(j == 25){
            numTeste[a] = i;
            a++;
        }
    }        
}
