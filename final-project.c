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
    struct node *next;
};
typedef struct Node node;
struct Node *head = NULL;
struct Node *current = NULL;
void sortedAppend(int id, int price,char*name,char*type,char*about);
void checkNameWithId(int id, int price,char*name,char*type,char*about);
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
void checkNameWithId(int id, int price,char*name,char*type,char*about)
{
   node*current=head;
   int flagName;
   char temp[30];
   if(head==NULL)
   {
       int cpyNum;
         printf("Append\t");
         printf("Enter number of copies: ");scanf("%d",&cpyNum);
         for(int i=0;i<cpyNum;i++)sortedAppend(id,price,name,type,about);
   }
   else{
   while (current!=NULL)
   {
      //check on string
   strcpy(temp,current->name);
   for(int i=0;name[i]!='\0'&&current!=NULL;i++)
   {
      if(temp[i]==name[i])flagName=1;
      else
      {
         flagName=0;
         break;
      }
   }  
   //check
     if(id==current->id && flagName==0)
      {
         printf("Invalid value,this id exists for another book name\n");
         //short menu display return to main or same process
         //......
         break;
      }
      else if(flagName==1 && id!=current->id)
      {
         printf("Invalid value,this name exists for another book id\n");
         //short menu display return to main or same process
         //........
         break;
      }
      else
      {
         int cpyNum;
         
         printf("Enter number of copies: ");scanf("%d",&cpyNum);
         for(int i=0;i<cpyNum;i++)sortedAppend(id,price,name,type,about);
         printf("Book added successfuly\n");
         break;
      }
      current=current->next;
   }
   }
}