# include <stdio.h>
int gcd(int a, int b, int c) {
    if (a%c==0&&b%c==0) {
        return c;
    }
    else {
        gcd (a,b,--c);
    }
}
void main () {
    int a,b,c,d;
    printf("Enter two integers :");
    scanf("%d %d", &a, &b);
    c = (a>b)? b:a;
    d = gcd(a,b,c);
    printf("The GCD of %d and %d is %d.",a,b,d);
}