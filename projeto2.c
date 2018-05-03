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
  int randomNumber, value;
  randomNumber = generatorRandomNumbers();
  sprintf(fileName,"./DataSet/asphalt/asphalt_%02d.txt", randomNumber);
  asphalt[randomNumber-1] = 1;

  //countRowsAndColumns(fileName, fp, &columns, &rows);
}

void selectGrassImages(int *grass, int *rows, int *columns, char *fileName, FILE *fp){
  int contGrass;
  int randomNumber, value;
  randomNumber = generatorRandomNumbers();
  sprintf(fileName,"./DataSet/grass/grass_0%d.txt", randomNumber);
  grass[randomNumber-1] = 1;

  //countRowsAndColumns(fileName, fp, &columns, &rows);
}

void countRowsAndColumns(char *fileName, FILE *fp, int *columns, int *rows){
  int value;
  fp = fopen(fileName,"r");

  while(!feof(fp)){
    fscanf(fp, "%d",&value);
    if(value == ';'){
      *columns++;
    }
    else if(value == '\n'){
      *rows++;
    }
  }
  *rows--;
  *columns = *columns/(*rows)+1;
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

// void ilbp(){
//
// }

// void glcm(){
//
// }
