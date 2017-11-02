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

  setRoot(root);
  loadData(root);

  findLevelOrder(array, root, root, 0, 0, 0, 0);
/*
  for(i = 0; i < 100; i++){
    free(array[i]);
  }
*/
}
