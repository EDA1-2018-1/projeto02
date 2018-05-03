/*
    Érico Bandeira - 16/0070287
    Luciana Ribeiro Lins de Albuquerque - 15/0016131
    Max Henrique Barbosa - 16/0047013
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define BINMAX 511

void allocMatrix(float **arrayImages);
void calculateTrainingMatrics(int *rows, int *columns, int *grass, int *asphalt, char *fileName, FILE *fp);
void selectAsphaltImages(int *asphalt, int *rows, int *columns, char *fileName, FILE *fp);
void selectGrassImages(int *grass, int *rows, int *columns, char *fileName, FILE *fp);
void countRowsAndColumns(char *fileName, FILE *fp, int *columns, int *rows);
int generatorRandomNumbers();

int main() {

  FILE *fp;
  int **pixels; //matriz
  int random=49, rows, columns, i;
  float **arrayImages; //caracteristicas
  char fileName[33] = "";
  static int asphalt[50], grass[50];

  printf("CHEGOU");
  allocMatrix(arrayImages);
  calculateTrainingMatrics(&rows, &columns, grass, asphalt, fileName, fp);

  return 0;
}

void allocMatrix(float **arrayImages){
  int arraySize, i;
  arraySize = BINMAX + 24;
  arrayImages = (float**)calloc(50,sizeof(float*));
  for(i=0; i<50; i++) {
    *(arrayImages+i) = (float*)calloc(arraySize,sizeof(float));
  }
}

void calculateTrainingMatrics(int *rows, int *columns, int *grass, int *asphalt, char *fileName, FILE *fp){
  int count, value;
  for(count=0;count<50;count++){
    rows=0;
    columns=0;

    if(count%2){
      selectGrassImages(grass, &rows, &columns, fileName, fp);
    } else {
      selectAsphaltImages(asphalt, &rows, &columns, fileName, fp);
    }
  }
}

void selectAsphaltImages(int *asphalt, int *rows, int *columns, char *fileName, FILE *fp) {
  int contAsphalt;
  int randomNumber;
  char value;
  randomNumber = generatorRandomNumbers();
  sprintf(fileName,"./DataSet/asphalt/asphalt_%02d.txt", randomNumber);
  asphalt[randomNumber-1] = 1;

  countRowsAndColumns(fileName, fp, &columns, &rows);
}

void selectGrassImages(int *grass, int *rows, int *columns, char *fileName, FILE *fp){
  int contGrass;
  int randomNumber;
  char value;
  randomNumber = generatorRandomNumbers();
  sprintf(fileName,"./DataSet/grass/grass_%02d.txt", randomNumber);
  grass[randomNumber-1] = 1;

  countRowsAndColumns(fileName, fp, &columns, &rows);
}

void countRowsAndColumns(char *fileName, FILE *fp, int *columns, int *rows){
  char value;

  fp = fopen(fileName,"r");
  while(!feof(fp)){
    fscanf(fp,"%c",&value);
    if(value == ';'){
      *columns++;
    } else if(value == '\n'){
      *rows++;
    }
  }
  *rows -= 1;
  //*columns = *columns/(*(rows+1));
   printf("%d %d\n",*rows,*columns);
   fclose(fp);
}

// void selectTrainingImagens(){
//
// }
//
// void selectTestImages(){
//
// }

int generatorRandomNumbers(){
  srand(time(NULL));
  return (rand() % (50)) + 1;
}

void ilbp(int **pixels, int rows, int columns, float **arrayImages, int value){
  int i,j;
  for(i = 1; i < rows-1; i++) {
    for (j = 1; j < columns-1; j++) {
      quadranteIlbp(pixels,i,j,arrayImages,value);
    }
  }
}

void quadranteIlbp(int **pixels,int row,int colum,float **arrayImages,int value){
  float total=0.0;
  int value=0,min;
  int vetor[9];
  for (int i = row-1; i <= row+1; i++) {
    for (int j = colum-1; j <= colum+1; j++) {
      total += *(*(pixels+i)+j);
      vetor[value] = pixels[i][j];
      value++;
    }
  }
  for (int i = 0; i < 9; i++) {
    if (total/9 >= vetor[i]) {
      vetor[i] = 1;
    } else {
      vetor[i] = 0;
    }
  }
  min = minValue(vetor,256,0);
  if (count%2) {
    arrayImages[(count-1)/2][min]+=1;
  } else {
    arrayImages[50/2+count/2][min]+=1;
  }
}

int minValue(int *vetor,int mini,int cont){
  int n;
  if (count == 9) {
    return mini;
  } else {
    n = binForDec(vetor);
    if (n < mini) {
      mini = n;
    }
    rotVetor(vetor);
    return minValue(vetor,min,count+1);
  }
}

int binForDec(int *bin){
  int decimal=0;
  for (int i = 0; i < 9; i++) {
    decimal += pow(2,(8-i))*bin[i];
  }
  return decimal;
}

void rotVetor(int *vetor){
  int count = vetor[0];
  int count1;
  vetor[0] = vetor[8];
  for (int i = 1; i < 9; i++) {
    count1 = vetor[i];
    vetor[i] = count;
    count = count1;
  }
}

void normVet(float *vetor,int tamVet){

  int maior=0,menor=10000,i;
  for (i = 0; i < tamVet; i++) {
    if (vetor[i] < menor) {
      menor = vetor[i];
    }else if(vetor[i] > maior){
      maior = vetor[i];
    }
  }
  if (maior == menor) {
    return;
  }
  for (i = 0; i < tamVet; i++) {
    vetor[i] = (vetor[i] - menor)/(maior - menor);
  }
}

void fazMedia(float **arrayImages,float *medGrass,float *medAsphalt){

  int i,j;
  float total=0.0;

  for (j = 0; j < BINMAX + 24; j++) {
    for (i = 0; i < 50/2; i++) {
      total+= arrayImages[i][j];
    }
    medGrass[j] = total/(50/2);
    total = 0.0;
    for (i = 50/2; i < 50; i++) {
      total+= arrayImages[i][j];
    }
    medAsphalt[j] = total/(50/2);
    total = 0.0;
  }

}

void medEuclidiana(float **arrayImages,float *medAsphalt,float *medGrass,int *acerto,int *aceitacaoFalsa,int *rejeicaoFalsa){
  float total = 0.0,distGrass,distAsphalt;
  int i,j;
  for (i = 0; i < 50; i++) {
    for (j = 0; j < 536; j++) {
      total+= pow(arrayImages[i][j] - medGrass[j],2);
    }
    distGrass = sqrt(total);
    total = 0.0;
    for (j = 0; j < 536; j++) {
      total+= pow(arrayImages[i][j] - medAsphalt[j],2);
    }
    distAsphalt = sqrt(total);
    total = 0.0;
    if (i < 50/2) {
      if (distGrass < distAsphalt) {
        *acerto += 1;
      } else {
        *rejeicaoFalsa += 1;
      }
    } else{
      if (distGrass > distAsphalt) {
        *acerto += 1;
      } else {
        *aceitacaoFalsa += 1;
      }
    }
  }
}

// void glcm(){
//
// }
