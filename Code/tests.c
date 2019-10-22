#include "header.h"
int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	test_my_pow();

	delete_down(master);
	return 0;
}
