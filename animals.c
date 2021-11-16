//COP3502 Fall 2021
//Recitation Program #1
//Kattis: Alphabet Animals
//Veronica Martucci
//09-01-2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function creates a 2D array containing the list of animals
//and return the 2d array
char **createAnimalList(int n){

  char **list = calloc(n, sizeof(char*));

  for(int i = 0; i < n; i++){

    char temp[21];
    scanf("%s", temp);

    int length = (strlen(temp)+1);

    list[i] = calloc(length, sizeof(char));
    strcpy(list[i], temp);
  }

  return list;
}

//This function creates a frequency array to keep track of how many
//words start with each letter, then returns the array
int *createStartingLetterFrequencyArray(char **list, int n){

  int *freqArray = calloc(26, sizeof(int));

  //initialize all values in array to 0
  for(int i = 0; i < 26; i++){
    freqArray[i] = 0;
  }

  //read the first letter of every animal(string) and add 1 to that box
  for(int i = 0; i < n; i++){
    freqArray[list[i][0] - 'a']++;
  }

  return freqArray;
}

//This function checks startingLfreqArray to see if the lastletter is in it. If not it prints a ?.
//If it is, then it prints the word and checks if there is a following word. if there isn't then
//it print an !
void checkFirstLetter(char **list, int n, char lastLetter, int *freqArray){

  //If there is a word starting with the lastletter
  if(freqArray[lastLetter - 'a'] > 0){

    for(int i = 0; i < n; i++){

      char firstLetter = list[i][0];

      //if the first letter matched the last letter of the previous animal
      if(firstLetter == lastLetter){

        int length = strlen(list[i]);
        char endLetter = list[i][length - 1];

        //substract 1 for words that start and end with the same letter
        freqArray[firstLetter - 'a']--;
        //If there isn't a following word print the animal with an !
        if(freqArray[endLetter - 'a'] <= 0) {
          printf("%s!\n", list[i]);
          return;
        }
        //reset frequency array
        freqArray[firstLetter - 'a']++;
      }
    }

    for(int i = 0; i < n; i++){

      char firstLetter = list[i][0];

      //if the first letter matched the last letter of the previous animal
      if(firstLetter == lastLetter){

        int length = strlen(list[i]);
        char endLetter = list[i][length - 1];

        //Print the animal
        printf("%s\n", list[i]);
        return;
      }
    }
  }
  else {
    printf("?\n");
    return;
  }
}

//This function frees the memory used for the 2d array (list)
void freeMemory(char **list, int n, int *freqArray){

  for(int i = 0; i < n; i++){
    free(list[i]);
  }
  free(list);
  free(freqArray);
}


int main(){

  char animal[21];
  int n;

  scanf("%s", animal);
  scanf("%d", &n);

  char lastLetter = animal[strlen(animal) - 1];

  char **list = createAnimalList(n);

  int *freqArray = createStartingLetterFrequencyArray(list, n);

  checkFirstLetter(list, n, lastLetter, freqArray);

  freeMemory(list, n, freqArray);

  return 0;
}
