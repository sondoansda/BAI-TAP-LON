#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<malloc.h>
#include<windows.h>
#define MAX 10
struct Kho {
	char Ten[20];
	char QuocGia[20];
    int Loai;
	int SoLuong;
	int ID;
};
typedef struct Kho K;
void NhapVaccine(K *p,int &n,char file[]){
	FILE *f;
	f=fopen(file,"wb");char yn[2];
	  printf("\nVaccine thu %d : ",n+1);
      printf("\nTen Vaccine : ");fflush(stdin);gets((*(p+n)).Ten) ;
      printf("\nQuocGia : ");fflush(stdin);gets((*(p+n)).QuocGia) ;
      printf("\nLoai (ml): ");scanf("%d",&(*(p+n)).Loai);
	  printf("\nSo Luong : ");scanf("%d",&(*(p+n)).SoLuong);
	  (*(p+n)).ID = n+1;
	  fwrite((p+n),sizeof( K),1,f);
	  n++;
fclose(f);
}
void ThemVac(K arr[],int &n,char file[],char b[],char c[],int d,int e ){
	FILE *f;f=fopen(file,"ab");
    	n++;
         strcpy(arr[n-1].Ten,b);
	     strcpy(arr[n-1].QuocGia,c);
	     arr[n-1].Loai= d;
	     arr[n-1].SoLuong = e;
	     arr[n-1].ID=n;
	     fwrite(&arr[n-1],sizeof(K),1,f);
	     fclose(f);
}
int demVaccine(K arr[],int n,char file[]){
	FILE *f;f=fopen(file,"rb");int s=0;
	for(int i=0;i<n;i++){
		s+=arr[i].SoLuong;
	}
	return s;
}
void them(K arr[],int &n,char file[],int max,K arr1[],int &n1,char file1[]){
	int a=demVaccine(arr,n,file);
	int a1=demVaccine(arr1,n1,file1);
	char b[20],c[20];int d,e;
	  printf("\nLo Vaccine them vao kho : ");
      printf("\nTen Vaccine : ");fflush(stdin);gets(b) ;
      printf("\nQuocGia : ");fflush(stdin);gets(c) ;
      printf("\nLoai (ml): ");scanf("%d",&d);
	  printf("\nSo Luong : ");scanf("%d",&e);
	  int aa;aa =max- a; int t;t=e-aa;
	   if(e>=aa) {
	   	ThemVac(arr,n,file,b,c,d,aa);
	   	ThemVac(arr1,n1,file1,b,c,d,t);
	   }
	   else  ThemVac(arr,n,file,b,c,d,e); 
}
int  ChuyenVaccineDi (K arr[],int &n,char file[],int id,int soluong){
	FILE *f ;f=fopen(file,"ab");int c= 0;
	for(int i=0;i<n;i++){
		if(arr[i].ID==id){
			arr[i].SoLuong -=soluong;
			fwrite(&arr[i],sizeof(K),1,f);
			c++;
	}
	}   
	fclose(f); 
	if(c==0) {
	printf("\nKho %s da het loai Vaccine nay ",file);
	return 0;
	}
	return 1;     
}  
void HienThiVac(K arr[],int n,char file[]){
	FILE *f;
	f=fopen(file,"rb");
	printf("\nVaccine kho %s : \n",file);
	printf("\n%-10s\t%-10s\t%-10s\t%-10s","TenVac","QuocGia","Loai","SoLuong");
	for(int i=0;i<n;i++){
		fread(&arr[i],sizeof(K),1,f);
		printf("\n%-10s\t",arr[i].Ten);
		printf("%-10s\t",arr[i].QuocGia);
		printf("%d\t\t",arr[i].Loai);
		printf("%d\t\t",arr[i].SoLuong);
	}
	fclose(f);
	Sleep(3000);
}
              
void mainQuanLyKho(){
	char file[] ="A";int n=0; K arr[MAX];  K *p;  p=&arr[0];   
	char file1[]="B";int n1=0; K arr1[MAX]; K *p1;  p1=&arr1[0];
	int max =1000;
	FILE*f;f=fopen(file,"rb");
	while((fread(&arr[n],sizeof(K),1,f))==1){
		n++;
	}

	if(n==0){
		printf("\nThong tin Vaccine trong kho A trong !!!\nVui long nhap thong tin ");
			p=(K *)malloc(sizeof(K));
			NhapVaccine(p,n,file);
	}
	fclose(f);
	FILE *f1;f1=fopen(file1,"rb");
	while((fread(&arr1[n],sizeof(K),1,f1))==1){
		n1++;
		}
	if(n1==0){
		printf("\nThong tin Vaccine trong kho B trong !!!\nVui long nhap thong tin ");
			p1=(K *)malloc(sizeof(K));
			NhapVaccine(p1,n1,file1);
	}
	fclose(f1);
	while(1){system("cls");
	printf("\n------------------------------- QUAN LY KHO VACCINE -------------------------------");
	printf("\n1.Hien thi kho Vaccine");
	printf("\n2.Nhap kho Vaccine");
	printf("\n3.Chung chuyen Vaccine");
	printf("\nLua chon cua ban : ");int choose;scanf("%d",&choose);
	switch(choose){
		case 1: system("cls");HienThiVac(arr,n,file);HienThiVac(arr1,n1,file1);break;
		case 2: system("cls");them(arr,n,file,max,arr1,n1,file1);break;
		case 3: system("cls");
		        if(ChuyenVaccineDi(arr,n,file,5,1)) {
				Sleep(2000);break;}
	            else {
	                   	if(ChuyenVaccineDi(arr1,n1,file1,5,1)) break;
		                else {
						printf("\nKhong con loai Vaccine nay !!!");
						Sleep(2000);break;}
		                     }
		case 4:break;
		
	}
}
}



int main (){
 mainQuanLyKho();
	return 0;
}