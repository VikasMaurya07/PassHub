#include <stdio.h>
long long int cow(int a, int b) {
  if(b==0) {
    return 1;
  }
  return a*cow(a,b-1);
}
int mod(int a, int b, long long int c) {
  int f = cow(a,b)%c;
  return f;
}
void main () {
  printf("%d",mod(63,51,255));
  printf("%d",cow(35,35));
}