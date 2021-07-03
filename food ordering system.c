#include<stdio.h>
char password[10]={"codechamp"};
void mypassword();
void addfooditem();
void display();
void search();
void update();
void deletefooditem();
int attempt=1;
struct food_order
{
 char fname[50];
 int fcode;
 float fprice;
};
void main()
{
   clrscr();
   mypassword();
   getch();

}
void mainmenu()
{
 int ch;
 char chs;
 clrscr();
 printf("\n 1. Add new food item \n 2. Delete food item \n 3. search food item \n 4. update food item\n 5. Display food list\n");
 scanf("%d",&ch);
 switch(ch)
 {
  case 1:/* Add Records*/
	    addfooditem();
	    break;
  case 2:/*delete record*/
	    deletefood();
	    break;
  case 3:/* Sort Records*/
	search();
	    break;
  case 4:/* Search Records*/
	    update();
	    break;
  case 5:/* Display Records*/
	  display();
	  break;
 }
 printf("\n Do you want to perform more operation\t");
 fflush(stdin);
 scanf("%c",&chs);
 if(chs=='Y' || chs=='y')
  mainmenu();
 else
  exit(0);
 getch();
}

void addfooditem(void)
{
FILE *fp;
struct food_order s;
clrscr();
printf("Welcome to adding food record");
fp=fopen("food order","a");
printf("\n Enter food code:\t");
scanf("%fpd",&s.fname);
printf("Enter food code:\t");
scanf("%s",s.fcode);
printf("Enter food price:\t");
scanf("%s",s.fprice);
fwrite(&s,sizeof(struct food_order),1,fp);
fclose(fp);
printf("\nfood successfully added to the list");
getch();
}

void display()
{
 FILE *fp;
 struct food_order ret;
 fp=fopen("food","r");
 if(fp==NULL)
  {
   printf("\nFile not Exits");
   exit(0);
  }
  fseek(fp,0,SEEK_SET);
 printf("\n\t Food code.\t\tFood Name \t\tFood price\n");
 while(fread(&ret,sizeof(ret),1,fp)!=NULL)
  {
   ;
   printf("\t\t%d \t\t%s \t\t%s\n",ret.fcode,ret.fname,ret.fprice);
  }
  fclose(fp);
  printf("\n\n\n Enter any Key \t");
  getch();
}
void mypassword(void)
{
   char d[25]="Password Protected";
   char ch,pass[10];
   int i=0,j;
   clrscr();
   gotoxy(10,4);
    for(j=0;j<20;j++)
    {
    delay(50);
    printf("*");
    }
    for(j=0;j<20;j++)
   {
   delay(50);
   printf("%c",d[j]);
   }
   for(j=0;j<20;j++)
   {
   delay(50);
   printf("*");
   }
   gotoxy(10,10);
   gotoxy(15,7);
   printf("\nEnter Password:");
   ch=getch();
   while(ch!=13)
   {
    if(ch!=13 && ch!=8){
    putch('*');
    pass[i] = ch;
    i++;
    ch=getch();
    }
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {
    printf("Password match");
    gotoxy(17,10);
    printf("Press any key to countinue.....");
    getch();
    mainmenu();

   }
    else
   {
     gotoxy(15,16);
     printf("\aWarning!! Incorrect Password \n \t Please Try Again");
     getch();
     mypassword();
   }

}
 void search()
 {
   FILE *fp;
   int ser,found=0;
   struct food_order ret;
   clrscr();
   fp=fopen("foods","rb");
   if(fp==NULL);
    {
      printf("Food item doesn't exit\n");
      getch();
    }
    printf("enter food code to search\n");
    scanf("%d",&ser);
    while(1)
    {
      fread(&ret,sizeof(ret),1,fp);
      if(feof(fp))
       break;
      if(ret.fcode==ser)
       {
	 found=1;
	 printf("\nfood item is present in the list\n");
	 printf("\n the food item is %s",ret.fname);
	 break;
       }
    }
}
void update()
 {
   FILE *fp;
   int i,ser,found;
   struct food_order ret;
     clrscr();
     printf("enter food code to update:");
     scanf("%d",&ser);
   fp=fopen("food","rb+");
   if(fp==NULL)
   {
	printf("file does not exists");
	exit(0);
   }
   while(fread(&ret,sizeof(ret),1,fp)==1)
   {
     if(ret.fcode==ser)
     {
       printf("enter food name");
       scanf("%s",ret.fname);
       fseek(fp,-sizeof(ret),SEEK_CUR);
       found=fwrite(&ret,sizeof(ret),1,fp);
       break;
     }
   }
   fclose(fp);
   if(found==0)
    printf("\nfood item not found so can't perform update");
   else
    printf("\nfood list is updated");
}
void deletefooditem()
{
  FILE *fp,*ft;
  int i,ser,found;
    struct food_order ret;
    clrscr();
    printf("enter food code to delete:");
    scanf("%s",&ser);
    fp=fopen("foods","r");
    ft=fopen("foodf","wb");
    if(fp==NULL)
    {
	printf("\nfile does not exists");
	exit(0);
    }
    fseek(fp,0,SEEK_SET);
    while(fread(&ret,sizeof(ret),1,fp)==1);
    {
	if(ret.fcode!=ser)
	{
		fwrite(&ret,sizeof(ret),1,ft);
	}
    }
    fclose(fp);
    fclose(ft);
    remove("foods");
    rename("foodf","foods");
    remove("foodf");
}
