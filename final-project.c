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
int choss=100;
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
void total_stored();
void fileWriting();
void displayBook();
void updatePrice();
void searchBook();
int signIn();
void manageSecurity();
void choose();
void menu();
void End();
void draw(void);
void drawforsearch(void);
void gotoxy(int , int );
void searchWithType(char* type);
void delay(int);
void (*fun[])() ={addBook,delete_book,searchBook,updatePrice,total_stored,displayBook,manageSecurity,End};
void main() {
	//reading from the file
	static int dontRepeat = 0;
	static int flagSingIn;
	if (dontRepeat == 0){
	system("color 6");
	fileReading();//read file after startung
	flagSingIn = signIn();//sign in only one time
	}
	dontRepeat = 1;//breaking main loop
	if (flagSingIn == 1)
	{
		printf("\n\n\t\t\t\t\t\t WELCOME to the book date base program.");
		menu();
		int num;
		do {
			printf("\n\n\n\n\n   \t\t\t\t\t\t choose a Number: ");
			scanf("%d", &num);
		} while (num < 1 || num > 8);
		system("cls");//new
		fun[num - 1]();
		if (choss == 0) { printf("Program Ended\n"); fileWriting();return 0; }
		do {
			choose();
			do {
			      printf("\n\n\t\tchoosen Number: ");
			      scanf("%d", &choss);
			} while (choss != 1 && choss != 2);
			if (choss == 1)
			{
			   system("cls");
			   fun[num - 1]();
			}
		  } while (choss == 1);

			if (choss == 2)
			{
			  main();
			}
	}
	else
	{
	printf("Program Ended\n");
	return 0;
	}
	system("pause");
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
void total_stored()
{
   printf("Number of total stored books = %d",length());
}
void fileWriting()
{
   node*tmpNode=head;
   FILE* myfile;
   myfile = fopen("record.txt","wb");
   while (tmpNode!=NULL)
   {
      //appending data in file
      fwrite(&(tmpNode->id),sizeof(tmpNode->id),1,myfile);
      fwrite(&tmpNode->price,sizeof(tmpNode->price),1,myfile);
      fwrite(&tmpNode->name,sizeof(tmpNode->name),1,myfile);
      fwrite(&tmpNode->type,sizeof(tmpNode->type),1,myfile);
      fwrite(&tmpNode->about,sizeof(tmpNode->about),1,myfile);
      //counter
      tmpNode=tmpNode->next;
   }
 fclose(myfile);
}

void displayBook()
{
   printf("\t\t\t\tDisplaying books\n");
   int check=0;
   do{
       printf("[1] Display all books with shrot informations\n[2] Display one book with all informations\n");
      printf("choosen way: ");
      scanf("%d",&check);
   }while(check!=1&&check!=2);
   switch (check)
   {
   case 1:
      {
         printList();
      break;
      }
      case 2:
      {
         searchBook();
         break;
      }
   default:
   printf("Erorr, can't take a decesion\n");
      break;
   }
}
void searchBook()
{
   int check=0;
   char temp[30];
   do{
   printf("\t\t\t[1] Search with name\n\t\t\t[2] Search with ID\n\t\t\t[3] Search with type\n\t\tchoosen way: ");
   scanf("%d",&check);
   }while(check!=1&&check!=2&&check!=3);
   switch (check)
   {
   case 1:
      {
         printf("Enter a book name to search: ");
         scanf("\n");scanf("%[^\n]",temp);
         searchWithId(returnId(temp));
         break;
      }
      case 2:
      {
         printf("Enter a book ID to search: ");
         int id;
         scanf("%d",&id);
         searchWithId(id);
         break;
      }
         case 3:
      {
         printf("Enter a book type to search: ");
         scanf("\n");scanf("%[^\n]",temp);
         searchWithType(temp);
         break;
         }
      
   default:
      printf("Error, can't take a desision!!\n");
      break;
   }
}
int signIn()
{

   //defulat pass
   char user[30]={"admin"};char userTemp[30];
   char password[10]={"0000"};char passwordTemp[10];
   //reading edited password from file
   FILE*manage;
   manage = fopen("manage.txt","rb");
   if(manage==NULL)printf("Defult password activated!!!\n");
   else{
      fread(user,30,1,manage);
      fread(password,10,1,manage);
   }
   //checking
   printf("\t\t\t\t\t*Welcome in the book data base program*\nplease sgin in to get acsess\n");
   printf("\t\t\tUser name: ");scanf("%s",userTemp);
   printf("\t\t\tPassword: ");scanf("%s",passwordTemp);
   int c;char ch;
   while( strCompare(userTemp,user)!=1 || strCompare(passwordTemp,password)!=1 )
   {
      printf("Wrong user name or password. Enter -1 to close the program or any key to resign in: ");
      scanf("%d",&c);
      if (c== -1)return -1;
      else
      {
          
         do{scanf("%c",&ch);}while (ch!='\n');//make sure there is a one char or repeat not to be located for next variable

      printf("\t\t\tUser name: ");scanf("%s",userTemp);
      printf("\t\t\tPassword: ");scanf("\n");scanf("%s",passwordTemp);
      }
   }
   printf("\n\nPassword Match!\nLOADING");
		for (int z = 0; z <70; z++)
		{
			delay(10000000);
		}

   return 1;
}
void manageSecurity(){
   char user[30];
   char password[10];
    if(signIn()==1)
   {
      printf("You can change the user name and password\n");
      printf("Enter new user name: ");
      scanf("%s",user);
      printf("Enter new password: ");
      scanf("%s",password);
      FILE*manage;
      manage = fopen("manage.txt","wb");
      fwrite(user,30,1,manage);
      fwrite(password,10,1,manage);
      fclose(manage);
   }
   else
   {
      printf("End of the program\n");
      fun[7]();
   }
}
void updatePrice()
{
    int ID=0;
    printf("\t\t\t\tUpating book price\n");
      int check=0;
   do{
   printf("\t\t\t[1] Update with name\n\t\t\t[2] Update with ID\n\t\tchoosen way: ");
   scanf("%d",&check);
   }while(check!=1&&check!=2);
   switch (check)
   {
      case 1:
      {
         char tmp[30];
         printf("Enter book name: ");
         scanf("\n");scanf("%[^\n]",tmp);
         ID=returnId(tmp);
         break;
      }
       case 2:
      {
         printf("Enter book ID: ");
         scanf("%d",&ID);
         break;
      }
      default:
      printf("\t\t\tError, can't take a desision!!\n");
      break;
   }
   {
    node* temp = head;
    while(temp!=NULL){//until last node

        if(temp->id==ID){//finding the desird node
            printf("Record with id %d Found !!!\n", ID);
            printf("Enter new price: ");
            scanf("%d", &temp->price);
            printf("Updation Successful!!!\n");
            return;
        }
        temp = temp->next;//counter
    }
    printf("\t\t\tbook with ID: %d is not found !!!\n",ID);
}
}
void choose()
{
	printf("\n\t\t\t\t");
	for (int i = 0; i < 57; i++)
	{
	   printf("#");
	}
	printf("\n\t\t\t\t#\t\t1-Return to the same process\t\t#\n\t\t\t\t#\t\t2-Return to the main menu\t\t#\n");
	printf("\t\t\t\t");
	for (int i = 0; i < 57; i++)
	{
	   printf("#");
	}
}
void menu()
{
	system("cls");
	system("color 9");
	printf("\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO OUR MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
	draw();
	gotoxy(30, 3);
	printf("[1] Add a book");
	gotoxy(30, 5);
	printf("[2] Delete a book");
	gotoxy(30, 7);
	printf("[3] search for a book");
	gotoxy(30, 9);
	printf("[4] Update book price");
	gotoxy(30, 11);
	printf("[5] Get number of books stored");
	gotoxy(30, 13);
	printf("[6] Display stored books");
	gotoxy(30, 15);
	printf("[7] manage security");
	gotoxy(30, 17);
	printf("[8] End program and save");
}
void End()
{    choss=0;
    system("cls");
    system("color 4");
    system("title Program Ended");
    delaying("Ending.");
    Sleep(3);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw(void)
{
	gotoxy(23, 2);
	printf("%c", 201);
		for (int i = 1; i < 40; i++)
		{
		   printf("%c", 205);
		}
	printf("%c", 187);
	for (int j = 0; j <17; j++)
	{
           gotoxy(23, 3 + j);
	   printf("%c", 186);
		for (int i = 1; i < 40; i++)
		{
			printf(" ");
		}
	   printf("%c", 186);
	}
	gotoxy(23, 20); printf("%c", 200);
		for (int k = 1; k < 40; k++)
		{
			printf("%c", 205);
		}
	printf("%c", 188);
}
void drawforsearch(void)
{
	gotoxy(15, 5);
	printf("%c", 201);
		for (int i = 1; i < 70; i++)
		{
		   printf("%c", 205);
		}
	printf("%c", 187);
		for (int j = 0; j <11; j++)
		{
		  gotoxy(15, 6 + j);
		  printf("%c", 186);
			for (int i = 1; i < 70; i++)
			{
			   printf(" ");
			}
		  printf("%c", 186);
		}
	gotoxy(15, 16); 
	printf("%c", 200);
		for (int k = 1; k < 70; k++)
		{
		 printf("%c", 205);
		}
	printf("%c", 188);
}

void searchWithType(char* type)
{
   node*current=head;
   int flag=0,temp=0;
   while (current!=NULL)//loop in the list
   {
      if(strCompare(type,current->type))
      {
         flag=1;
         if(temp!=current->id){//don't print
            printf("name: %-30s\tprice: %2d\tid: %3d\tabout?: %s\n",current->name,current->price,current->id,current->about);
         }
      }
      temp=current->id;
      current=current->next;//counter
   }
   if(flag==0)printf("This type of books not found\n");
}
void delay(int j)
{
int i, k;
for (i = 0; i<j; i++)
	k = i;
}
