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
  displayMenu();

  //findLevelOrder(array, root, root, 0, 0, 1, 0);
/*
  for(i = 0; i < 100; i++){
    free(array[i]);
  }
*/
  float basket = 0;
  while(1){
    float num = -1;
    char usrInput[20];
    char checkMenu[20];
    node *n = malloc(sizeof(node));
    
    fprintf(stderr, "\nInput: ");

    fgets(usrInput, 20, stdin);
    sscanf(usrInput, "%f", &num);
    sscanf(usrInput, "%s", checkMenu);

    if(strcmp(checkMenu, "menu") == 0){
      displayMenu();
    }
    else{
      if(num == 1){//add product
        fprintf(stderr, "Enter product name: ");
        fgets(usrInput, 20, stdin);
        cleanNode(n);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->productName, usrInput);

        fprintf(stderr, "Enter number in stock: ");
        fgets(usrInput, 20, stdin);
        n->stock = atof(usrInput);
        while(n->stock == 0){
          fprintf(stderr, "Invalid Input\n");
          fprintf(stderr, "Enter number in stock: ");
          fgets(usrInput, 20, stdin);
          n->stock = atof(usrInput);      
        }

        fprintf(stderr, "Enter unit type: ");
        fgets(usrInput, 20, stdin);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->unit, usrInput);

        fprintf(stderr, "Enter product price: ");
        fgets(usrInput, 20, stdin);
        n->price = atof(usrInput);
        while(n->price == 0){
          fprintf(stderr, "Invalid Input\n");
          fprintf(stderr, "Enter product price: ");
          fgets(usrInput, 20, stdin);
          n->price = atof(usrInput);
        }

        fprintf(stderr, "Enter price per unit: ");
        fgets(usrInput, 20, stdin);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->pricePerUnit, usrInput);
        fprintf(stderr, "\n");
      
        addToTree(root, root, n);
      }
      else if(num == 2){//purchase product
        fprintf(stderr, "Enter product name: ");
        fgets(usrInput, 20, stdin);
        cleanNode(n);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->productName, usrInput);
 
        fprintf(stderr, "Enter quantity: ");
        fgets(usrInput, 20, stdin);
        sscanf(usrInput, "%f", &num);
        num = atof(usrInput);
        while(num == 0){
          fprintf(stderr, "Invalid Input\n");
          fprintf(stderr, "Enter quantity: ");
          fgets(usrInput, 20, stdin);
          sscanf(usrInput, "%f", &num);
          num = atof(usrInput);
        }      

        num = makePurchase(root, root, n, num);
      
        if(num == -1){
          fprintf(stderr, "Unable to complete purchase\n\n");
        }
        else{
          fprintf(stderr, "Cost of product %.2f\n", num);
          basket += num;
        }
      }
      else if(num == 3){//check price of product
        cleanNode(n);
 
        fprintf(stderr, "Enter product name: ");
        fgets(usrInput, 20, stdin);
        cleanNode(n);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->productName, usrInput);

        n = findProduct(root, root, n);


        if(n->price == 0){
          fprintf(stderr, "Price check failed!\n"); 
        }
        else{
          fprintf(stderr, "Price is: %.2f %s\n", n->price, n->pricePerUnit);
        }
      }
      else if(num == 4){//display all products
        //findLevelOrder finds all nodes on binary tree breadth first
        findLevelOrder(array, root, root, 0, 0, 1, 0);
      }
      else if(num == 5){//remove products
        cleanNode(n);
 
        fprintf(stderr, "Enter product name: ");
        fgets(usrInput, 20, stdin);
        cleanNode(n);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->productName, usrInput);

        num = removeFromTree(root, root, n);
        fprintf(stderr, "num: %.2f\n", num);

      }
      else if(num == 6){//show product
        cleanNode(n);
 
        fprintf(stderr, "Enter product name: ");
        fgets(usrInput, 20, stdin);
        cleanNode(n);
        sscanf(usrInput, "%s", usrInput);
        strcpy(n->productName, usrInput);

        n = findProduct(root, root, n);
        
        if(n->price == 0){
          fprintf(stderr, "Price check failed!\n");  
        }
        else{
          displayNode(n);
        }

      }
      else if(num == 7){//check sales / inventory
        findLevelOrder(array, root, root, 0, 0, 1, 0); 
        fprintf(stderr, "Current sales: %.2f\n", basket);
      }
      else if(num == 8){
        fprintf(stderr, "Thank you for shopping at Miles grocery store!\n");

        
        break;
      }
    }
   
  }
}
