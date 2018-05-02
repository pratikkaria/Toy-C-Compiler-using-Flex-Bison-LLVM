extern int printf(char const *format, ...);

int ga=10;
int gb=20;
int gc = 0;

void docomplex(){
	int a= 10;
    int b = 20;
   
    int c = a+b;
    int d = a+b;   	

    printf("%d\n", c);
    printf("%d\n", d);

	gc = ga+gb;
}

int main(){

	docomplex();

    int a= 10;
    int b = 20;
    int b2 = 20;

    int c = a+b;
    int d = a+b;   

    printf("%d\n", c);
    printf("%d\n", d);

    int e = a+b*2-8 /c;
    int f = a+b*2-8/c;

    printf("%d\n", e);
    printf("%d\n", f);

    int tmp = ga+gb;

    printf("%d\n", tmp);

   int l = 10;
   if(l<10){
   	int k = a+b;
   	printf("%d\n", k);
   }else{
   	int m = a+b2;
   	printf("%d\n", m);
   }	 

   for(int i=0;i<4;i++){
   	int lt = a+b;
   	printf("%d\n", lt);
   }

    return 0;
}