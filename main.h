/*
PENDU
*/

/*ACTUAL GAME*/
char myupper(char c);
char readChar();
int getWordSize(char *c);
int sameArray(int *array1, int *array2, int size);
void copyArray(int *array1, int *array2, int size);
void startGame(char *mot);
void clearArray(int *value, int size);
void printWord(char *mot, int *found, int sizeofWord, char *toPrint);
int isInWord(char *word, char schar, int sizeofWord, int *found);
int sommeArray(int *array, int size);
void hideLetter(char lettre[27], char cara);
void coup(char *mot, int *found, int sizeofWord, int *nbCoup, char lettre[27]);

/*READ FILE*/
int getNbOfWords(char *fileName, int *nbOfWords);
int initListOfWords(char *fileName, char **string, int nbOfWords);