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
void sortedAppend(int id, int price,char*name,char*type,char*about);
void checkNameWithId(int id, int price,char*name,char*type,char*about);
int countbooks( int id);
void delete( int id);
void delete_book();
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
	if(temp==NULL)return c;
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
   node *ptr = head;
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

void delete(int id) 
{
   node* current = head;
   node* previous = NULL;
   if(head == NULL) {
      printf("List is Empty!!!\n");
      return;
   }
   while(current->id != id) {
      if(current->next == NULL) {
         printf("Book not found!!!\n");
         return;
      } else {
         previous = current;
         current = current->next;
      }
   }
   if(current == head) {
      head = head->next;
   } else {
      previous->next = current->next;
   }
 free(current);
   return;
}

void delete_book()
  {
     int x,id;
     int cpyNum=0;
     char name[30];
    puts("\t\t\t\t\tBy any way you want to delete" );
     do{
        printf("please, Enter number [1] to delete by id oR number [2] to delete by name:\n\tchoosen number: ");
        scanf("%d",&x);
     }
     while( x != 1 && x != 2);
    if( x == 1)
    {
        printf("please, Enter the id to delete: ");
        scanf("%d",&id );
        printf("How many copies? : ");
        scanf("%d",&cpyNum);
      int count=countbooks(id);
      if (count==0)printf("Id not found!!\n");
      else if(cpyNum<0||cpyNum>count&&count!=0)printf("Number of copies is out of range\n ");
      else{
      for(int i=0;i<cpyNum;i++)delete(id);
      puts("The deletion process was successful.");
      }
    }

    else if ( x == 2)
    {
      printf("please, Enter the name to delete: ");
      scanf("\n");scanf("%[^\n]",name);
      id = returnId(name);
      if(id==-1){
         printf("book not found!!\n");
      }
      else
      {
      printf("How many copies? : ");
      scanf("%d",&cpyNum);
      int count=countbooks(id);
      if (count==0)printf("Id not found!!");
      else if(cpyNum<0||cpyNum>count&&count!=0)printf("Number of copies is out of range\n ");
      else{
      for(int i=0;i<cpyNum;i++)delete(id);
      puts("The deletion process was successful.");
      }
      }
    }

  }


