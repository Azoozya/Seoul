#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  FILE *In,*Out;
  In = fopen("transporteur.bmp","rb");
  Out = fopen("test.bmp","wb");
  int c;
  do {
    c = getc(In);
    fprintf(Out,"%c",c);
  } while(c != EOF);
  return 0;
}
