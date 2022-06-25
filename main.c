#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));   // Initialization, should only be called once.
    char mot[7] = "SALUTA\0";
    printf("Made by Aderox\n");

    char *fileName = "list.txt";
    int nbOfWords = 0;
    int result = getNbOfWords(fileName, &nbOfWords);

    //create an array of string with the size of the number of words
    char **string = malloc(sizeof(char *) * nbOfWords);
    initListOfWords(fileName, string, nbOfWords);

    /*printf("Fichier ouvert. Nombre de mot: %d\nString:\n", nbOfWords);
    for (int i = 0; i < nbOfWords; i++)
    {
        printf("mot %d: %s\n", i, string[i]);
    }*/

    int r = rand() % nbOfWords;
    //printf("Mot 'random' pour r=%d: '%s'", r, string[r]);
    char *gameWord = string[r];
    free(string);
    startGame(gameWord);
}

/* READ FILE !! */
int getNbOfWords(char *fileName, int *nbOfWords)
{
    FILE *file = NULL;
    int cara = 0;
    *nbOfWords = 0;

    file = fopen(fileName, "r+");
    if (file == NULL)
    {
        return 0;
    }
    else
    {

        cara = fgetc(file);
        if (cara != EOF)
        {
            (*nbOfWords) = 1;
        }
        while (cara != EOF)
        {
            if (cara == '\n')
            {
                (*nbOfWords)++;
            }
            cara = fgetc(file);
        }

        fclose(file);
        return 1;
    }
}


int initListOfWords(char *fileName, char **string, int nbOfWords)
{
    printf("file name %s\n", fileName);

    FILE *file = NULL;
    int cara = 0;

    file = fopen(fileName, "r+");
    if (file == NULL)
    {
        return 0;
    }
    else
    {
        //for each words, read each char and create a substring with the apropriate size, then read again the
        //same word and add it in the substring. add the substring to string
        for (int i = 0; i < nbOfWords; i++)
        {
            int posInit = ftell(file);
            int sizeWord = 0;
            int cara = fgetc(file);

            //char mot[255] = ""; //debug

            while (cara != '\n' && cara != EOF)
            {
                //mot[sizeWord] = cara;
                sizeWord++;
                cara = fgetc(file);
            }
            if (sizeWord != 0)
            {
                sizeWord++;
            }

            //printf("Le mot %s a une taille de %d\n", mot, sizeWord);

            fseek(file, posInit, SEEK_SET);
            char *word = NULL;
            word = malloc(sizeof(char) * sizeWord);
            if (word == NULL)
            {
                return -1;
            }

            word[sizeWord - 1] = '\0';
            cara = 0;
            int j = 0;
            //printf("loop %d\n", i);

            while (cara != '\n' && cara != EOF)
            {
                cara = fgetc(file);
                if (cara != '\n' && cara != EOF)
                {
                    word[j] = cara;
                    j++;
                    //printf("%c", cara);
                }
            }

            //printf("Mot numero %d: '%s'\n", i, word);
            string[i] = word;
        }

        fclose(file);
        return 1;
    }
}

/* game */
char myupper(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 32;
    }
    return c;
}

char readChar()
{
    char cara = 0;
    cara = getchar();
    cara = myupper(cara);
    while (getchar() != '\n')
        ;
    return cara;
}

int sameArray(int *array1, int *array2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (array1[i] != array2[i])
        {
            return 0;
        }
    }
    return 1;
}

int getWordSize(char *mot)
{
    int n = 0;
    while (mot[n] != '\0')
    {
        n++;
    }
    return n + 1;
}

void clearArray(int *value, int size)
{
    for (int i = 0; i < size; i++)
    {
        value[i] = 0; //1 for hack
    }
}

void printWord(char *mot, int *found, int sizeofWord, char *toPrint)
{
    for (int i = 0; i < sizeofWord; i++)
    {
        if (found[i])
        {
            toPrint[i] = mot[i];
        }
        else
        {
            toPrint[i] = '*';
        }
    }
    toPrint[sizeofWord - 1] = '\0';
}

/*
return 0: miss
return 1: ok
return 2: already toucehd
*/
int isInWord(char *word, char schar, int sizeofWord, int *found)
{
    int touche = 0;
    int n = 0;
    while (word[n] != '\0')
    {
        if (word[n] == schar)
        {
            if (found[n] == 1)
            {
                return 2;
            }
            found[n] = 1;
            touche = 1;
        }
        n++;
    }
    return touche;
}

void copyArray(int *array1, int *array2, int size)
{
    for (int i = 0; i < size; i++)
    {
        array2[i] = array1[i];
    }
}

void hideLetter(char lettre[27], char cara)
{
    int n = 0;
    while (lettre[n] != '\0')
    {
        if (lettre[n] == cara)
        {
            lettre[n] = '*';
        }
        n++;
    }
}

void coup(char *mot, int *found, int sizeofWord, int *nbCoup, char lettre[27])
{
    char cara = readChar();
    int *oldfound = malloc(sizeof(int) * sizeofWord);
    copyArray(found, oldfound, sizeofWord);
    hideLetter(lettre, cara);
    int touche = isInWord(mot, cara, sizeofWord, found);
    if (touche == 1)
    {
        printf("Bravo vous avez trouve la lettre %c\n", cara);
    }
    else if (touche == 2)
    {
        printf("Vous avez deja trouve la lettre %c\n", cara);
    }
    else
    {
        printf("Dommage c'est rate pour la lettre %c\n", cara);
        (*nbCoup)++;
    }
}

int sommeArray(int *array, int size)
{
    int n = 0;
    for (int i = 0; i < size; i++)
    {
        n += array[i];
    }
    return n;
}

void startGame(char *mot)
{
    printf("Bienvenue dans le pendu !\n");
    //printf("Mot: %s \n", mot);

    int sizeofWord = getWordSize(mot);
    int nbCoup = 0;

    char lettre[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    char *toPrint = malloc(sizeof(char) * sizeofWord);
    int *found = malloc(sizeof(int) * sizeofWord);
    if (toPrint == NULL || found == NULL)
    {
        return;
    }

    clearArray(found, sizeofWord);
    //clearArray(toPrint, sizeofWord);

    while (nbCoup < 11)
    {
        if (sommeArray(found, sizeofWord) == sizeofWord - 1)
        {
            printf("game over: good ending, you met a waifu car girl");
            return;
        }
        else
        {
            printWord(mot, found, sizeofWord, toPrint);
            printf("Voici le mot a deviner: %s. Il vous reste %d vie(s).\n", toPrint, 10 - nbCoup);
            printf("Voici les lettres qu'ils vous restent:\n%s\n", lettre);
            coup(mot, found, sizeofWord, &nbCoup, lettre);
        }
    }
    printf("game over");
}
