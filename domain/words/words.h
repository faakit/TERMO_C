#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define WORDS_FILE "palavras.txt"
#define SORTED_WORDS_FILE "sorted.txt"
#define NUMBER_OF_WORDS 18289

//Retorna uma palavra aleatória do dicionário.
char * getRandomWord();

//Verifica se a palavra já foi sorteada anteriormente.
int alreadySorted(char * word);

//TRANSFORMA UMA STRING PARA CAIXA ALTA.
void toUppercase(char * word);

//transforma uma string para caixa baixa.
void toLowercase(char * word);

//Coloca a palavra sorteada no arquivo de já sorteados.
void putSorted(char * word);

#endif