#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<malloc.h>
#include<windows.h>
#include <ctype.h>
#define MAX 10

struct MuiTiem{
 char TenMui[20];
 char QuocGia[20];
 int Loai;
 int kcTiem;
};
 struct QuanLyNguoiDaTiem{
 char Ten[40];
 char CCCD[15];
 char QueQuan[40];
 char SDT[11];
 MuiTiem  a[MAX];
 int id; 
};
typedef struct QuanLyNguoiDaTiem QL;
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void  nhap  (QL *p,int &n,char TenFile[]){
 FILE *f;
 f=fopen(TenFile,"wb");char yn[2];
 for(int i=0;i<n;i++){
  printf("\nNguoi tiem thu %d ",i+1);
  printf("\nTen nguoi tiem : ");fflush(stdin);gets((*(p+i)).Ten);
  printf("CCCD : ");fflush(stdin);gets((*(p+i)).CCCD);
  printf("Que quan : ");fflush(stdin);gets((*(p+i)).QueQuan);
  printf("So dien thoai : ");fflush(stdin);gets((*(p+i)).SDT);
  printf("So mui da tiem : ");int c;scanf("%d",&c);
     (*(p+i)).id= c;
  for(int j = 0;j<c;j++){
   printf("\nThong tim mui %d : ",j+1);
   printf("\nTen mui tiem : ");fflush(stdin);gets((*(p+i)).a[j].TenMui);
   printf("Quoc gia : ");fflush(stdin);gets((*(p+i)).a[j].QuocGia);
   printf("Loai (ml): ");scanf("%d",&(*(p+i)).a[j].Loai);
   printf("Khoang cach tiem (ngay): ");scanf("%d",&(*(p+i)).a[j].kcTiem);
   
  }
  fwrite((p+i),sizeof (QL),1,f );
  }
 fclose(f);

}
void xoakitu(char *s,int vt){  
	int n= strlen (s);
	for(int i=vt;i<n-1;i++){
			s[i]= s[i+1];
		}
		s[n-1]=NULL;
		n--;
	}

