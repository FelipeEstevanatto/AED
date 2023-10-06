// ATIVIDADE PRATICA 2 - Concatenação de Strings invertidas
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int x, y, tamA = 0, tamB = 0, tamC, contador = 0;
  char C, *stringX, *stringY, *stringZ;

  scanf("%d %d %c", &x, &y, &C);

  stringX = malloc((x + 1) * sizeof(char));
  stringY = malloc((y + 1) * sizeof(char));

  scanf("%s %s", stringX, stringY);

  while (stringX[tamA] != '\0')
    tamA++;
  while (stringY[tamB] != '\0')
    tamB++;

  // Tamanho das 2 string + espaço pro \0
  tamC = tamA + tamB + 1;

  stringZ = malloc(tamC * sizeof(char));

  // Inversão das palavras
  for (int i = 0; i < tamC - 1; i++) {
    if (tamA > 0) {
      stringZ[i] = stringX[tamA - 1];
      tamA--;
    } else if (tamB > 0) {
      stringZ[i] = stringY[tamB - 1];
      tamB--;
    }
    if (stringZ[i] == C)
      contador++;
  }
  stringZ[tamC] = '\0';

  // Resultados
  puts(stringZ);
  printf("%d\n%d\n", tamC-1, contador);

  // Liberando memória alocada
  free(stringX);
  free(stringY);
  free(stringZ);

  return 0;
}