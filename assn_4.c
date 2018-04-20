#include<stdio.h>
#include<stdlib.h>
//B tree node structure
typedef struct { /* B-tree node */
  int n; /* Number of keys in node */
  int *key; /* Node's keys */
  long *child; /* Node's child subtree offsets */
} btree_node;
char * indexFileName;
int order;

void add(int k){

}
void find(int k){

}
void print(){

}
void end(){

}

int main(int argc , char *argv[]) {
    indexFileName = argv[1];
    order = atoi(argv[2]);

    char line[200], *token, *key;
    while(strcmp(line,"end\n")!=0){
        fgets(line,200,stdin);
        token = strtok(line," ");
        if(strcmp(token,"add") == 0){
          token = strtok(NULL," ");
          key = atoi(token);
        }//end of add
        else if(strcmp(token,"find")==0){
          token = strtok(NULL," ");
          key = atoi(token);
        }//end of find
        else if(strcmp(token,"print\n")==0){

        }//end of print
        else
            break;
    }//end of while
    return 0;
}
