#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct node {
	char name[30];
	char type[30];
	char about[100];
	int price;
    int id;
    struct node *next;
};
typedef struct node node;
struct node *head = NULL;
struct node *current = NULL;

void main() {
   //temporary used elements
    char tmpName[30];
	char tmpType[30];
	char tmpAbout[100];
	int tmpPrice;
    int tmpId;
    node*tmpNode;
    //reading from the file
}
