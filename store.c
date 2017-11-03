#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
  node *root = malloc(sizeof(node));


  node* *array[100];

  int i;
  for(i = 0; i < 100; i++){
    if(i == 0){
      array[i] = malloc(1 * sizeof(node*));
    }
    array[i] = malloc(2 * i * sizeof(node*));
  }

  cleanNode(root);
  loadData(root);

  findLevelOrder(array, root, root, 0, 0, 1, 0);
  displayMenu();
/*
  for(i = 0; i < 100; i++){
    free(array[i]);
  }
*/
  while(1){
    float num, basket;
    char usrInput[20];
    char checkExit[20];
    node *n = malloc(sizeof(node));
    
    fprintf(stderr, "Input: ");

    fgets(usrInput, 20, stdin);
    sscanf(usrInput, "%f", &num);
    sscanf(usrInput, "%s", checkExit);
    if(strcmp(checkExit, "exit") == 0){
      fprintf(stderr, "Thank you for shopping at Miles grocery store!\n");
      break;
    }
    if(num == 1){ 
      fprintf(stderr, "Enter product name: ");
      fgets(usrInput, 20, stdin);
      cleanNode(n);
      sscanf(usrInput, "%s", usrInput);
      strcpy(n->productName, usrInput);

      fprintf(stderr, "Enter number in stock: ");
      fgets(usrInput, 20, stdin);
      sscanf(usrInput, "%f", &num);
      n->stock = num;
      
      fprintf(stderr, "Enter unit type: ");
      fgets(usrInput, 20, stdin);
      sscanf(usrInput, "%s", usrInput);
      strcpy(n->unit, usrInput);

      fprintf(stderr, "Enter product price: ");
      fgets(usrInput, 20, stdin);
      sscanf(usrInput, "%f", &num);
      n->price = num;
      
      fprintf(stderr, "Enter price per unit: ");
      fgets(usrInput, 20, stdin);
      sscanf(usrInput, "%s", usrInput);
      strcpy(n->pricePerUnit, usrInput);
      fprintf(stderr, "\n");
      
     addToTree(root, root, n);
    }
    else if(num == 2){
      fprintf(stderr, "Enter product name: ");
      fgets(usrInput, 20, stdin);
      cleanNode(n);
      sscanf(usrInput, "%s", usrInput);
      strcpy(n->productName, usrInput);

      fprintf(stderr, "Enter quantity: ");
      fgets(usrInput, 20, stdin);
      sscanf(usrInput, "%f", &num);
      
      //makePurchase(root, n, num);

    }
    else if(num == 3){

    }
    else if(num == 4){
      findLevelOrder(array, root, root, 0, 0, 1, 0);
    }
    else if(num == 5){

    }
    else if(num == 6){

    }
    else if(num == 7){

    }
   
  }
}
