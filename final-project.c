#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct Node {
	char name[30];
	char type[30];
	char about[100];
	int price;
   	int id;
    	struct Node *next;
};
typedef struct Node node;
struct Node *head = NULL;
struct Node *current = NULL;
void sortedAppend(int id, int price,char*name,char*type,char*about);
int countbooks( int id);
void printList();
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
void sortedAppend(int id, int price,char*name,char*type,char*about)
{
   node *newnode = (node *)malloc(sizeof(node));//making a new node in the memory
   //assigning data
   newnode->id = id;
   newnode->price=price;
   strcpy(newnode->name,name);
   strcpy(newnode->type,type);
   strcpy(newnode->about,about);
   //conecting the node in a porper place in the list
   newnode->next=NULL;
   node*currentPtr=head,*previousPtr=NULL;
   while (currentPtr != NULL && id >= currentPtr->id) {
      previousPtr = currentPtr; // walk to ...
      currentPtr = currentPtr->next; // ... next node
   }
   if(previousPtr==NULL)
   {
      newnode->next=head;
      head=newnode;
   }
   else{
      previousPtr->next=newnode;
      newnode->next=currentPtr;
   }
}

int countbooks(int id)
{
int i;
int c = 0;
struct node* temp = head;
while (temp!=NULL)
{
	if (temp->id == id)
	{
	   break;
	}
	temp = temp->next;
}
for (i =temp->id; temp != NULL&&temp->id == id; i++)
	{
	c++;
	temp = temp->next;
    }
printf("Number of copies:");
return c;
}

void printList()
{
   struct node *ptr = head;
   int cpyNum=1;
   while(ptr->next != NULL) {
      if(ptr->id!=ptr->next->id){//don't print more than with same id
         printf("book name: %-30s\tid: %3d\t Number of copies: %3d\n",ptr->name,ptr->id,cpyNum);   
         printf("\n");
         cpyNum=1;//to reset its value to the default value to began to count
      }
	  else { cpyNum++;}//count number of copies
      ptr=ptr->next;
   }
   printf("book name: %-30s\tid: %3d\t Number of copies: %3d\n",ptr->name,ptr->id,cpyNum);  
   return;
}
