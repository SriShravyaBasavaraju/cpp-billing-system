
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
struct item
{
int sno;
int code;
char name[50];
int qty;
int price;
};
char sn[5],co[5],q[5],p[5],menu,submenu;
struct item s[50],rec;
int i,ch,n,x,y,nor,ca=0,size,nu,c,qt;
FILE *fp,*ft;
void add();
void menu1();
void submenu1();
void dis();
void admin();
void admini();
void display();
void modify();
int search(int);
void billing();
void branches();
void contact();
void exitmenu();
void entrymenu();
void table();
void menuloop();
void submenuloop();
void main()
{
int gdriver = DETECT, gmode;
 initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
fp=fopen("item.txt","rb+");
entrymenu();
do
{
menuloop();
}while(menu>='1' || menu<='5');
cleardevice();
closegraph();
}
void entrymenu()
{
cleardevice();
setcolor(RED);
 settextstyle(TRIPLEX_FONT,0,7);
 outtextxy(140,30,"Welcome To");
 settextstyle(GOTHIC_FONT,0,10);
 setcolor(WHITE);
 outtextxy(0,150,"Food World");
 settextstyle(SMALL_FONT,0,10);
 setcolor(RED);
 outtextxy(250,320,"...feel the taste");
 settextstyle(DEFAULT_FONT,0,1.8);
 setcolor(WHITE);
 outtextxy(150,450,"press any key to continue.....");
getch();
}
void menu1()
{
cleardevice();
setcolor(RED);
 settextstyle(TRIPLEX_FONT,0,5);
 outtextxy(0,0,"Food World...");
 outtextxy(150,130,">>> MENU <<<");
 setcolor(WHITE);
 settextstyle(TRIPLEX_FONT,0,3);
 outtextxy(210,210,"1. Administration");
 outtextxy(210,250,"2. Product Details");
 outtextxy(210,290,"3. Branches");
 outtextxy(210,330,"4. Contact Details");
 outtextxy(210,370,"5. Exit");
}
void menuloop()
{
menu1();
setcolor(RED);
settextstyle(DEFAULT_FONT,0,1.9);
 outtextxy(190,430,"please choose your menu option...");
menu=getch();
switch(menu)
{
case '1':admin();break;
case '2':
do
{
submenuloop();
}while(submenu>='1' && submenu<='4');
break;
case '3':branches();break;
case '4':contact();break;
case '5':exitmenu();break;
}
}
void submenu1()
{
cleardevice();
setcolor(RED);
 settextstyle(TRIPLEX_FONT,0,5);
 outtextxy(0,0,"Food World...");

 outtextxy(70,130,">>> Product Details<<<");
 setcolor(WHITE);
 settextstyle(TRIPLEX_FONT,0,3);
 outtextxy(190,210,"1. Display all items");
 outtextxy(190,250,"2. Add new items");
 outtextxy(190,290,"3. Modify existing items");
 outtextxy(190,330,"4. Billing");
}
void submenuloop()
{
submenu1();
setcolor(RED);
settextstyle(DEFAULT_FONT,0,1.9);
 outtextxy(190,430,"please choose any option...");
submenu=getch();
switch(submenu)
{
case '1':display();break;
case '2':add();break;
case '3':modify();break;
case '4':billing(); break;
}
}
void display()
{
cleardevice();
table();
rewind(fp);
fflush(stdin);
x=35;
y=85;
while(fread(&rec,sizeof(rec),1,fp)==1)
{
x=35;
if(y<(getmaxy()-50)) dis();
else
{
cleardevice();
table();
x=35;
dis();
}
y=y+30;
}
outtextxy(40,470,"press any key to continue...");
getch();
submenu1();
}
void dis()
{
char sn[10],co[10],q[10],p[10];
setcolor(WHITE);
   itoa(rec.sno,sn,10);
   itoa(rec.code,co,10);
   itoa(rec.qty,q,10);
   itoa(rec.price,p,10);
outtextxy(x,y,sn);
outtextxy(x+60,y,co);
outtextxy(x+210,y,rec.name);
outtextxy(x+430,y,q);
outtextxy(x+530,y,p);
}
void table()
{
cleardevice();
setcolor(WHITE);
rectangle(20,40,getmaxx()-20,getmaxy()-30);
line(20,70,getmaxx()-20,70);
line(70,40,70,getmaxy()-30);
line(150,40,150,getmaxy()-30);
line(420,40,420,getmaxy()-30);
line(530,40,530,getmaxy()-30);
outtextxy(30,55,"SNO");
outtextxy(90,55,"CODE");
outtextxy(210,55,"NAME OF THE PRODUCT");
outtextxy(440,55,"QUANTITY");
outtextxy(540,55,"PRICE/Ps");
}
void add()
{
cleardevice();
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,5);
outtextxy(50,30,"FOOD WORLD");
setcolor(WHITE);
rectangle(200,150,430,320);
settextstyle(GOTHIC_FONT,0,3);
outtextxy(220,190,"enter the details of");
outtextxy(220,230,"the product....");
settextstyle(DEFAULT_FONT,0,1);
outtextxy(180,450,"press any key to continue......");
getch();
cleardevice();
fseek(fp,0,2);
n=ftell(fp);
nor=n/sizeof(rec);
printf("enter number of items");
scanf("%d",&nu);
for(i=nor;i<(nor+nu);i++)
{
printf("enter:\nsno\tcode\tname\tqty\tprice\n");
scanf("%d %d %s %d %d",&s[i].sno,&s[i].code,s[i].name,&s[i].qty,&s[i].price);
fwrite(&s[i],sizeof(s[i]),1,fp);
}
}
void modify()
{
int m;
cleardevice();
printf("enter the code of the productyou want to modify");
scanf("%d",&c);
m=search(c);
if(m==0) printf("the code you have entered is not found");
else
{
printf("enter the modified details");
printf("enter:\nsno\tcode\tname\tqty\tprice\n");
scanf("%d %d %s %d %d",&rec.sno,&rec.code,rec.name,&rec.qty,&rec.price);
size=sizeof(rec);
fseek(fp,-size,1);
fwrite(&rec,sizeof(rec),1,fp);
}
outtextxy(40,470,"press any key to continue...");
getch();
submenu1();
}
int search(int p)
{
int flag=0;
rewind(fp);
fflush(stdin);
while(fread(&rec,sizeof(rec),1,fp)==1)
{
if(rec.code==p)
{
flag=1;
break;
}
}
if(flag==0) return 0;
else return 1;
}
void billing()
{
int sum=0;
cleardevice();
rewind(fp);
printf("enter the codes and quantity of the product and print 0 for exit");
do
{
scanf("%d %d",&c,&qt);
rewind(fp);
while(fread(&rec,sizeof(rec),1,fp)==1)
{
if(rec.code==c)
sum=sum+(qt*rec.price);
}
}while(c!=0);
printf("bill amount is %d",sum);
getch();
}
void admin()
{
admini();
setcolor(WHITE);
outtextxy(100,430,"press any key to continue...");
getch();
}
void admini()
{
cleardevice();
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,4);
outtextxy(60,20,"> > >  ADMINISTRATION  < < <");
setcolor(WHITE);
settextstyle(GOTHIC_FONT,0,3);
outtextxy(60,100,"* Who?");
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,3);
outtextxy(60,130,"Established by Shravya and Swathi");
setcolor(WHITE);
settextstyle(GOTHIC_FONT,0,3);
outtextxy(60,200,"* When?");
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,3);
outtextxy(60,230,"On March 27th,2010");
setcolor(WHITE);
settextstyle(GOTHIC_FONT,0,3);
outtextxy(60,280,"* What?");
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,3);
outtextxy(60,320,"Consists of all household groceries");
outtextxy(60,350,"and enables you with happy-shopping..!!");
}

