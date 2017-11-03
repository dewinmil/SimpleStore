#ifndef FUNCTIONS_H
#define FUNCTIONS_H


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


node root;


void displayMenu();


void cleanNode(node *n);


int findFileSize(char* string);


void addToTree(node *root, node *parent, node *n);


char* loadData();


void saveData(node *root);


void removeFromTree(node *n);


void displayNode(node *node);


int findLevelOrder(node* *array[100],node *root, node *parent, int row, int column, int remaining, int prevDepth);



float makePurchase(node *root, node *parent, node *n, int num);


#endif
