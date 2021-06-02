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
void addBook();
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
return c;
}

void printList()
{
   node *ptr = head;
   int cpyNum=1;
   if(length()==0){printf("There is no books stored\n");return;}
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
          printf("\t\t\tBook is added successfuly\n");
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
        printf("\t\t\t[1] Delete by id\n\t\t\t[2] to delete by name\n\tchoosen number: ");
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
      for(int i=0;i<cpyNum;i++)Delete(id);
      printf("\tRemaning Number of copies: %d\n",countbooks(id));
      puts("\t\t\tThe deletion process was successful.");
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
      for(int i=0;i<cpyNum;i++)Delete(id);
      printf("\tRemaning Number of copies: %d\n",countbooks(id));
      puts("\t\t\tThe deletion process was successful.");
      }
      }
    }

}
void searchWithId(int id) {
system("cls");

	 node*current = head;
	if (head == NULL) {  //if list is empty
		printf("There is no data, list is empty\n");
		return;
	}
	while (current->id != id) {  //navigate through list
		if (current->next == NULL) { printf("Book not found\n"); return; } //if it is last node
		else current = current->next;//go to next link
	}
   drawforsearch();
	//if data found, display the current node
	gotoxy(16, 7);
	printf("\t\tname:    %-s\n", current->name);

	gotoxy(16, 8);
	printf("\t\ttype:   %s\n", current->type);

	gotoxy(16, 9);
	printf("\t\tprice:   %d\n", current->price);

	gotoxy(16, 10);
	printf("\t\tid:      %d\n", current->id);

   gotoxy(16, 11);
	printf("\t\tNumber of copies:   %d\n", countbooks(current->id));

	gotoxy(16, 12);
	printf("\t\tAbout:   %s\n", current->about);
	gotoxy(16, 17);
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
   int L1=0,L2=0;
   while(str1[L1]!='\0')L1++;//length 1
   while(str2[L2]!='\0')L2++;//length 2
   if(L1==L2){
   for(int i=0;str2[i]!='\0';i++)
   {
      if(str2[i]==str1[i])flag=1;
      else
      {
         flag=0;
         return flag;
      }
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
void addBook()
{
   int c;
   char ch;
   char tmpName[30];
	char tmpType[30];
	char tmpAbout[100];
	int tmpPrice;
   int tmpId;
   printf("\t\t\t\tAdding books\n");
   do
	{
		printf("Enter name: ");scanf("\n");scanf("%[^\n]",tmpName);
		printf("Enter id: ");scanf("%d",&tmpId);
      printf("Enter price: ");scanf("%d",&tmpPrice);
      printf("Enter type: ");scanf("\n");scanf("%[^\n]",tmpType);
      printf("Enter Further information: ");scanf("\n");scanf("%[^\n]",tmpAbout);
      checkNameWithId(tmpId,tmpPrice,tmpName,tmpType,tmpAbout);
		printf("\t\t\t[1] = add another book.\n\t\t\t[other] = finish\n\t\t\tchoosen way: ");
      scanf("\n%d",&c);
      do{scanf("%c",&ch);}while (ch!='\n');//make sure there is a one char or repeat not to be located for next variable
	}while ( c== 1 );
}
