#include "header.h"
int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	// test_my_pow();
	// test_merge_bits(master);
	// test_get_nb_alpha_char();
	// test_alpha_filter(master);
	// test_char_to_int();
	// test_char_to_short();
	//
	// test_init_header(master);
	//test_extract_raw_header(master);
	//test_raw_to_fichierEntete(master);
	test_raw_to_imageEntete(master);

	//test_exo_2_3(master);

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
	}while(test_success(Test) != YES);

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

void test_init_header(mp* master)
{
		//De l'Initialisation de fichier bmp, nous devons vérifier les bonnes valeurs sont mises dedans
		int success = 0;
		bitmap* test = init_header(master);

		if(test->size_fichierEntete != 14) success = 1;
		if(test->size_imageEntete != 40) success = 1;
		if(test->size_couleurPallete != 4) success = 1;
		if(test->size_header != 54) success = 1;

		if (success != 1) printf("init_header() fonctionnel\n");
		else printf("init_header() non fonctionnel\n");
}

void test_extract_raw_header(mp* master)
{
		int success = 0;
		FILE* transporteur_hexdump;

	  do {
	    transporteur_hexdump = fopen("hexdump_transporteur_bmp","r");
	  } while(test_success(transporteur_hexdump) != YES);

		bitmap* test_header = init_header(master);
		extract_raw_header(test_header, master);

		char raw_reference[test_header->size_header];

		char save = '\0';
		long cursor = 0;
		int file_counter = 0;

		while (cursor < test_header->size_header)
		{
			if (file_counter <= 7) getc(transporteur_hexdump);
			else
			{
				save = getc(transporteur_hexdump);
				if(isalnum(save) != 0)
				{
					raw_reference[cursor] = save;
					cursor++;
				}
			}
			file_counter++;
			if (file_counter >= 48) file_counter = 0;
		}

		for (long index = 0; index < test_header->size_fichierEntete; index++)
		{
			printf("raw_reference[%ld] = %c | test_header->raw_fichier[%ld] = %c\n",index, raw_reference[index], index, test_header->raw_fichier[index]);
			if (raw_reference[index] != test_header->raw_fichier[index]) success = 1;
		}

		for (long index = 0; index < test_header->size_imageEntete; index++)
		{
			printf("raw_reference[%ld] = %c | test_header->raw_image[%ld] = %c\n",index + test_header->size_fichierEntete, raw_reference[index + test_header->size_fichierEntete], index, test_header->raw_image[index]);
			if (raw_reference[index + test_header->size_fichierEntete] != test_header->raw_image[index]) success = 1;
		}

		if (success != 1) printf("extract_raw_header() fonctionnel\n");
		else printf("extract_raw_header() non fonctionnel\n");
		//NB : 48 caractères par ligne dans hexdump_transporteur_bmp (en comptant \n)!

		fclose(transporteur_hexdump);
}

