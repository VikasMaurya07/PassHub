#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// to calculate number of digits
int numdig(int n) {
  int count = 0; 
  while (n > 0) {
    count++; 
    n = n / 10; 
  }
  return count; 
}
// gcd calc
int gcd(int a, int b) {
  if (a == 0) return b;
  if (b == 0) return a;
  return gcd(b, a % b);
}
// To generate public key
int pub(int phi, int n, int i) {
    if (i >= phi || numdig(i) != 2) {
        return -1;
    }
    else if (gcd(i,n)==1) { 
        return i; 
    }
    else {
        return pub(phi,n,++i);
    }
}
// calculating power
int cow(int a, int b) {
  if(b==0) {
    return 1;
  }
  return a*cow(a,b-1);
}
// for modular power 
int mod(int a, int b, int c) {
  int f = cow(a,b)%c;
  return f;
}
// generating private key
int priv(int a, int phi, int i) {
    while(numdig(i)>=2) {
        if (a*i%phi==1) {
            return i;
        }
        else {
            return priv(a,phi,++i);
        }
    }
}
void main() {
   int p1 = 10007;
   int p2 = 99991;
   int n = p1*p2;
   int phi = (p1-1)*(p2-1);
   int a = pub(phi,n,20);
   int d = priv(a,phi,10);
   printf("\n%d %d\n",a,d);
  // getting the message to encrypt from the user
  char msg[100];
  printf("Enter the message to encrypt: ");
  fgets(msg, 100, stdin);
  //to encrypt the message
  int encmsg[100];
  for (int i = 0; i < strlen(msg); i++) {
    int mul = mod(msg[i], a, n);
    encmsg[i] = mul;
  }
  for(int i= 0;i<strlen(msg);i++){
    printf("%d ",encmsg[i]);
  }
}