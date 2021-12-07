#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRLEN 130000
#define WORDSIZE 30

void insert(char biglist[][WORDSIZE], char* buffer, int idx);
int interp(char k[WORDSIZE], char arr[][WORDSIZE], int l, int r);
int readfile(char* file, char* buffer, char biglist[ARRLEN][WORDSIZE]);

int main(int argc, char* argv[])
{
   if (argc < 2) {
      printf("Incorrect usage. Example: ./spellchecker <filename.txt>\n");
      return 1;
   }
   
   char biglist[ARRLEN][WORDSIZE];
   char* buffer = calloc(WORDSIZE, sizeof(char));   
   int len = readfile(argv[1], buffer, biglist);
 
   char word[WORDSIZE];
   printf("Enter a word: ");
   scanf("%s", word);
   
   if (interp(word, biglist, 0, len-1)==-1){
      printf("Word not in dictionary.\n");
   }
   else{
      printf("Word is in the dictionary.\n");
   }
   
   free(buffer);
   
   return 0;
}

int readfile(char* file, char* buffer, char biglist[ARRLEN][WORDSIZE])
{
   FILE* fp = fopen(file, "r");   
   if(!fp){
      fprintf(stderr, "Cannot read from file\n");
      exit(EXIT_FAILURE);
   }
   
   int i = 0;
   while(fscanf(fp, "%s", buffer) != EOF){      
      insert(biglist, buffer, i);
      i++;
   }
      
   fclose(fp);
   return i;
}

void insert(char biglist[][WORDSIZE], char* buffer, int idx)
{
   bool added = false;
   for (int i=0; i<idx; i++){
      if (strcmp(buffer, biglist[i]) < 0){
         for (int j=idx; j>i; j--){
            strcpy(biglist[j], biglist[j-1]);
         }
         strcpy(biglist[i], buffer);
         added = true;
         return;
      }
   }
   if (!added) {
      strcpy(biglist[idx], buffer);   
   }         
} 

int interp(char k[WORDSIZE], char arr[][WORDSIZE], int l, int r)
{
   int m;
   double md;
   
   while(l <= r){
      md = ((double)(k[0]-arr[l][0])/(double)(arr[r][0]-arr[l][0])*(double)(r-l)) + (double)(l);
      m = 0.5 + md;
      if((m > r) || (m < l)){
         return -1;
      }
      if(strcmp(k, arr[m])==0){
         return m;
      }
      else{
         if(strcmp(k, arr[m]) > 0){
            l = m + 1;
         }
         else{
            r = m - 1;
         }
      }
   }
   
   return -1;
}