void test_raw_to_fichierEntete(mp* master)
{
		int success = 0;
		short test_signature;
		int test_tailleFichier;
		int test_reserve;
		int test_offset;

		FILE* transporteur_hexdump;

		do {
			transporteur_hexdump = fopen("hexdump_transporteur_bmp","r");
		} while(test_success(transporteur_hexdump) != YES);

		bitmap* test_header = init_header(master);
		extract_raw_header(test_header, master);
		raw_to_fichierEntete(test_header);

		char raw_reference[test_header->size_fichierEntete];

		char save = '\0';
		long cursor = 0;
		int file_counter = 0;

		while (cursor < test_header->size_fichierEntete)
		{
			if (file_counter <= 7) getc(transporteur_hexdump);
			else
			{
				save = getc(transporteur_hexdump);
				if(isalnum(save) != 0)
				{
					raw_reference[cursor] = save;
					cursor++;
				}
			}
			file_counter++;
			if (file_counter >= 48) file_counter = 0;
		}

		test_signature = char_to_short((unsigned char)raw_reference[1],(unsigned char)raw_reference[0]);
	  test_tailleFichier = char_to_int((unsigned char)raw_reference[5],(unsigned char)raw_reference[4],(unsigned char)raw_reference[3],(unsigned char)raw_reference[2]);
	  test_reserve = char_to_int((unsigned char)raw_reference[9],(unsigned char)raw_reference[8],(unsigned char)raw_reference[7],(unsigned char)raw_reference[6]);
	  test_offset = char_to_int((unsigned char)raw_reference[13],(unsigned char)raw_reference[12],(unsigned char)raw_reference[11],(unsigned char)raw_reference[10]);

		if(test_signature != test_header->fichier->signature) success = 1;
		if(test_tailleFichier != test_header->fichier->tailleFichier) success = 1;
		if(test_reserve != test_header->fichier->reserve) success = 1;
		if(test_offset != test_header->fichier->offset) success = 1;

		printf("On a %x et %x\n",test_signature, test_header->fichier->signature);
		printf("On a %x et %x\n",test_tailleFichier, test_header->fichier->tailleFichier);
		printf("On a %x et %x\n",test_reserve, test_header->fichier->reserve);
		printf("On a %x et %x\n",test_offset, test_header->fichier->offset);

		if (success != 1) printf("raw_to_fichierEntete() fonctionnel\n");
		else printf("raw_to_fichierEntete() non fonctionnel\n");
}

