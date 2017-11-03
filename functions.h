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


float removeFromTree(node *root, node *parent, node *n);


void displayNode(node *node);


void findLevelOrder(node* *array[15],node *root, node *parent, int row, int column, int remaining, int prevDepth);


float makePurchase(node *root, node *parent, node *n, int num);


node* priceCheck(node *root, node *parent, node *n);


node* findProduct(node *root, node *parent, node *n);


void saveState(node* *array[100]);


#endif
