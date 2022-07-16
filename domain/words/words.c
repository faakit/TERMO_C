#include "words.h"

char * getRandomWord(){
  FILE *wordsFile = fopen(WORDS_FILE, "r");
  if (wordsFile == NULL) {
    exit(1);
  }

  char * word = malloc(6 * sizeof *word);
  srand(time(NULL) / 86400);
  do {
    int wordIndex = rand() % NUMBER_OF_WORDS + 1;    // Numero aleatório até a última palavra

    fseek(wordsFile, (wordIndex-1) * 6 * sizeof(char), SEEK_SET);
    fscanf(wordsFile, "%s", word);
  } while(alreadySorted(word));

  putSorted(word);
  fclose(wordsFile);
  toUppercase(word);
  return word;
}

int alreadySorted(char * word){
  FILE *sortedWordsFile = fopen(SORTED_WORDS_FILE, "a+"); // Cria o arquivo caso não exista.
  if (sortedWordsFile == NULL) {
    exit(1);
  }
  char * scannedWord = malloc(6 * sizeof *scannedWord);
  do {
    fscanf(sortedWordsFile, "%s", scannedWord);
    if(strcmp(scannedWord, word) == 0){
      free(scannedWord);
      fclose(sortedWordsFile);
      return 1;
    }
  } while (!feof(sortedWordsFile));
  free(scannedWord);
  fclose(sortedWordsFile);
  return 0;
}

void putSorted(char * word){
  FILE *sortedWordsFile = fopen(SORTED_WORDS_FILE, "a");
  if (sortedWordsFile == NULL) {
    exit(1);
  }
  fprintf(sortedWordsFile, "%s\n", word);
  fclose(sortedWordsFile);
}

void toUppercase(char * word){
  int j = 0;
  while (word[j]) {
    word[j] = toupper(word[j]);
    j++;
  }
}

void toLowercase(char * word){
  int j = 0;
  while (word[j]) {
    word[j] = tolower(word[j]);
    j++;
  }
}