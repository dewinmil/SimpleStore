#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
  node* root;
  //setRoot(root);
  loadData(root);
  //displayNode(&root);
  //displayNode(root.childRight);

  node* *array[100];
  findLevelOrder(array, root, root, 0, 0, 0, 0);
}
