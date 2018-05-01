#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[]) {
  int func;

  scanf("%d\n", func);

  if (func = 1){
    media_de_matriz();
  }

  else if (func = 2) {
    vetorBinario();
  }

  else if (func = 3) {
    Binario_para_decimal();
  }

return 0;
}
//=================================================================================
int media_de_matriz () {//Pega uma matriz 3x3 e transforma numa matriz 3x3 binária
  int pixel, soma, media, novaMatriz;

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      scanf("%d\n", &pixel[i][j]);
      soma += pixel[i][j];
    }
  }

  media = soma / 9;

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if(pixel[i][j] > media){
        novaMatriz[i][j] = 1;
      }
      else{
        novaMatriz[i][j] = 0;
      }
    }
  }

return novaMatriz;
}
/*===========================================================================*/
int vetorBinario (){ //Converte a Matriz em Vetor
  int vetBin[8], indice = 0;

  while (j < 3) {
    i = 0;
    vetBin[indice] = novaMatriz[i][j];
    indice = indice + 1;
    j++;
  }

  i = 1;
  while (i < 3) {
    j = 2;
    vetBin[indice] = novaMatriz[i][j];
    indice = indice + 1;
    i++;
  }

  j = 1;
  while (j >= 0) {
    i = 2;
    vetBin[indice] = novaMatriz[i][j];
    indice = indice + 1;
    j--;
  }

  j = 0;
  while (j < 2) {
    i = 1;
    vetBin[indice] = novaMatriz[i][j];
    indice = indice + 1;
    j++;
  }

return vetBin[8];
}
//============================================================================

void Binario_para_decimal(){//Transforma binario para decimal
  int dec=0,num,d=1;
  do
  {
    dec = dec+(num%10)*d;
    d = d*2;
    num = num/10;
  }
  while(num!=0);
}
