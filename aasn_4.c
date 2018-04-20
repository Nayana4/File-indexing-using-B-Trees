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

add(int k){

}
find(int k){

}
print(){

}
end(){

}

int main(int argc , char *argv[]) {
    indexFileName = argv[1];
    order = atoi(argv[2]);
    return 0;
}
