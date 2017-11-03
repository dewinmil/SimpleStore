#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct node{
  char productName[20];
  float stock;
  char unit[20];
  float price;
  char pricePerUnit[20];
  struct node* parent;
  struct node* childLeft;
  struct node* childRight;
} node;

void *nptr = NULL;
//node root;


void displayMenu(){
  char mainMenu[450];
  strcpy(mainMenu, "Welcome to the Miles DeWind grocery store\n");
  strcat(mainMenu, "Please let me know what you want to do according to the menu below\n");
  strcat(mainMenu, "==================================================================\n");
  strcat(mainMenu, "1: Add product to store             2: Purchase product from store\n");
  strcat(mainMenu, "3: Check price of a product         4: Show products in store\n");
  strcat(mainMenu, "5: Remove a product from store      6: Find product\n");
  strcat(mainMenu, "7: Inventory\n");
  strcat(mainMenu, "You can type a selection number, or exit to leave the store\n\n");
  fprintf(stderr, "%s", mainMenu);
}


void cleanNode(node *n){
  int i;
  for(i = 0; i < 20; i++){
    
  n->productName[i] = '\0';
  n->unit[i] = '\0';
  n->pricePerUnit[i] = '\0';;
  }
  n->stock = 0;
  n->price = 0;
  n->childLeft = nptr;
  n->childRight = nptr;
  n->parent = nptr;
}

int findFileSize(char* string){
  int filesize;
  FILE *fp;
  fp = fopen(string, "r");

  if(fp == NULL){
    return -1;
  }
  fseek(fp, 0, SEEK_END);

  filesize = ftell(fp);

  fclose(fp);

  return filesize;

}


void displayNode(node *n){
  fprintf(stderr, "name: %s\nstock: %.2f\nunit: %s\nprice: %.2f\npricePerUnit: %s\n\n\n", n->productName, n->stock, n->unit, n->price, n->pricePerUnit);
}


void addToTree(node *root, node *parent, node *n){

  //global variable root is empty / not created so set == to node n
  if(strlen(root->productName) == 0){

    strcpy(root->productName, n->productName);
    root->stock = n->stock;
    strcpy(root->unit, n->unit);
    root->price = n->price;
    strcpy(root->pricePerUnit, n->pricePerUnit);
  }
  else{ 
    //have a root / compare n to see if belongs to left of potential parent
    if(strcmp(n->productName, parent->productName) < 0){
      if(!parent->childLeft){
        n->parent = parent;
        parent->childLeft = n;
      }else{
        //node did have left child / run again with left child as potential parent
        addToTree(root, parent->childLeft, n);
      }
    }
    else if(strcmp(n->productName, parent->productName) > 0){
      if(!parent->childRight){
        n->parent = parent;
        parent->childRight = n;
      }else{
        addToTree(root, parent->childRight, n);
      }
    }
  }
}


void loadData(node *root){
  int fd;
  char str[8];
  strcpy(str, "data.txt");
  int size = findFileSize(str);
  fd = open("data.txt", O_RDONLY | S_IRUSR);
  char buffer[size]; 
  pread(fd, buffer, size, 0);
  //receive parse buffer by line and space
  char *token;
  token = strtok(buffer," \n");
  int index = -1;
  node *n = malloc(sizeof(node));
  while(token != NULL){
    index = (index+1) % 5;
    if(index == 0){
      n = malloc(sizeof(node));
    }
    switch (index){
      case 0:
        strcpy(n->productName, token);
        break;
      case 1:
        n->stock = (float)atoi(token);
        break;
      case 2:
        strcpy(n->unit, token);
        break;
      case 3:
        n->price = (float)atoi(token);
        break;
      case 4:
        strcpy(n->pricePerUnit, token);
        addToTree(root, root, n);
        break;
    }
    token = strtok(NULL," \n");
  }  
}


void saveData(node root){
  
}


void removeFromTree(node *parent, node *n){
  
  //removing root / clear all pointers & values
  if(parent->parent == nptr){
    cleanNode(parent);
    free(parent);
  }
  else{ 
    //have a root / compare n to see if belongs to left of potential parent
    if(strcmp(n->productName, parent->productName) < 0){
      if(parent->childLeft){
        removeFromTree(parent->childLeft, n);
      }
    }
    else if(strcmp(n->productName, parent->productName) > 0){
      if(parent->childRight){
        removeFromTree(parent->childRight, n);
      }
    }
    else{//must be equal
      if(n->childLeft){
        n->childLeft->parent = n->parent;
        if(parent->childRight){
          n->childRight->parent = n->childLeft;
          n->childLeft->childRight = n->childRight;
        }
      }else if(n->childRight){
        n->childRight->parent = parent->parent;
      }
    }
  }
}


int findLevelOrder(node* *array[100], node *root, node *parent, int row, int column, int remaining, int prevDepth){
 

  displayNode(parent);
  if(parent->childLeft){
    array[column][row] = parent->childLeft;
    row++;
  }
  if(parent->childRight){
    array[column][row] = parent->childRight;
    row++;
  }
  remaining--;
  if(remaining > 0){
    findLevelOrder(array, root, array[column-1][prevDepth-remaining], row, column, remaining, prevDepth);
  }
  else{
    if(row == 0){
      return 1;
    }
    else{
      column++;
      prevDepth = row;
      remaining = row;
      row = 0;
      findLevelOrder(array, root, array[column-1][prevDepth-remaining], row, column, remaining, prevDepth);
    }
  }

//float makePurchase(node *root, node *n, int num){

//}
  
}

















