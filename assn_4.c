#include<stdio.h>
#include<stdlib.h>
//B tree node structure
typedef struct { /* B-tree node */
  int n; /* Number of keys in node */
  int *key; /* Node's keys */
  long *child; /* Node's child subtree offsets */
} btree_node;
long rootOffset;
int order;
//linked list for queue implementation
typedef struct node{ /* Queue node */
  long data;
  struct Qnode* next;
}Qnode;
Qnode* front = NULL;
Qnode* rear = NULL;

FILE *indexFile;
char * indexFileName;
int i = 0;


void enQueue(long offset) {
  Qnode* node = (Qnode*)malloc(sizeof(Qnode*));
  node->data = offset;
  node->next = NULL;
  if(front == rear){
    front = rear = node;
    return;
  }
  rear->next = node;
  rear = node;
}

long deQueue(){
  long offset;
  offset = front->data;
  if(front == rear)
     front = rear = NULL;
  else
     front = front->next;
  return offset;
}

void add(int k){
    indexFile = fopen(indexFileName,"r+b");
    btree_node node;
    node.n = 0;
    node.key = (int *) calloc( order - 1, sizeof( int ) );
    node.child = (long *) calloc( order, sizeof( long ) );
    fread(&rootOffset,sizeof(long),1,fp);
    if(rootOffset == -1){
      rootOffset = sizeof(long);
      fwrite(&rootOffset,sizeof(long),1,index_file);
    }//end of if
    else{

    }//end of else
}

void find(int k, long offset){
    btree_node node;
    node.n = 0;
    node.key = (int *) calloc( order - 1, sizeof( int ) );
    node.child = (long *) calloc( order, sizeof( long ) );
    fseek(indexFile, offset, SEEK_SET);
    fread(&node.n,sizeof(int),1,indexFile);
    fread(node.key,sizeof(int),(order-1),indexFile);
    fread(node.child,sizeof(long),order,indexFile);
    if(node.child[0] == 0){
        for(i = 0; i < node.n; i++){
            if(k == node.key[i]){
              printf("Entry with key=%d exists\n",k);
              return;
            }
        }
        printf("Entry with key=%d does not exist\n",k);
        return;
    }
    else{
        for(i = 0; i < node.n; i++){
            if(k == node.key[i]){
              printf("Entry with key=%d exists\n",k);
              return;
            }
            else if(k < node.key[i]){
              break;
            }
        }
    }
    if(node.child[i] != 0){
        return find(k, node.child[i]);
    }
    else{
        printf("Entry with key=%d does not exist\n",k);
    }
}

void print(){
    int level = 1;
    int qSize = 1;
    btree_node node;
    node.n = 0;
    node.key = (int *) calloc( order - 1, sizeof( int ) );
    node.child = (long *) calloc( order, sizeof( long ) );
    while(front <= rear){
       printf("%2d: ", level);
       long nodeOffset = deQueue();
       fseek(indexFile, nodeOffset, SEEK_SET);
       //read the node from the file
       fread(&node.n,sizeof(int),1,indexFile);
	     fread(node.key,sizeof(int),(order-1),indexFile);
       fread(node.child,sizeof(long),order,indexFile);
       //print the keys in the node
       for( i = 0; i < node.n - 1; i++ ) {
         printf( "%d,", node.key[i] );
       }
       printf( "%d", node.key[ node.n - 1 ] );
       if(node.child[0] != 0){
          level++;
          for(i = 0; i <= node.n; i++){
              enQueue(node.child[i]);
          }
       }
       printf("\n");
    }//end of while loop
}

int main(int argc , char *argv[]) {
    indexFileName = argv[1];
    order = atoi(argv[2]);
    indexFile = fopen(indexFileName,"r+b");
    /* If file doesn't exist, set root offset to unknown and create * file,
     otherwise read the root offset at the front of the file */
    if ( indexFile == NULL ) {
      rootOffset = -1;
      indexFile = fopen( indexFileName, "w+b" );
      fwrite( &rootOffset, sizeof( long ), 1, indexFile );
    }
    else{
      fread( &rootOffset, sizeof( long ), 1, indexFile );
    }
    //read input
    char line[200], *token, *key;
    gets(line);
    while(strcmp(line,"end")!=0){
        if(strncmp(line,"add",3) == 0){
            token = strtok(line," ");
            key = strtok(NULL," ");
            add(atoi(key));
        }
        else if(strncmp(line,"find",3) == 0){
            token = strtok(line," ");
            key = strtok(NULL," ");
            indexFile = fopen(indexFileName,"r+b");
            fseek(indexFile,0L,SEEK_SET);
            fread( &rootOffset, sizeof( long ), 1, indexFile );
            if(rootOffset != -1){
                find(atoi(key), rootOffset);
            }
            else
                printf("Entry with key=%d does not exist\n",key);
        }
        else if(strncmp(line,"print",3) == 0){
            indexFile = fopen(indexFileName,"r+b");
            fseek(indexFile,0L,SEEK_SET);
            fread( &rootOffset, sizeof( long ), 1, indexFile );
            if(rootOffset != -1){
              enQueue(rootOffset);
              print();
            }
        }
        else
          break;
    }//end of while
    return 0;
}
