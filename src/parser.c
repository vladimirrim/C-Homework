#include <stdlib.h>
#include "../include/phonebook.h"
#include <string.h>
#include <stdio.h>
#include <expat.h>
#define BUFFER_SIZE 1

typedef struct my_data{
   phonebook_t *book;
   int cnt;
   int overflow;
}my_data;


void start_element(void *data, const char *element, const char **attribute) {
    int i = 0;
    for (i = 0; attribute[i]; i += 2) {
        if(!strcmp(attribute[i],"name")){
            ((my_data*)data)->cnt = 0;
            char *tmp=malloc(sizeof(char)*800);
            strcpy(tmp,attribute[i+1]);
            strcpy((((my_data*)data)->book->humans+((my_data*)data)->book->size)->name,strtok(tmp," "));
            strcpy((((my_data*)data)->book->humans+((my_data*)data)->book->size)->middle_name,strtok(NULL," "));
            strcpy((((my_data*)data)->book->humans+((my_data*)data)->book->size)->family_name,strtok(NULL," "));
            (((my_data*)data)->book->humans+((my_data*)data)->book->size)->phones_num=0;
            ((my_data*)data)->book->size++;
            if(((my_data*)data)->book->size==((my_data*)data)->book->capacity-1){
                resize_book(((my_data*)data)->book);
            }
            free(tmp);
        }
    }
}

void end_element(void *data, const char *element) {
   if(!strcmp(element,"phone")){
       int i=((my_data*)data)->cnt;
       int j=((my_data*)data)->book->size-1;
       ((my_data*)data)->cnt++;
       ((my_data*)data)->overflow=0;
       (((my_data*)data)->book->humans+j)->phones_num++;
}

}

void handle_data(void *data, const char *content, int length) {
    char *tmp = malloc(length+10);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    int i=((my_data*)data)->cnt;
    int j=((my_data*)data)->book->size-1;
    if(tmp[0]>='0'&&tmp[0]<='9'){
      if(((my_data*)data)->overflow==0){
        strcpy(((((my_data*)data)->book->humans + j)->phones[i]),tmp);
       }else{
        strcat(((((my_data*)data)->book->humans + j)->phones[i]),tmp);
       }
        ((my_data*)data)->overflow=1;
    }
    free(tmp);
}

int parse_xml(char *buff, unsigned buff_size,const char *filename,phonebook_t *book) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    my_data *data=malloc(sizeof(my_data));
    data->book=malloc(sizeof(phonebook_t));
    *(data->book)=*book;
    data->cnt=0;    
    data->overflow=0;
    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, data);
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
    *book=*(data->book);
    free(data->book);   
    free(data);
    return 0;
}
