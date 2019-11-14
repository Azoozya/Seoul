#include "header.h"
int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	test_my_pow();
	test_merge_bits(master);
	test_get_nb_alpha_char(); //A REVOIR !
	test_alpha_filter(master);
	test_char_to_int();
	test_char_to_short();

	delete_down(master);
	return 0;
}

/*-----------------TEST EXO 1-----------------*/
void test_get_nb_alpha_char(void)
{
	int success = 0;
	FILE *Test;
	int Nbr = 300;
	long test;
	char* test_filename = "Get_nb_alpha_char_Test.txt";

	test = get_nb_alpha_char(test_filename);

	if (test != 26) success = 1;

	if (success != 1) printf("get_nb_alpha_char() fonctionnel\n");
	else printf("get_nb_alpha_char() non fonctionnel\n");
}

void test_alpha_filter(mp* master)
{
	FILE* Test;
	char* test_filename = "alpha_filter_test.txt";
	long max_alpha_char = get_nb_alpha_char(test_filename);
	int success = 0;
	char index = 0;
	int character = '\0';
	// printf("get_nb_alpha_char = %ld\n", max_alpha_char);

	char* test_filter = alpha_filter(test_filename, max_alpha_char, master);

	do {
    Test = fopen(test_filename,"r");
	}while(test_succes(Test) != YES);

 	 character = getc(Test);

	 do{
		if (isupper(character) != 0 && *(test_filter+index) == 0) success = 1;
		if (isupper(character) == 0 && *(test_filter+index) != 0) success = 1;
		index++;
		character = getc(Test);
	} while (character != EOF && index < max_alpha_char);

	if (success != 1) printf("alpha_filter() fonctionnel\n");
	else printf("alpha_filter() non fonctionnel\n");

	fclose(Test);
}

void test_merge_bits(mp* master)
{
	char bits[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
	long max = 32;
	int* test_bytes;
	int success = 0;

	test_bytes = merge_bits(bits, max, master);

	for (int index = 0; index < 4; index++)
		if (*(test_bytes+index) != 0xAA) success = 1;

	if (success != 1) printf("merge_bits() fonctionnel\n");
	else printf("merge_bits() non fonctionnel\n");

}


/*-----------------TEST EXO 1-----------------*/



/*-----------------TEST EXO 2-----------------*/


void test_char_to_short(void)
{
	int success = 0;
	unsigned short short_test = 0xF8E3;
	unsigned short test_compare;
	unsigned char lsB = 0xE3;
	unsigned char msB = 0xF8;

	test_compare = char_to_short(msB, lsB);

	if(short_test != test_compare) success = 1;

	if (success != 1) printf("char_to_short() fonctionnel\n");
	else printf("char_to_short() non fonctionnel\n");
}

void test_char_to_int(void)
{
	int success = 0;
	unsigned int int_test = 0xAE84C34A;
	unsigned int test_compare;
	unsigned char first = 0x4A;
	unsigned char second = 0xC3;
	unsigned char third = 0x84;
	unsigned char fourth = 0xAE;

	test_compare = char_to_int(second, first, fourth, third);

	if (int_test != test_compare) success = 1;

	if (success != 1) printf("char_to_int() fonctionnel\n");
	else printf("char_to_int() non fonctionnel\n");
}

// void test_exo_2_2(void)
// {
// 	int success = 0;
//
//
// 	if (success != 1) printf("exo_2_2() fonctionnel\n");
// 	else printf("exo_2_2() non fonctionnel\n");
// }
//
// void test_exo_2_3(void)
// {
// 	int success = 0;
//
//
// 	if (success != 1) printf("exo_2_3() fonctionnel\n");
// 	else printf("exo_2_3() non fonctionnel\n");
// }

/*-----------------TEST EXO 2-----------------*/
