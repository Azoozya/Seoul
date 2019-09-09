#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned short lama = -1;
	unsigned int dromadaire = -1;
	unsigned char vigogne = -1;
	printf("[Short] %d:%u\n",sizeof(short),lama);
	printf("[Int] %d:%u\n",sizeof(int),dromadaire);
	printf("[Char] %d:%d\n",sizeof(char),vigogne);	
return 0;
}
