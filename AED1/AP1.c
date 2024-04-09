// ATIVIDADE PRÁTICA 1 - Contagem de letras
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define TAM_MAX 256

int main() {

	char string[TAM_MAX];
	setlocale(LC_ALL, "pt_BR.utf8");
	int contador[256] = {0};

    // Recebe a string e remove o \r e \n do final
	fgets(string, TAM_MAX, stdin);

	for(int i=0; i < strlen(string); i++) {
        unsigned char c = (unsigned char)string[i];

		if (isalpha(c))
			contador[toupper(c)]++;
	}

	for (int i = 0; i < 256; i++) {
		char c = toupper(i);
        if (contador[i] > 0) {
            printf("%c %d\n", c, contador[i]);
        }
    }


	return 0;
}