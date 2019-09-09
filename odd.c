#include <stdio.h>
#include <stdlib.h>
#define MAX 100


int main(int argc , char* argv[])
{
  FILE* Out;
  int counter = 0;
  int n = 0;
  Out = fopen("nombres_impaires.txt","w");
    if (Out == NULL)
      perror("Ouverture impossible\n");
    else
      {
        while(counter < MAX)
          {
            if ( n%2 == 1)
              {
                fprintf(Out,"%d\t",n);
                counter++;
              }
            n++;
          }
      }
  fclose(Out);
  return 0;
}
