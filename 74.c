#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
struct collection
{
 char name[30];
 float cost;
 int quantity;
 int age1;
 int age2;
};
void add (char*);
void edit (char*);
void show(char*);
void search (char*);
void del (char*);
int main(int argc,char* argv[])
{
 SetConsoleCP(1251);
 SetConsoleOutputCP(1251);
 setlocale(LC_ALL,"Rus");
 char filename[50];
 int menu;
 puts("File name");
 gets (filename);
 FILE *f;
 if ((f=fopen(filename,"ab"))==NULL)
 perror ("Create error");
 fclose(f);
 do
 {
 system("CLS");
 puts ("1. Add note");
 puts ("2. Edit note");
 puts ("3. View note");
 puts ("4. Search");
 puts ("5. Remove note");
 puts ("6. Exit");
 scanf ("%d%*c",&menu);
 switch (menu)
 {
 case 1 : add (filename); break;
 case 2 : edit (filename); break;
 case 3 : show (filename); break;
 case 4 : search (filename);break;
 case 5 : del (filename);
 }
 }
 while (menu!=6);
 return 0;
}
struct collection input_toy (void)
{
 struct collection toy;
 puts ("Name");
 gets(toy.name);
 puts ("Cost");
 while((scanf("%f",&toy.cost)==0)||toy.cost<0);
 {
 fflush(stdin);
 }
 puts ("Quantity");
 scanf("%d",&toy.quantity);
 puts ("Up");
 while((scanf("%d", &toy.age1 )==0)||toy.age1<0)
 {
 printf("Error\n");
 fflush(stdin);
 puts ("To");
 }
 puts ("To");
 while((scanf("%d", &toy.age2 )==0)||toy.age2<0)
 {
 printf("Error\n");
 fflush(stdin);
 puts ("To");
 }
 return toy;
}
void print1 (struct collection data)
{
 printf ("Name : %s\nCost : %f\nQuantity : %d\nUp : %d\nTo :%d\n",data.name,data.cost,data.quantity,data.age1,data.age2);
}
void add(char* file)//добавление одной структуры в файл
{
 FILE *f;
 struct collection toy;
 setlocale(LC_ALL,"Rus");
 system ("CLS");
 if ((f=fopen(file,"ab"))==NULL)
 {
 perror ("Error file open");
 getchar();
 return;
 }
 toy = input_toy();
 fwrite(&toy, sizeof(toy),1,f);
 fclose(f);
}
void edit (char* file)
{
 setlocale(LC_ALL,"Rus");
 FILE *f;
 struct collection toy;
 int cost;
 char name[30];
 char yes;
 system("CLS");
 if ((f=fopen (file,"rb+"))==NULL)
 {
 perror ("Error file open"); getchar();
 return;
 }
 printf("Name: "); gets(name);
 while (fread(&toy,sizeof(toy),1,f))
 if (!strcmp(toy.name,name))
 {
 print1(toy);
 puts ("Edit?(y/n)");
 do
 {
 yes = getchar(); getchar();
 }
 while (yes!='y' && yes!='Y' && yes !='n' && yes!='N');
 if (yes=='y' || yes=='Y')
 {
 toy = input_toy();
 fseek(f,-sizeof(toy),SEEK_CUR);
 fwrite(&toy,sizeof(toy),1,f);
 fseek(f,0,SEEK_CUR);
 }
 }
 puts ("Search completed"); getchar();
 fclose(f);
}
void show (char* file)
{
 setlocale(LC_ALL,"Rus");
 FILE *f;
 struct collection toy;
 char menu,name[30]="Name not found";
 int k=0,i,n=0,age1=0,age2=0,kol=0;
 float Cost=0;
 long len;
 unsigned int num = 1, num_last;
 system("CLS");
 if((f=fopen(file,"rb"))==NULL)
 {
 perror("Error file open");
 getchar();
 return;
 }
 puts("| є | Name | Cost | Quantity | Up/to |");
 puts("----------------------------------------------------------------------------------------------------");
 while (fread(&toy,sizeof(toy),1,f)==1){
 n=0;
 for(i=0;i<20;i++)
 {
 if
((toy.name[i]=='к'||toy.name[i]==' ')&&toy.name[i+1]=='о'&&toy.name[i+2]=='н'
&&

toy.name[i+3]=='с'&&toy.name[i+4]=='т'&&toy.name[i+5]=='р'&&toy.name[i+6]=='у'&&toy.name[i+7]=='к'&&toy.name[i+8]=='т'&&toy.name[i+9]=='о'&&toy.name[i+10]=='р')
 {
 n++;
break;
 }
 }
 if(Cost<toy.cost&&n){
 Cost=toy.cost;
 strcpy(name,toy.name);
 age1=toy.age1;
 age2=toy.age2;
 kol=toy.quantity;
 }
 printf("|%4d|%24s|%20.2f|%22d| от %3d до %3d|\n",++k,toy.name,toy.cost,toy.quantity,toy.age1,toy.age2);
 }
 puts("----------------------------------------------------------------------------------------------------");
 printf("—ведени€ о самом дорогом конструкторе\nName:%s\nCost:%.2f\nQuantity:%d\nUp: %d To %d",name,Cost,kol,age1,age2);
 fclose (f);
 getchar();
}
void search (char* file)
{
 setlocale(LC_ALL,"Rus");
 FILE *f;
 struct collection toy;
 int Cost,Age1=0,quan=0;
 int flag=0;
 char name[40];
 system("CLS");
 if((f=fopen(file,"rb"))==NULL)
 {
 perror("Error file open"); getchar();
 return;
 }
 puts("Cost?"); scanf("%d",&Cost);
 puts("Up/To?"); scanf("%d",&Age1);
 puts("| Name | Cost | Quantity | Up/To |");
 puts("-----------------------------------------------------------------------------------------------");
 while (fread(&toy,sizeof(toy),1,f)==1){
 if ( toy.cost <=Cost && (toy.age1<=Age1 && toy.age2>=Age1))
 {
 printf("|%24s|%20.2f|%22d| от %3d до %3d|\n",toy.name,toy.cost,toy.quantity,toy.age1,toy.age2);
 flag++;
 }
 }
 if (flag == 0) puts ("---");
 fclose(f);
 getchar();getchar();
}
void del(char*file)
{
 setlocale(LC_ALL,"Rus");
 FILE *f1, *f2;
 unsigned int y,n_file,i=0,j=0,flag,age1,age2,quantity;
 float cost;
 char name[40];
 struct collection toy;
 system ("CLS");
 if ((f1=fopen(file,"r"))==NULL)
 {
 perror("Error file open"); getchar();
 return;
 }
 fseek(f1,0,SEEK_END);
 n_file = ftell(f1) / sizeof(toy);
 if (n_file == 0)
 {
 puts("File clear"); getchar();
 return;
 }
 puts("Enter Ќазвание удал€емой записи?");
 scanf("%s",&name);
 puts("Enter стоимость удал€емой записи?");
 scanf("%f",&cost);
 puts("Enter количество удал€емой записи?");
 scanf("%u",&quantity);
 puts ("Enter возрастные границы удал€емой записи?");
 scanf("%u",&age1);
 scanf("%u",&age2);
 rewind(f1);
 if((f2=fopen("temp.dat","wb"))==NULL)
 {
 perror("Error file open");
 getchar();
 return;
 }
 while (fread(&toy,sizeof(toy),1,f1)==1)
 {
 flag=0;
 i++;
 if (strcmp(toy.name,name)==0)
 flag++;
 if (toy.cost==cost)
 flag++;
 if (toy.quantity==quantity)
 flag++;
 if (toy.age1==age1 && toy.age2==age2)
 flag++;
 if (flag!=4){
 fwrite (&toy,sizeof(toy),1,f2);
 j++;
 }
 }
 if (i!=j)
 puts("Note removed");
 else
 puts("Note not exist");
 fclose(f1);
 fclose(f2);
 remove(file);
 rename("temp.dat",file);
 getchar();getchar();
}
