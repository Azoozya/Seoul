#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int test_in(char* table,char input);

int main(int argc,char* argv[])
{
  FILE* In;
  int counter = 0;
  char* voyelles = "aeiouyAEIOUY";
  In = fopen(argv[1],"r");
  char buffer;
  do {
    buffer = getc(In);
    counter += test_in(voyelles,buffer);
    printf("Counter = %d\n",counter);
  } while(EOF != buffer);
  return 0;
}

int test_in(char* table,char input)
{
  int output = 0;
  for (int rank = 0 ; rank < 12 ; rank++)
    {
      if (input == table[rank])
        output++;
    }
  return output;
}
