#include <stdio.h>
#include <expat.h>
#include <string.h>
#include <stdlib.h>
#include "names.h"
#include <time.h>

#define BUFFER_SIZE 100000

typedef struct human_s{
    char name[256];
    char middle_name[256];
    char family_name[256];
    char phones[10][21];
}human_t;
typedef struct phonebook_s {
    human_t *humans;
    size_t size;
    size_t capacity;
}phonebook_t;

phonebook_t *phonebook;
int cnt;

int cmp_humans(const void *a,const void *b){
    return strcmp(((human_t *)a)->family_name,((human_t *)b)->family_name);
}

void resize(phonebook_t *book){
    book->capacity*=2;
    human_t *tmp=realloc(book->humans,book->capacity*sizeof(human_t));
    book->humans=tmp;
}

void start_element(void *data, const char *element, const char **attribute) {
    int i = 0;
    for (i = 0; attribute[i]; i += 2) {
        if(!strcmp(attribute[i],"name")){
            cnt = 0;
            printf("%d\n",phonebook->size);
            char *tmp=(char *)malloc(sizeof(char)*256);
            strcpy(tmp,attribute[i+1]);
            strcpy((phonebook->humans + phonebook->size)->name,strtok(tmp," "));
            strcpy((phonebook->humans + phonebook->size)->middle_name,strtok(NULL," "));
            strcpy((phonebook->humans + phonebook->size)->family_name,strtok(NULL," "));
            free(tmp);
            phonebook->size++;
            if(phonebook->size==phonebook->capacity-1){
                resize(phonebook);
            }
        }
    }
}

void end_element(void *data, const char *element) {
}

void handle_data(void *data, const char *content, int length) {
    char *tmp = (char*)malloc(length);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    if(tmp[0]>='0'&&tmp[0]<='9'&&phonebook->size-1>=0){
        strcpy(((phonebook->humans + phonebook->size-1)->phones[cnt]),tmp);
        cnt++;
    }
    free(tmp);
}

int parse_xml(char *buff, size_t buff_size,const char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    return 0;
}


void push_back_human(phonebook_t *book, human_t *human){
    if(book->size==book->capacity-1){
        resize(book);
    }
    *(book->humans+book->size) = *human;
    book->size++;
    free(human);
}


human_t *get_human(){
     human_t *human=malloc(sizeof(human_t));
     strcpy(human->name,kNames[rand()%100]);
     strcpy(human->family_name,kFamilyNames[rand()%100]);
     strcpy(human->middle_name,kMiddleNames[rand()%49]);
     int i=rand()%10;
     for(int j=0;j<=i;j++){
        char *tmp=malloc(sizeof(char)*21);
        int rnd= 1000000 + rand()%1000000000;
        sprintf(tmp, "%d", rnd);
        strcpy(human->phones[j],tmp);
        free(tmp);
     }
    return human;
}


int load_phonebook_xml(const char *filename){
    char buffer[BUFFER_SIZE];
    int result=0;
    result=parse_xml(buffer, BUFFER_SIZE,filename);
    qsort(phonebook->humans,phonebook->size,sizeof(human_t),cmp_humans);
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
       while((book->humans+i)->phones[j][0]>='0'&&(book->humans+i)->phones[j][0]<='9'){
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
    for(int i=0;i<phonebook->size;i++){
    printf("name: %s\nmiddle name: %s\nfamily name: %s\n",(book->humans+i)->name,(book->humans+i)->middle_name,(book->humans+i)->family_name);
    int j=0;
    while((book->humans+i)->phones[j][0]>='0'&&(book->humans+i)->phones[j][0]<='9'){
      printf("phone: %s\n",(book->humans+i)->phones[j]);
      j++;
     }
    printf("\n\n");
    }
}


void gen_phonebook(phonebook_t *book, size_t size){
     for(int i=0;i<size;i++){
       push_back_human(book,get_human());
     }
}


void clear_phonebook(phonebook_t *book){
    free(book->humans);
    free(book);
}

int main(int argc,char **argv) {
    srand(time(NULL));
    phonebook=malloc(sizeof(phonebook_t));
    phonebook->humans=malloc(sizeof(human_t)*4);
    phonebook->capacity=4;
    phonebook->size=0;
    load_phonebook_xml(argv[1]);
    print_phonebook(phonebook);
    phonebook->size=0;
    gen_phonebook(phonebook,12);
    save_phonebook_xml(argv[2],phonebook);
    clear_phonebook(phonebook);
    return 0;
}
