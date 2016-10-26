#include <stdio.h>
#include <expat.h>
#include "../include/phonebook.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char **argv) {
    srand(time(NULL));
    int cnt;
    phonebook_t *phonebook=malloc(sizeof(phonebook_t));
    phonebook->humans=malloc(sizeof(human_t)*4);
    phonebook->capacity=4;
    phonebook->size=0;
    load_phonebook_xml(argv[1],phonebook);
    print_phonebook(phonebook);
    clear_phonebook(phonebook);
    phonebook=malloc(sizeof(phonebook_t));
    phonebook->humans=malloc(sizeof(human_t)*4);
    phonebook->capacity=4;
    phonebook->size=0;
    gen_phonebook(phonebook,12);
    save_phonebook_xml(argv[2],phonebook);
    clear_phonebook(phonebook);
    return 0;
}
