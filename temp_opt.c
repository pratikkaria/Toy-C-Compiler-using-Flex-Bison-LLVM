extern int printf(char const *format, ...);

int add(int a, int b){
	return a+b;
}

int main(){

    int la = 10;
    int lb = 20;
    int lc = la+lb*2;
    int ld = la+lb*2;

    int sum = add(la, lb);
    printf("%d\n", sum);
    printf("%d\n", lc);
    printf("%d\n", ld);


    
    return 0;
}