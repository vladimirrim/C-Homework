#include <stdlib.h>
#include "../include/position.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void count(void *k,void *m) {
int l=*((int *)k);
l++;
*((int*)k)=l;
}
void print(void *k,void *m){
    char *s;
    s=(char*)malloc(sizeof(char)*32);
    position_node *p = (position_node*) malloc(sizeof(position_node));
    p=(position_node*)m;
    strcpy(s,(char *)k);
    printf(s,p->x,p->y);
    free(s);
    free(p);
}
void apply(intrusive_list *lst, void (*op)(void *k,void *m), void *k){
    intrusive_node *head = &lst->head;
    intrusive_node *node = head->next;
    while(node!=head){
        position_node *pnode = get_position(node);
        op(k,pnode);
        node=node->next;
    }
}
int main(int argc, char **argv) {
    FILE *f;
    intrusive_list* l = malloc(sizeof(intrusive_list));
    init_list(l);
    int x, y;
    char *px=malloc(sizeof(char)*10);
    char *py=malloc(sizeof(char)*10);
    int k=0;
    int i = 1;
    if ( !strcmp(argv[1],"loadtext") ) {
        f = fopen(argv[2], "r");
        while (1) {
           if(fscanf(f, "%d%d", &x, &y)!=2)
            break;
            add_position(l, x, y);
        }
        fclose(f);
        if (!strcmp(argv[3],"print")){
            apply(l,print,argv[4]);
        }
        if(!strcmp(argv[3],"count")){
            apply(l,count,&k);
            printf("%d",k);
        }
        if(!strcmp(argv[3],"savetext")){
            f=fopen(argv[4],"a");
            intrusive_node *head = &l->head;
            intrusive_node *node = head->next;
            while(node!=head){
                position_node *pnode = get_position(node);
                fprintf(f,"%d %d\n",pnode->x,pnode->y);
                node=node->next;
            }
            fclose(f);
        }      
        if(!strcmp(argv[3],"savebin")){
            f=fopen(argv[4],"ab");
            intrusive_node *head = &l->head;
            intrusive_node *node = head->next;
            while(node!=head){
                position_node *pnode = get_position(node);
                fwrite(&(pnode->x),1,3,f);
                fwrite(&(pnode->y),1,3,f);
                node=node->next;
            }
            fclose(f);
        }
    } else {
        f = fopen(argv[2], "rb");
        while (!feof(f)) {
            fread(px, 1, 3, f);
            if(fread(py, 1, 3, f)!=3)
            break;
            x=0;y=0;
            for(int i=3;i>-1;i--){
                *((char *)&x + i)=*(px+i);
                *((char *)&y + i)=*(py+i);
            }
            add_position(l,x,y);
        }
    fclose(f);
        if (!strcmp(argv[3],"print")){
            apply(l,print,argv[4]);
        }
        if(!strcmp(argv[3],"count")){
            apply(l,count,&k);
            printf("%d",k);
        }
        if(!strcmp(argv[3],"savetext")){
            f=fopen(argv[4],"a");
            intrusive_node *head = &l->head;
            intrusive_node *node = head->next;
            while(node!=head){
                position_node *pnode = get_position(node);
                fprintf(f,"%d %d\n",pnode->x,pnode->y);
                node=node->next;
            }
            fclose(f);
        }
        if(!strcmp(argv[3],"savebin")){
            f=fopen(argv[4],"ab");
            intrusive_node *head = &l->head;
            intrusive_node *node = head->next;
            while(node!=head){
                position_node *pnode = get_position(node);
                fwrite((char*)&pnode->x,1,3,f);
                fwrite((char*)&pnode->y,1,3,f);
                node=node->next;
            }
            fclose(f);
        }
    }
remove_all(l);
free(px);
free(py);
    return 0;
}
