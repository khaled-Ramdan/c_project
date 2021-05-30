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
void Delete( int id);
void delete_book();
void printList();
void searchWithId(int id);
int returnId(const char*name);
int length();
bool strCompare(const char* str1,const char* str2);
void fileReading();
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
void fileReading()
{
	//temporary variables to be read
   char tmpName[30];
   char tmpType[30];
   char tmpAbout[100];
   int tmpPrice;
   int tmpId;
   FILE* myfile;
   myfile= fopen("record.txt","rb");//file reading
   if (myfile == NULL)
   printf("Eror oppening the file \n");
   else{
       while(fread(&tmpId,sizeof(tmpId),1,myfile)==1&&fread(&tmpPrice,sizeof(tmpPrice),1,myfile)==1&&fread(&tmpName,sizeof(tmpName),1,myfile)==1&&fread(&tmpType,sizeof(tmpType),1,myfile)==1&&fread(&tmpAbout,sizeof(tmpAbout),1,myfile)==1){
       sortedAppend(tmpId,tmpPrice,tmpName,tmpType,tmpAbout);
       }
   }
   fclose(myfile);
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
   if(head==NULL)
   {
       int cpyNum;
         printf("Enter number of copies: ");scanf("%d",&cpyNum);
         for(int i=0;i<cpyNum;i++)sortedAppend(id,price,name,type,about);
          printf("Book is added successfuly\n");
   }
   else{
   while (current!=NULL)
   {
   //check on string
    flagName=strCompare(current->name,name);//compare two strings
   //check
     if(id==current->id && flagName==0)//same id different name
      {
         printf("Invalid value,this id exists for another book name\n");
         //short menu display return to main or same process
         //......
         return;
      }
      else if(flagName==1 && id!=current->id)//same name different id
      {
         printf("Invalid value,this name exists for another book id\n");
         //short menu display return to main or same process
         //........
         return;
      }
      current=current->next;
   }
      int cpyNum;
      printf("Enter number of copies: ");scanf("%d",&cpyNum);
      for(int i=0;i<cpyNum;i++)sortedAppend(id,price,name,type,about);
      printf("Book added successfuly\n");
      return;
   }
}

void Delete(int id) 
{
   node* current = head;
   node* previous = NULL;
   if(head == NULL) {//if list is empty
      printf("List is Empty!!!\n");
      return;
   }
   while(current->id != id) { //navigate through list
      if(current->next == NULL) { //if it is last node
         printf("Book not found!!!\n");
         return;
      } else {
         previous = current;//store reference to current link
         current = current->next;//move to next link
      }
   }
   if(current == head) {//found a match, update the link
      head = head->next;//change first to point to next link
   } else {
      previous->next = current->next;  //bypass the current link
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
     while( x != 1 && x != 2);//user can choose only 1 or 2
    if( x == 1)
    {
        printf("please, Enter the id to delete: ");
        scanf("%d",&id );
        printf("How many copies? : ");
        scanf("%d",&cpyNum);
      int count=countbooks(id);//git number of copies of abooks
      if (count==0)printf("Id not found!!\n");
      else if(cpyNum<0||cpyNum>count&&count!=0)printf("Number of copies is out of range\n ");//negative number or more than exisit books
      else{
      for(int i=0;i<cpyNum;i++)Delete(id);
      puts("The deletion process was successful.");
      }
    }

    else if ( x == 2)
    {
      printf("please, Enter the name to delete: ");
      scanf("\n");scanf("%[^\n]",name);
      id = returnId(name);//get the id of the name
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
      for(int i=0;i<cpyNum;i++)Delete(id);
      puts("The deletion process was successful.");
      }
      }
    }
}
void searchWithId(int id) {
   node* current = head;
   if(head == NULL) {  //if list is empty
      printf("There is no data, list is empty\n");
      return;
   }
   while(current->id != id) {  //navigate through list
      if(current->next == NULL) {printf("Book not found\n");return;} //if it is last node
      else current = current->next;//go to next link
   }
   //if data found, display the current node
   printf("name: %-30s\ttype: %-12s\tprice: %2d\tid: %3d\tabout?: %s\n",current->name,current->type,current->price,current->id,current->about);
   return;
}
	
int returnId(const char*name)
{
   node*current=head;
   bool flag=0;
   while (current!=NULL)
   {
   flag = strCompare(name,current->name);
      if(flag==1)break;   
      current=current->next;
   }
   if(flag==1)return current->id;
   else return -1;
}

 bool strCompare(const char* str1,const char* str2)
{
   int flag=0;
   for(int i=0;str2[i]!='\0';i++)
   {
      if(str2[i]==str1[i])flag=1;
      else
      {
         flag=0;
         return flag;
      }
   }
   return flag;  
}

int length()
{
   int length = 0;
   node *current;
 
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
 
   return length;
}
}
