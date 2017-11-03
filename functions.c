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
  char mainMenu[550];
  strcpy(mainMenu, "Welcome to Miles grocery store\n");
  strcat(mainMenu, "Please let me know what you want to do according to the menu below\n");
  strcat(mainMenu, "==================================================================\n");
  strcat(mainMenu, "1: Add product to store             2: Purchase product from store\n");
  strcat(mainMenu, "3: Check price of a product         4: Show products in store\n");
  strcat(mainMenu, "5: Remove a product from store      6: Find product\n");
  strcat(mainMenu, "7: Inventory                        8: Done for day\n");
  strcat(mainMenu, "Please type a selection number, or type exit to leave the store\n\n");
  strcat(mainMenu, "You can also type menu to redisplay this menu when line says input\n");
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
        n->stock = atof(token);
        //n->stock = (float)atoi(token);
        break;
      case 2:
        strcpy(n->unit, token);
        break;
      case 3:
        n->price = atof(token);
        //n->price = (float)atoi(token);
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


float removeFromTree(node *root, node *parent, node *n){
   
  //product on left branch of node
  if(strcmp(n->productName, parent->productName) < 0){
    if(parent->childLeft){
      removeFromTree(root, parent->childLeft, n);
    }
    else{
      return -1; //couldn't find product
    }
  }
  //product on right branch of node
  else if(strcmp(n->productName, parent->productName) > 0){
    if(parent->childRight){
      removeFromTree(root, parent->childRight, n);
    }
    else{
      return -1; //couldn't find product
    }
  }
  else{//must be on correct product
    if(parent->parent == nptr){//must be root
      if(parent->childLeft){
        displayNode(parent->childLeft);
        strcpy(parent->productName, parent->childLeft->productName);
        parent->stock = parent->childLeft->stock;
        strcpy(parent->unit, parent->childLeft->unit);
        parent->price = parent->childLeft->price;
        strcpy(parent->pricePerUnit, parent->childLeft->pricePerUnit);

        node * tmp = parent->childLeft;
        parent->childLeft = parent->childLeft->childLeft;
        if(tmp->childRight){
          addToTree(parent, parent, tmp->childRight);
        }
        cleanNode(tmp);
        free(tmp);
      }else if(parent->childRight){
        strcpy(parent->productName, parent->childRight->productName);
        parent->stock = parent->childRight->stock;
        strcpy(parent->unit, parent->childRight->unit);
        parent->price = parent->childRight->price;
        strcpy(parent->pricePerUnit, parent->childRight->pricePerUnit);
        
        node * tmp = parent->childRight;
        parent->childLeft = parent->childRight->childLeft;
        parent->childRight = parent->childRight->childRight; 
        cleanNode(tmp);
        free(tmp);
      }else{
        cleanNode(parent);
      }
      return 1;
    }
    else{
      if(parent->parent->childLeft == parent){
        parent->parent->childLeft = nptr;
      }
      if(parent->parent->childRight == parent){
        parent->parent->childRight = nptr;

      }
      if(parent->childLeft){
        parent->childLeft->parent = nptr;
        addToTree(root, root, parent->childLeft);
      }
      if(parent->childRight){
        parent->childRight->parent = nptr;
        addToTree(root, root, parent->childRight);
      }
      cleanNode(parent);
      free(parent);
      return 1;
    }
  }

}


void findLevelOrder(node* *array[100], node *root, node *parent, int row, int column, int remaining, int prevDepth){
 
  //free & malloc array
  if(row == 0 && column == 0){
    int i;
    for(i = 0; i < 100; i++){
      free(array[i]);
    }
   
    for(i = 0; i < 100; i++){
      if(i == 0){
        array[i] = malloc(1 * sizeof(node*));
      }
      array[i] = malloc(2 * i * sizeof(node*));
    }

  } 

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
      //done - do nothing
    }
    else{
      column++;
      prevDepth = row;
      remaining = row;
      row = 0;
      findLevelOrder(array, root, array[column-1][prevDepth-remaining], row, column, remaining, prevDepth);
    }
  }
}

float makePurchase(node *root, node *parent, node *n, float num){

  //root is empty / not created so can't make purchase
  if(strlen(root->productName) == 0){
    return -1;
  }
  else{ 
    //product on left branch of node
    if(strcmp(n->productName, parent->productName) < 0){
      if(parent->childLeft){
        makePurchase(root, parent->childLeft, n, num);
      }
      else{
        return -1; //couldn't find product

      }
    }
    //product on right branch of node
    else if(strcmp(n->productName, parent->productName) > 0){
      if(parent->childRight){
        makePurchase(root, parent->childRight, n, num);
      }
      else{
        return -1; //couldn't find product
      }
    }
    else{//must be on correct product
      if(parent->stock >= num){
        parent->stock -= num;
        num *= parent->price;
        return num;
      }
      else{
        return -1;
      }
    }
  }
}


node* findProduct(node *root, node *parent, node *n){
  //root is empty / not created so can't make purchase
  if(strlen(root->productName) == 0){
    return n;
  }
  else{ 
    //product on left branch of node
    if(strcmp(n->productName, parent->productName) < 0){
      if(parent->childLeft){
        findProduct(root, parent->childLeft, n);
      }
      else{
        return n; //couldn't find product
      }
    }
    //product on right branch of node
    else if(strcmp(n->productName, parent->productName) > 0){
      if(parent->childRight){
        findProduct(root, parent->childRight, n);
      }
      else{
        return n; //couldn't find product
      }
    }
    else{//must be on correct product
      if(parent->price > 0){
        return parent;
      }
      else{
        return n;
      }
    }
  }
  
}



