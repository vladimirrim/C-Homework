#include <stdlib.h>
#include "../include/phonebook.h"
#include "../include/names.h"
#include <stdio.h>
#include <expat.h>
#include <string.h>
#define BUFFER_SIZE 10000
int cmp_humans(const void *a,const void *b){
    return strcmp(((human_t *)a)->family_name,((human_t *)b)->family_name);
}


void resize_book(phonebook_t *book){
    book->capacity*=2;
    human_t *tmp=realloc(book->humans,book->capacity*sizeof(human_t));
    book->humans=tmp;
}


void push_back_human(phonebook_t *book, human_t *human){
    if(book->size==book->capacity-1){
        resize_book(book);
    }
    *(book->humans+book->size) = *human;
    book->size++;
    free(human);
}


human_t get_human(phonebook_t *book,char *family_name){
    int i=0; 
    while(!strcmp((book->humans+i)->family_name,family_name)){
    i++;
}
  return *(book->humans+i);
}


int load_phonebook_xml(const char *filename,phonebook_t *book){
    char buffer[BUFFER_SIZE];
    int result=0;
    result=parse_xml(buffer, BUFFER_SIZE,filename, book);
    qsort(book->humans,book->size,sizeof(human_t),cmp_humans);
    return result;
}


int save_phonebook_xml(const char *filename, phonebook_t *book){
     FILE *f;
     f = fopen(filename,"w");
     if (f == NULL) {
        printf("Failed to open file\n");
        return 1;
     }
     fprintf(f,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
     fprintf ( f,"<phonebook>\n");
     for(int i=0;i<book->size;i++){
       fprintf ( f,"<human name=\"%s %s %s\">\n",(book->humans+i)->name,(book->humans+i)->middle_name,(book->humans+i)->family_name);
       int j=0;
       while(j<(book->humans+i)->phones_num){
         fprintf(f,"<phone>%s</phone>\n",(book->humans+i)->phones[j]);
         j++;
       } 
       fprintf ( f,"</human>\n");
     }
     fprintf ( f,"</phonebook>");
     fclose(f);
     return 0;
}


void print_phonebook(phonebook_t *book){
    printf("%d\n",book->size);
    for(int i=0;i<book->size;i++){
    printf("name: %s\nmiddle name: %s\nfamily name: %s\n",(book->humans+i)->name,(book->humans+i)->middle_name,(book->humans+i)->family_name);
    int j=0;
    while(j<(book->humans+i)->phones_num){
      printf("phone: %s\n",(book->humans+i)->phones[j]);
      j++;
     }
    printf("\n\n");
    }
}


void gen_phonebook(phonebook_t *book, size_t size){
     for(int i=0;i<size;i++){
     human_t *human=malloc(sizeof(human_t));
     int tmp=rand()%100;
     strcpy(human->name,kNames[tmp]);
     tmp=rand()%100;
     strcpy(human->family_name,kFamilyNames[tmp]);
     tmp=rand()%49;
     strcpy(human->middle_name,kMiddleNames[tmp]);
     int k=rand()%10;
     human->phones_num=k;
     for(int j=0;j<=k;j++){
        char *tmp=malloc(sizeof(char)*21);
        int rnd= 1000000 + rand()%1000000000;
        sprintf(tmp, "%d", rnd);
        strcpy(human->phones[j],tmp);
        free(tmp);
     }
       push_back_human(book,human);
     }
}


void clear_phonebook(phonebook_t *book){
    free(book->humans);
    free(book);
}

