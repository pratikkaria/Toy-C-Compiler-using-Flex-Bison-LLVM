extern int printf(char const *format, ...);

int main() {

    int s1 = 10;
    int s2 = s1 + 10; // this will directly have 20, we need to use it, else it will not be generated
    printf("%d\n", s2);

    // a code will not be generated
    int a = 10;
    int b = 40;
    printf("%d\n", b);

    // this will not be generated
    while (b <= 10) {
        printf("%d\n", b);
        b++;
    }

    int c = 0;
    // this will be generated
    // and as c is constant, there will be no compare statement
    while (c <= 10) {
        printf("%d\n", c);
        c++;
    }

    // this will not be generated
    int d = 10;
    if (d == 20) {
        printf("%d\n", d);
    }

    // this will be generated with no compare statemetn
    int e = 10;
    if (e == 10) {
        printf("%d\n", e);
    }


    return 0;
}