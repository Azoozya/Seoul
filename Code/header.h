#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define ERROR 63336
#define NONE 36663
#define YES 333
#define NO 4444
#define MAX_TRY 100

#define LSB 1
#define SSB 2
#define TSB 4
#define FSB 8
#define FFSB 16
#define SSSB 32
#define SSSSSB 64
#define MSB 128

/* master_pointer */
typedef struct mp mp;
struct mp
{
  void* pointer;
  mp* previous;
  mp* next;
};

/* fonctions */
typedef struct REPLACE_ME REPLACE_ME;
struct REPLACE_ME
{
    REPLACE_ME* previous;
    REPLACE_ME* next;
};

/* bitmap.h */
typedef struct __attribute__((__packed__)) {
	unsigned short signature;
	unsigned int tailleFichier;
	unsigned int reserve;
	unsigned int offset;
} fichierEntete;

typedef struct __attribute__((__packed__)) {
	unsigned int tailleEntete;
	unsigned int largeur;
	unsigned int hauteur;
	unsigned short plan;
	unsigned short profondeur;
	unsigned int compression;
	unsigned int tailleImage;
	unsigned int resolutionHorizontale;
	unsigned int resolutionVerticale;
	unsigned int nombreCouleurs;
	unsigned int nombreCouleursImportantes;
} imageEntete;

typedef struct couleurPallete couleurPallete;
struct couleurPallete
{
	unsigned char B;
	unsigned char V;
	unsigned char R;
	unsigned char reserve;

};

typedef struct __attribute__((__packed__)) {
  fichierEntete* fichier;
  char* raw_fichier;
  long size_fichierEntete;

  imageEntete* image;
  char* raw_image;
  long size_imageEntete;

  long size_couleurPallete;
  long size_header;
} bitmap;

/* master_pointer */
mp* create_master_pointer(void);
int add_pointer_master(void* pointer,mp* master);
mp* reach_last_cell(mp* head);
void delete_down(mp* head);

/* fonctions */
void delete_up_and_down(REPLACE_ME* cell);
int test_succes(void* name);

void exo_1(mp* master);
long get_nb_alpha_char(char* filename);
char* alpha_filter(char* filename,long max_alpha_char,mp* master);
int* merge_bits(char* bits,long max_alpha_char,mp* master);

void exo_2(mp* master);

void exo_2_1(bitmap* header);
bitmap* init_header(mp* master);
void extract_raw_header(bitmap* header,mp* master);
unsigned short char_to_short(unsigned char msB,unsigned char lsB);
unsigned int char_to_int(unsigned char second,unsigned char lsB,unsigned char msB,unsigned char third);
void raw_to_fichierEntete(bitmap* header);
void raw_to_imageEntete(bitmap* header);
void show_struct(bitmap* header);

void exo_2_2(bitmap* header);

void exo_2_3(bitmap* header);
/* main (devrait être vide) */

/* test */
