// working code
extern int printf(char const *format, ...);

int ga=10;
int gb=20;
int gc=0;

int addt(int a, int b){
    return a+b;
}

int add(){
    int la = 10;
    int lb = 20;
    int lc = la+lb;
    int ld = la+lb;    
	gc = ga+gb;
	return gc;
}


int main(){

    int la = 10;
    int lb = 20;
    int lc = la+lb;
    int ld = la+lb;

    printf("%d\n", lc);
    printf("%d\n", ld);

    la = 30;
    int le = la+lb;
	printf("%d\n", le);    

    int sum = addt(la, lb);
    printf("%d\n", sum);

    add();
    int tmp = ga+gb;
    printf("%d\n",tmp );
    ga=10;
    int tmp2 = ga+gb;
    printf("%d\n",tmp2 );

    
    return 0;
}