void test_raw_to_imageEntete(mp* master)
{
	int success = 0;
	int test_tailleEntete;
	int test_largeur;
	int test_hauteur;
	short test_plan;
	short test_profondeur;
	int test_compression;
	int test_tailleImage;
	int test_resolutionHorizontale;
	int test_resolutionVerticale;
	int test_nombreCouleurs;
	int test_nombreCouleursImportantes;

	FILE* transporteur_hexdump;

	do {
		transporteur_hexdump = fopen("hexdump_transporteur_bmp","r");
	} while(test_success(transporteur_hexdump) != YES);

	bitmap* test_header = init_header(master);
	extract_raw_header(test_header, master);
	raw_to_imageEntete(test_header);

	char raw_reference[test_header->size_imageEntete];

	char save = '\0';
	long cursor = 0;
	int file_counter = 0;

	while(cursor < test_header->size_fichierEntete)
	{
		if (file_counter <= 7) getc(transporteur_hexdump);
		else
		{
			save = getc(transporteur_hexdump);
			if(isalnum(save) != 0) cursor++;
		}
		file_counter++;
		if (file_counter >= 48) file_counter = 0;
	}

	save = '\0';
	cursor = 0;

	while (cursor < test_header->size_imageEntete)
	{
		if (file_counter <= 7) getc(transporteur_hexdump);
		else
		{
			save = getc(transporteur_hexdump);
			if(isalnum(save) != 0)
			{
				raw_reference[cursor] = save;
				cursor++;
			}
		}
		file_counter++;
		if (file_counter >= 48) file_counter = 0;
	}

	test_tailleEntete = char_to_int((unsigned char)raw_reference[3],(unsigned char)raw_reference[2],(unsigned char)raw_reference[1],(unsigned char)raw_reference[0]);
  test_largeur = char_to_int((unsigned char)raw_reference[7],(unsigned char)raw_reference[6],(unsigned char)raw_reference[5],(unsigned char)raw_reference[4]);
  test_hauteur = char_to_int((unsigned char)raw_reference[11],(unsigned char)raw_reference[10],(unsigned char)raw_reference[9],(unsigned char)raw_reference[8]);
  test_plan = char_to_short((unsigned char)raw_reference[13],(unsigned char)raw_reference[12]);
  test_profondeur = char_to_short((unsigned char)raw_reference[15],(unsigned char)raw_reference[14]);
  test_compression = char_to_int((unsigned char)raw_reference[19],(unsigned char)raw_reference[18],(unsigned char)raw_reference[17],(unsigned char)raw_reference[16]);
  test_tailleImage = char_to_int((unsigned char)raw_reference[23],(unsigned char)raw_reference[22],(unsigned char)raw_reference[21],(unsigned char)raw_reference[20]);
  test_resolutionHorizontale = char_to_int((unsigned char)raw_reference[27],(unsigned char)raw_reference[26],(unsigned char)raw_reference[25],(unsigned char)raw_reference[24]);
  test_resolutionVerticale = char_to_int((unsigned char)raw_reference[31],(unsigned char)raw_reference[30],(unsigned char)raw_reference[29],(unsigned char)raw_reference[28]);
  test_nombreCouleurs = char_to_int((unsigned char)raw_reference[35],(unsigned char)raw_reference[34],(unsigned char)raw_reference[33],(unsigned char)raw_reference[32]);
  test_nombreCouleursImportantes = char_to_int((unsigned char)raw_reference[39],(unsigned char)raw_reference[38],(unsigned char)raw_reference[37],(unsigned char)raw_reference[36]);

	if(test_tailleEntete != test_header->image->tailleEntete) success = 1;
	if(test_largeur != test_header->image->largeur) success = 1;
	if(test_hauteur != test_header->image->hauteur) success = 1;
	if(test_plan != test_header->image->plan) success = 1;
	if(test_profondeur != test_header->image->profondeur) success = 1;
	if(test_compression != test_header->image->compression) success = 1;
	if(test_tailleImage != test_header->image->tailleImage) success = 1;
	if(test_resolutionHorizontale != test_header->image->resolutionHorizontale) success = 1;
	if(test_resolutionVerticale != test_header->image->resolutionVerticale) success = 1;
	if(test_nombreCouleurs != test_header->image->nombreCouleurs) success = 1;
	if(test_nombreCouleursImportantes != test_header->image->nombreCouleursImportantes) success = 1;

	printf("On a %x et %x\n",test_tailleEntete, test_header->image->tailleEntete);
	printf("On a %x et %x\n",test_largeur, test_header->image->largeur);
	printf("On a %x et %x\n",test_hauteur, test_header->image->hauteur);
	printf("On a %x et %x\n",test_plan, test_header->image->plan);
	printf("On a %x et %x\n",test_profondeur, test_header->image->profondeur);
	printf("On a %x et %x\n",test_compression, test_header->image->compression);
	printf("On a %x et %x\n",test_tailleImage, test_header->image->tailleImage);
	printf("On a %x et %x\n",test_resolutionHorizontale, test_header->image->resolutionHorizontale);
	printf("On a %x et %x\n",test_resolutionVerticale, test_header->image->resolutionVerticale);
	printf("On a %x et %x\n",test_nombreCouleurs, test_header->image->nombreCouleurs);
	printf("On a %x et %x\n",test_nombreCouleursImportantes, test_header->image->nombreCouleursImportantes);

	if (success != 1) printf("raw_to_fichierEntete() fonctionnel\n");
	else printf("raw_to_fichierEntete() non fonctionnel\n");
}

void test_exo_2_3(mp* master)
{
	int success = 0;
	FILE *Transporteur, *Reproduction;
	char compare_R = '\0';
	char compare_T = '\0';

	bitmap* header = init_header(master);
  extract_raw_header(header,master);
  raw_to_fichierEntete(header);
  raw_to_imageEntete(header);

	exo_2_3(header);

	do{
		Transporteur = fopen("transporteur.bmp","rb");
	} while(test_success(Transporteur) != YES);

	do{
		Reproduction = fopen("Ex2_3.bmp","rb");
	} while(test_success(Reproduction) != YES);

	do{
		compare_T = getc(Transporteur);
		compare_R = getc(Reproduction);
		if(compare_R != compare_T) success = 1;
	} while(compare_R != EOF || compare_T != EOF);

	if (success != 1) printf("exo_2_3() fonctionnel\n");
	else printf("exo_2_3() non fonctionnel\n");
}

/*-----------------TEST EXO 2-----------------*/
