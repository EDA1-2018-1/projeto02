#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarNumerosTreinamento(int, int *);
void gerarNumerosTeste(int *, int*);

int main (int argc, char *argv[]){

    FILE *fp;
    char nomeArquivo[33] = "asphalt_01.txt", guardarPonto;
    int *imagem, linha=0, coluna=0, tempVar, numTreinamento[25];
    int random=49, contAsphalt = 0, contGrass = 0, numTeste[25], guardarColuna;

    gerarNumerosTreinamento( random, numTreinamento);
    gerarNumerosTeste(numTeste, numTreinamento);

    imagem = (int**) malloc(sizeof(int*));
    for(contAsphalt = 0; contAsphalt < 25; contAsphalt++){
        sprintf(nomeArquivo,"./DataSet/asphalt/asphalt_%02d.txt", numTreinamento[contAsphalt]);
        printf("%s\n", nomeArquivo);
        fp = fopen(nomeArquivo,"r");
        do{
            fscanf(fp,"%d%c", &tempVar, &guardarPonto);
            if(guardarPonto == ';'){
                coluna++;
                imagem = (int *) realloc(imagem, coluna*sizeof (int));
                imagem[coluna-1] = tempVar;
            }else{
                coluna = 0;
                linha++;
            }
        }while(!feof(fp));
        printf("%d\n", imagem[0]);
        linha = 0;
        
        // fclose(fp);
        // free(imagem);    - comentar com o Lucas depois

        // 1; 2; 3; 4; 5; 6; 7; 8; 9; 10

    }

    gerarNumerosTreinamento( random, numTreinamento);
    gerarNumerosTeste(numTeste, numTreinamento);

    for(contGrass = 0; contGrass < 25; contGrass++){
        if(numTreinamento[contGrass] < 10){
            sprintf(nomeArquivo,"./DataSet/grass/grass_0%d.txt", numTreinamento[contGrass]);
        }else{
            sprintf(nomeArquivo,"./DataSet/grass/grass_%d.txt", numTreinamento[contGrass]);
        }
        printf("%s\n", nomeArquivo);
        fp = fopen(nomeArquivo,"r");
        do{
            fscanf(fp,"%d%c", &tempVar, &guardarPonto);
            if(guardarPonto == ';'){
                coluna++;
                imagem = (int *) realloc(imagem, coluna*sizeof (int));
                imagem[coluna-1] = tempVar;
            }
        }while(!feof(fp));
        // fclose(fp);
        // free(imagem);    - comentar com o Lucas depois
    }


return 0;
}

/////////////////////////////////////////////////////////////////////////////

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
