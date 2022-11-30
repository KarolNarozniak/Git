#include<graphics.h>
#include<math.h>
#include<iostream>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
using namespace std;

const int a=800,b=800,bok_bloku=50,v=10,r=4;

void blok(int x,int y,int a)
{
	line(x-a/2,y-a/2,x+a/2,y-a/2);	//dó³ kwadratu
	line(x+a/2,y-a/2,x+a/2,y+a/2);	//prawy bok
	line(x+a/2,y+a/2,x-a/2,y+a/2);	//góra
	line(x-a/2,y+a/2,x-a/2,y-a/2);	//lewy blok
}


main(){
	int n,xc=a/2,yc=b/2,licz=0;
	double o,vx,vy;
	time_t begin, end;
	cout<<"ILE BLOKOW: ";
	cin>>n;
	
	initwindow(a,b);
	int **T = new int * [n];
	for (int i = 0; i<n; i++)
		T[i] = new int [2];
	for (int i=0;i<n;i++){
		T[i][0]=0;
		T[i][1]=0;
	}
	for(int i=0;i<n;i++){
		T[i][0]=rand()%a;
		T[i][1]=rand()%b;
		if(T[i][0]<0) {
			T[i][0]=0+r;
		}
		if(T[i][0]>a){
		 T[i][0]=a-r;
		 setfillstyle(SOLID_FILL,YELLOW);
		}
		if(T[i][1]<0){
		 T[i][1]=0+r;
		 setfillstyle(SOLID_FILL,GREEN);
		 }
		if(T[i][1]>b) {
		T[i][1]=b-r;
		setfillstyle(SOLID_FILL,WHITE);
		}		
	}
	for(int i=0;i<n;i++){
		if(i>1){
			int j=0;
			do	{
					T[i][0]=rand()%a;
					T[i][1]=rand()%b;
					j++;
				}while((sqrt(((T[i][0]-T[j][0])*(T[i][0]-T[j][0]))+((T[i][1]-T[j][1])*(T[i][1]-T[j][1])))<bok_bloku));
		}
		blok(T[i][0],T[i][1],bok_bloku);	
	}
	
	cout<<"KAT PUSZCZENIA PILKI: "<<endl;
	cin>>o;
	clock_t start = clock();
	vx=v*(cos(o*3.14/180));
	bool czy=true;
	while (true){
		delay(16);
		cleardevice();
		circle(xc,yc,r);
		setfillstyle(SOLID_FILL,BLUE);
		floodfill(xc,yc,WHITE);
		xc+=vx;
		vy=-v*(sin(o*3.14/180));
		yc-=vy;
		for(int i=0;i<n;i++){
			blok(T[i][0],T[i][1],bok_bloku);
		}
		if((xc<=0+r)||(xc>=a-r))
		{
		  vx*=-1;
		}
		if((yc<=0+r)||(yc>=b-r)) o=180-2*o;
		
		for(int i=0;i<n;i++){
			if((xc<=T[i][0]+bok_bloku/2+r)&&(xc>=T[i][0]-bok_bloku/2-r)&&(yc<=T[i][1]+bok_bloku/2+r)&&(yc>=T[i][1]-bok_bloku/2-r)){
				if(abs(T[i][0]-xc)>=abs(T[i][1]-yc))	vx*=-1;
				o=180-2*o;
				licz++;
			}
		}
		clock_t end = clock();
		if(double(end - start)/CLOCKS_PER_SEC>=30+licz){
			cleardevice();
			settextstyle(2,0,10);
			setcolor(RED);
			outtextxy(a/4,b/2,"GAME OVER");
			delay(1000);
			cout<<"ILOSC ODBIC: "<<licz<<endl;	
			getch();
			for (int i = 0; i<n; i++)	delete [] T[i];
			closegraph();
			czy=0;
		} 
	}
	
}
