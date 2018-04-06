extern int printf(char const *format, ...);

int main() {

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
    // int d = 0;
    // while (d <= 10) {
    //     printf("%d\n", d);
    //     d++;
    // }

    // // this will not be generated
    // int d = 10;
    // if (d == 20) {
    //     printf("%d\n", d);
    // }

    // // this will be generated with no compare statemetn
    // int e = 10;
    // if (e == 10) {
    //     printf("%d\n", e);
    // }


    return 0;
}