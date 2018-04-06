extern int printf(char const *format, ...);
// this will not be genrated as no call to this
void demo() {

}

// this will be generated
int add(int m, int n) {
//    demo();
    return m+n;
}


int main() {

	int ma=0;	// this will be removed
	int mb = 12*ma; // this will directly have 0 stored to it
	printf("%d\n", mb);

    int sa = 12;
    int sb = sa + 11; // this will directly have 20, we need to use it, else it will not be generated
    printf("%d\n", sb);

    // // a code will not be generated
    int a = 10;
    int b = a + 40;
    printf("%d\n", b);

    // // this will not be generated as the condition is false
    while (b <= 10) {
        printf("%d\n", b);
    }

    
    // // this will be generated
    int d = 0;
    while (d <= 10) {
        printf("%d\n", d);
        d++;
    }

    // this will not be generated
    int e = 10;
    if (e == 20) {
        printf("%d\n", e);
    }

    // this will be generated with no compare statemetn
    int f = 10;
    if (f == 10) {
        printf("%d\n", f);
    }

    add(10,20);

    return 0;
}