void ChuanHoaTen( char s[]){
	int n =strlen(s);
 	for(int i=0;i<n;i++){
 		if((s[i]>64 && s[i]<91) ){ //hoa thanh in thuong
			s[i] +=32;
		}
		else if(s[i]>96 && s[i]<123||s[i]==32){ //in thuong va space giu nguyen
			s[i]-=0;
		}
		else {
			xoakitu(s,i);
			n--;i--;
		}
		if(s[i]==32 && s[i+1]==32){  //xoa 2 space lien nhau
			xoakitu(s,i);
			n--;
			i--;
		}
		if(s[i]==32 && i==0){ //xoa space dau
			xoakitu(s,i);
			i--;
			n--;
		}
		if(s[i]==32 && i==n-1){ //xoa space duoi
			xoakitu(s,i);
			i--;
			n--;
		}
	}
	for(int i=0;i<n;i++){
		if(s[i]==32 && s[i+1] != 32)s[i+1]-=32;
		if(i==0)s[i]-=32;
	}
}
void ChuanHoaSo(char s[]){
	int n =strlen(s);
 	for(int i=0;i<n;i++){
 		if((s[i]>47 && s[i]<58) ){ //hoa thanh in thuong
			s[i] +=0;
		}
		else {
			xoakitu(s,i);
			n--;i--;
		}
}}
void SapXep(QL arr[],int n,char TenFile[]){
	 FILE *f;f=fopen(TenFile,"rb");QL temp;
	 for(int i=0;i<n-1;i++){
	 	for(int j=i+1;j<n;j++){
	 		if(strcmp(arr[i].Ten,arr[j].Ten)>0){
	 			QL temp= arr[i];
	 			arr[i]=arr[j];
	 			arr[j]= temp;
			 }
		 }
	 }
	 fclose(f);
}
void LuuFile( QL arr[],int n,char TenFile[]){
	FILE *f;
	f=fopen(TenFile,"wb");
	for(int i=0;i<n;i++){
		fwrite(&arr[i],sizeof(QL),1,f);
	}
	fclose(f);
}
void Xoa(QL arr[],int &n,char TenFile[]){
	FILE *f;
	f=fopen(TenFile,"ab");
	char xoa[13];printf("\nDien can cuoc cong dan muon xoa : ");fflush(stdin);gets(xoa);
	
	for(int i=0;i<n;i++){
		if((strcmp(arr[i].CCCD,xoa))==0){
			for(int j=i;j<n-1;j++){
				arr[i]= arr[i+1];
			}
		}
		n--;
	}
fclose(f);
	LuuFile(arr,n,TenFile);
}
void CapNhapTT(QL arr[],int n,char TenFile[]){
FILE *f;f=fopen(TenFile,"wb");printf("\nNhap so can cuoc cong dan can sua thong tin : ");
char ten[40];fflush(stdin);gets(ten);
for(int i=0;i<n;i++){
	if( (strcmp(arr[i].CCCD,ten))==0){
		ChuanHoaTen( arr[i].Ten);
		ChuanHoaSo(arr[i].CCCD);
		ChuanHoaTen(arr[i].QueQuan);
		ChuanHoaSo(arr[i].SDT);
		 int c;
		c= arr[i].id + 1;
        printf("\nThong tim mui %d : ",c);
        printf("\nTen mui tiem : ");fflush(stdin);gets(arr[i].a[c-1].TenMui);
        printf("\nQuoc gia : ");fflush(stdin);gets(arr[i].a[c-1].QuocGia);
        do{
       	printf("\nLoai (ml)): ");scanf("%d",&arr[i].a[c-1].Loai);
        }while(arr[i].a[c-1].Loai<100);
        do{
        printf("\nKhoang cach tiem (ngay): ");scanf("%d",&arr[i].a[c-1].kcTiem);
		}while(arr[i].a[c-1].kcTiem<30);
		} 
		arr[i].id++;	
		fread(&arr[i],sizeof(QL),1,f);
}

	fclose(f);

}
void ThemVao( QL arr[],int &n,char TenFile[]){
	system("cls");
	FILE *f;
	f=fopen(TenFile,"ab");
     	n++;
     	 gotoXY(25,2);printf("Ten nguoi tiem thu %d : ",n);fflush(stdin);gets(arr[n-1].Ten);
		 gotoXY(25,3);printf("CCCD : ");fflush(stdin);gets(arr[n-1].CCCD);ChuanHoaSo(arr[n-1].CCCD);
         gotoXY(25,4);printf("Que quan : ");fflush(stdin);gets(arr[n-1].QueQuan);
         gotoXY(25,5);printf("So dien thoai : ");fflush(stdin);gets(arr[n-1].SDT);
		int c;
		 gotoXY(25,6);printf("So mui da tiem : ");scanf("%d",&c);
		arr[n-1].id= c;
        for(int j = 0;j<c;j++){
         gotoXY(25,8);printf("Thong tim mui %d : ",j+1);
         gotoXY(25,9);printf("Ten mui tiem : ");fflush(stdin);gets(arr[n-1].a[j].TenMui);
         gotoXY(25,10);printf("Quoc gia : ");fflush(stdin);gets(arr[n-1].a[j].QuocGia);
       do{
       	 gotoXY(25,11);printf("Loai : ");scanf("%d",&arr[n-1].a[j].Loai);
       }while(arr[n-1].a[j].Loai<100);
        do{
         gotoXY(25,12);printf("Khoang cach tiem : ");scanf("%d",&arr[n-1].a[j].kcTiem);
		}while(arr[n-1].a[j].kcTiem<30);
		system("cls");
		}
		fwrite(&arr[n-1],sizeof(QL),1,f);
		fclose(f);
	SapXep(arr,n,TenFile);
}
void KiemTraFile(QL arr[],int &n,char TenFile[]){
	FILE *f;f=fopen(TenFile,"ab");
	for(int i=0;i<n;i++){
		if((strlen(arr[i].CCCD))!=12){
			printf("\nThem khong thanh cong ko thanh cong do ban nhap sai CCCD ");
			for(int j=i;j<n-1;j++){
				arr[i]=arr[i+1];
			}
			n--;
		}
	}
		for(int i=0;i<n;i++){
		if((strlen(arr[i].SDT))!=10){
			printf("\nThem khong thanh cong ko thanh cong do ban nhap sai SDT ");
			for(int j=i;j<n-1;j++){
				arr[i]=arr[i+1];
			}
			n--;
		}

	}
	fclose(f);
	LuuFile(arr,n,TenFile);
	SapXep(arr,n,TenFile);
}
void HienThi (QL arr[],int n,char TenFile[]){ 
FILE *f;int t_pause= 3000;
f=fopen(TenFile,"rb");
 printf("\n%s\t%-10s\t%-15s\t\t%-10s\t%-10s\t%-10s\t%-10s%-10s","TenNguoiTiem ","CCCD","QueQuan","SoDienThoai","TenMuiTiem","QuocGia","Loai","Khoang Cach Tiem");
 for(int i=0;i<n;i++){
  fread(&arr[i],sizeof( QL),1,f);
  ChuanHoaTen(arr[i].Ten);
  printf("\n%s\t",arr[i].Ten);ChuanHoaSo(arr[i].CCCD);
  printf("%-10s\t",arr[i].CCCD);ChuanHoaTen(arr[i].QueQuan);
  printf("%-15s",arr[i].QueQuan);ChuanHoaSo(arr[i].SDT);
  printf("\t%-10s\t",arr[i].SDT);int c = arr[i].id;
  for(int j= 0;j<c;j++){
  	ChuanHoaTen(arr[i].a[j].TenMui);
  printf("%-10s\t",arr[i].a[j].TenMui);ChuanHoaTen(arr[i].a[j].QuocGia);
  printf("%-10s\t",arr[i].a[j].QuocGia);
  printf("%dml\t",arr[i].a[j].Loai);
if( i != (c-1))printf("  %d ngay\n\t\t\t\t\t\t\t\t\t",arr[i].a[j].kcTiem);
else printf("  %d ngay\n\t\t\t\t\t\t\t\t\t",arr[i].a[j].kcTiem);
      }
}
fclose(f);
SapXep(arr,n,TenFile);
Sleep(t_pause);
}
void MenuQuanLyNguoi(){
	 int n=0 ;
  QL *p;QL arr[MAX]; char TenFile[]="QuanLy"; p=&arr[0];
  FILE *f;f=fopen(TenFile,"rb");
while( (fread(&arr[n],sizeof(QL),1,f))==1){
	n++;
}
if(n==0){
//  	printf("\nFILE trong !!! Vui long nhap thong tin : ");
  	p=(QL *) malloc (n * sizeof(QL));
  	nhap(arr,n,TenFile);
  } 
  fclose(f);                   
 while(1){  
 system("cls");
  gotoXY( 25,1); printf("---------------------------------- CHUONG TRINH QUAN LY NGUOI TIEM ----------------------------------");
  gotoXY( 25,4); printf("1.Hien thi thong tin nguoi tiem ");
  gotoXY( 25,5); printf("2.Them nguoi tiem ");
  gotoXY( 25,6); printf("3.Cap nhap TT nguoi tiem");
  gotoXY( 25,7); printf("4.Xoa nguoi tiem khoi danh sach");
  gotoXY(25,8);printf("5.Thoat");int b;
 do{
 	gotoXY(25,10);printf("Lua chon cua ban : ");scanf("%d",&b);
 }while(b<1 && b>5);
 switch (b){                        
 	case 1: system("cls") ; HienThi(arr,n,TenFile) ;break;
    case 2: system("cls");ThemVao(arr,n,TenFile);KiemTraFile(arr,n,TenFile); break;
    case 3: system("cls");CapNhapTT(arr,n,TenFile);break;
    case 4 : system("cls");Xoa(arr,n,TenFile);break;
    case 5 : goto Thoat;break;
 }                                                                      
 }  
  Thoat: system("cls");   
}
int main(){
MenuQuanLyNguoi();                                                                      
 return 0; 
}