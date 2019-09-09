#include "header.h"
int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	delete_down(master);
	return 0;
}
