#include "header.h"

int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	//             EXEMPLE
	// char* CHANGE_ME;
	// do{
	// 	CHANGE_ME = malloc(sizeof(char));
	// 	if (test_success(CHANGE_ME) == YES)
	// 		add_pointer_master((void*)CHANGE_ME ,master);
	// 	 }while(test_success(CHANGE_ME) != YES);

	//Output : Fichier Ex1.txt
	exo_1(master);
	//Output : Fichier Ex2_1.txt
	exo_2(master);


	delete_down(master);
	return 0;
}