void branches()
{
cleardevice();
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,4);
outtextxy(100,20,"> > >  BRANCHES  < < <");
setcolor(WHITE);
settextstyle(SMALL_FONT,0,6);
outtextxy(30,80,"----- Has more than 10 branches across the state....");
delay(1000);
outtextxy(200,120,"* Hyderabad"); delay(1000);
outtextxy(200,150,"* Vijayawada"); delay(1000);
 outtextxy(200,180,"* Vizag"); delay(1000);
outtextxy(200,210,"* Guntur"); delay(1000);
 outtextxy(200,240,"* Nalgonda"); delay(1000);
outtextxy(200,270,"* Karimnagar"); delay(1000);
outtextxy(200,300,"* Kurnool"); delay(1000);
 outtextxy(200,330,"* Chittoor"); delay(1000);
 outtextxy(200,360,"* Cuddapah"); delay(1000);
 outtextxy(200,390,"* East Godavari");
 setcolor(RED);
 outtextxy(100,450,"press any key to continue..");
 getch();
}
void contact()
{
cleardevice();
setcolor(RED);
settextstyle(TRIPLEX_FONT,0,3);
outtextxy(10,10,">> For more information please contact . . . . .");
setcolor(WHITE);
settextstyle(GOTHIC_FONT,0,4);
outtextxy(50,120,"-> Shravya : 9704183704");
line(150,140,200,140);
outtextxy(60,170,"email-id : bsrishravya@yahoo.com");
line(60,190,170,190);
outtextxy(50,220,"-> Swathi : 9505136159");
line(100,240,200,240);
outtextxy(60,270,"email-id : pswathi99@yahoo.com");
line(60,290,170,290);
setcolor(RED);
settextstyle(SMALL_FONT,0,7);
outtextxy(50,400,"For any queries visit:");
outtextxy(320,400,"www.foodworld.com");
line(50,420,300,420);
setcolor(WHITE);
settextstyle(DEFAULT_FONT,0,1);
outtextxy(350,470,"press any key to continue.....");
getch();
}
void exitmenu()
{
cleardevice();
setcolor(WHITE);
settextstyle(TRIPLEX_FONT,0,2);
outtextxy(130,170,"THANK YOU. . . . .VISIT AGAIN. . . ! ! !");
setcolor(RED);
settextstyle(SMALL_FONT,0,5);
outtextxy(30,400,"Kindly post your suggestions and comments to :  food.world@gmail.com");
line(400,420,540,420);
setcolor(WHITE);
outtextxy(140,450,"press any key to exit...");
getch();
exit(0);
}


