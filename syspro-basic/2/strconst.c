#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char a[] = "Hello";
  char *b = "Hello";

  printf("a=%s, &a=%p\n",a,&a);
  printf("b=%s, &b=%p, b=%p\n",b,&b,b);
  return 0;
}
