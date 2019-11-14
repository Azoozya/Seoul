#include "header.h"

void delete_up_and_down(REPLACE_ME* cell)
//Libère chacune des cellules d'une liste chaînée de n'importe quel cellule , voir modèle de structure REPLACE_ME
{
  //Vérifie si on a un pointeur valable
  if (cell != NULL)
    {
      //Le cas ou la liste ne contient qu'une seule cellule
      if( cell->previous == NULL && cell->next == NULL)
        {
          free(cell);
        }
      else
        {
            REPLACE_ME* down = cell->next;
            REPLACE_ME* up = cell->previous;
            REPLACE_ME* buffer = NULL;
            free(cell);
            //Tant qu'il reste une cellule dans la liste
            while (down != NULL || up != NULL)
              {
                //Il y'a une cellule en haut ET en bas
                if( down != NULL && up != NULL)
                  {
                    buffer = down->next;
                    free(down);
                    down = buffer;

                    buffer = up->previous;
                    free(up);
                    up = buffer;
                  }
                //Il y'a une cellule en haut seulement
                if( down == NULL && up != NULL)
                  {
                    buffer = up->previous;
                    free(up);
                    up = buffer;
                  }
                //Il y'a une cellule en bas seulement
                if( down != NULL && up == NULL)
                  {
                    buffer = down->next;
                    free(down);
                    down = buffer;
                  }
              }
        }
    }
  else
    printf("delete_up_and_down : Pointeur invalide\n");
}

int test_succes(void* name)
//Vérifie si l'allocation a réussi
{
  if (name == NULL)
    return NO;
  else
    return YES;
}

int my_pow(int x , int alpha)
// Fonction calculant x puissance alpha
{
  int tmp = x;
  if(alpha == 0)
      return 1;
  else if(alpha == 1)
    return x;
  else
    {
      for(int depth = 1 ; depth < alpha ; depth++)
        x = x*tmp;
      return x;
    }
}


/* -------------Exo 1------------- */
void exo_1(mp* master)
/* Protocole de décodage de l'exercice 1 : Majuscule / Minuscule */
{
  FILE* Out;
  do {
    Out = fopen("Ex1.txt","w");
     }while(test_succes(Out) != YES);

  char* filename = "transporteur.txt";
  long max_alpha_char = get_nb_alpha_char(filename);  //Compte le nombre de caractères dans le fichier
  char* bits = alpha_filter(filename,max_alpha_char,master);  //Traduit les minuscules et majuscules du fichier en bits
  int* bytes = merge_bits(bits,max_alpha_char,master);  //Fusionne les bits pourge en faire des octets

  for(int cursor = 0 ; cursor < max_alpha_char/8 ; cursor++)
    fprintf(Out,"%c", bytes[cursor]); //Ecrit le message décodé à l'aide des octets récuperés plus haut.

  fclose(Out);
}

long get_nb_alpha_char(char* filename)
/* Fonction retournant le nombre de caractères alpha-numérique
présent dans le fichier dont le nom est passé en argument */
{
  FILE *In;
  long to_return = 0;
  int character = '\0';
  In = fopen(filename,"r");

  do {
    character = getc(In);
    if (isalpha(character) == 0)
      {
        to_return++;
      }
     to_return++;
     }while(character != EOF);

  fclose(In);
  return to_return;
}

char* alpha_filter(char* filename,long max_alpha_char,mp* master)
/* Cette fonction remplit un tableau contenant les valeurs 0 et 1 en fonction de l'état des caractères lus :
  Si c'est une majuscule, la valeur 1 sera mise dans le tableau. Si c'est une minuscule, ce sera la valeur 0. */
{
  FILE* In;
  char* to_return;
  int character;
  long counter = 0;
  do {
      to_return = malloc(max_alpha_char*sizeof(char));
     }while(test_succes(to_return) != YES);
  add_pointer_master((void*)to_return ,master);

  In = fopen(filename,"r");

  do {
    character = getc(In);
    if(isalpha(character) != 0)
      {
        if(isupper(character) != 0)
            to_return[counter] = 1;
        else
            to_return[counter] = 0;
        counter++;
      }
     }while(character != EOF);
  fclose(In);
  return to_return;
}

int* merge_bits(char* bits,long max_alpha_char,mp* master)
/* Cette fonction fusionne les bits (présent dans un tableau contenant des 0 et des 1)
  en octets (valeur allant de 0 à 255) et les mets dans un tableau. */
{
  int buffer;
  long cursor = 0;
  int* to_return;
   do{
    to_return = malloc((max_alpha_char/8)*sizeof(int));
    if (test_succes(to_return) == YES)
      add_pointer_master((void*)to_return ,master);
     }while(test_succes(to_return) != YES);

  for(int rank = 0 ; rank < max_alpha_char/8 ; rank++)
    {
      buffer = 0;
      //POWER
      for(int power = 7 ; power >= 0 ; power--)
        {
          buffer += bits[cursor]*my_pow(2,power);
          cursor++;
        }
      to_return[rank] = buffer;
    }
  return to_return;
}

/* -------------Exo 1------------- */


/* -------------Exo 2------------- */
void exo_2(mp* master)
{
  bitmap* header = init_header(master);
  extract_raw_header(header,master);
  raw_to_fichierEntete(header);
  raw_to_imageEntete(header);
  
  exo_2_1(header);
  exo_2_2(header);
  exo_2_3(header);
}

void exo_2_1(bitmap* header)
{
  show_struct(header);
}

bitmap* init_header(mp* master)
/*Initialisation de la structure "header", strucutre permettant de gérer les données des fichiers d'images*/
{
  char size_char = sizeof(char);
  char size_short = sizeof(short);
  char size_int = sizeof(int);

  bitmap* to_return;
  do{
    to_return = malloc(sizeof(bitmap));
    if (test_succes(to_return) == YES)
      add_pointer_master((void*)to_return ,master);
    }while(test_succes(to_return) != YES);

  fichierEntete* fichier;
  do{
  	fichier = malloc(sizeof(fichierEntete));
  	if (test_succes(fichier) == YES)
  		add_pointer_master((void*)fichier ,master);
    }while(test_succes(fichier) != YES);

  imageEntete* image;
  do{
    image = malloc(sizeof(imageEntete));
    if (test_succes(image) == YES)
      add_pointer_master((void*)image ,master);
    }while(test_succes(image) != YES);

  to_return->fichier = fichier;
  to_return->size_fichierEntete = (3*size_int+size_short);
  to_return->image = image;
  to_return->size_imageEntete = (9*size_int+2*size_short);
  to_return->size_couleurPallete = (4*size_char);
  to_return->size_header = to_return->size_imageEntete+to_return->size_fichierEntete;

  char* raw_fichier;
  do{
  	raw_fichier = malloc(to_return->size_fichierEntete*sizeof(char));
  	if (test_succes(raw_fichier) == YES)
  		add_pointer_master((void*)raw_fichier ,master);
    }while(test_succes(raw_fichier) != YES);

  char* raw_image;
  do{
  	raw_image = malloc(to_return->size_imageEntete*sizeof(char));
  	if (test_succes(raw_image) == YES)
  		add_pointer_master((void*)raw_image ,master);
    }while(test_succes(raw_image) != YES);

  to_return->raw_fichier = raw_fichier;
  to_return->raw_image = raw_image;

  return to_return;
}

void extract_raw_header(bitmap* header,mp* master)
/*Extrait les données de l'en-tête du fichier "transporteur.bmp" et les sépare
  (entre données du fichier en général et données de l'image) */
{
  FILE* In;
  do {
    In = fopen("transporteur.bmp","rb");
  } while(test_succes(In) != YES);

  char* raw;
  do{
  	raw = malloc((header->size_header)*sizeof(char));
  	if (test_succes(raw) == YES)
  		add_pointer_master((void*)raw ,master);
    }while(test_succes(raw) != YES);

  char buffer = '\0';
  for(int cursor = 0 ; cursor < header->size_header ; cursor++)
    {
      buffer = getc(In);
      raw[cursor] = buffer;
    }

  for(int cursor = 0 ; cursor < header->size_fichierEntete ; cursor++)
    {
      buffer = raw[cursor];
      header->raw_fichier[cursor] = buffer;
    }
  for(int cursor = header->size_fichierEntete ; cursor < header->size_fichierEntete+header->size_imageEntete ; cursor++)
    {
      buffer = raw[cursor];
      header->raw_image[cursor-header->size_fichierEntete] = buffer;
    }

  fclose(In);
}

unsigned short char_to_short(unsigned char msB,unsigned char lsB)
/*Fonction convertissant des valeurs char en valeurs short*/
{
  unsigned short to_return = 0;
  to_return = lsB+256*msB;
  return to_return;
}

unsigned int char_to_int(unsigned char second,unsigned char lsB,unsigned char msB,unsigned char third)
/* Fonction convertissant des veleurs char en valeurs int */
{
    int to_return = 0;
    to_return += msB;

    to_return *= 256;
    to_return += third;

    to_return *= 256;
    to_return += second;

    to_return *= 256;
    to_return += lsB;

    return to_return;
}

void raw_to_fichierEntete(bitmap* header)
/*Classe les données de l'en-tête du fichier dans la structure fichierEntete*/
{
  char* raw = header->raw_fichier;
  header->fichier->signature = char_to_short((unsigned char)raw[1],(unsigned char)raw[0]);
  header->fichier->tailleFichier = char_to_int((unsigned char)raw[5],(unsigned char)raw[4],(unsigned char)raw[3],(unsigned char)raw[2]);
  header->fichier->reserve = char_to_int((unsigned char)raw[9],(unsigned char)raw[8],(unsigned char)raw[7],(unsigned char)raw[6]);
  header->fichier->offset = char_to_int((unsigned char)raw[13],(unsigned char)raw[12],(unsigned char)raw[11],(unsigned char)raw[10]);
}

void raw_to_imageEntete(bitmap* header)
/*Classe les données de l'en-tête de l'image dans la structure imageEntete*/
{
  char* raw = header->raw_image;
  header->image->tailleEntete = char_to_int((unsigned char)raw[3],(unsigned char)raw[2],(unsigned char)raw[1],(unsigned char)raw[0]);
  header->image->largeur = char_to_int((unsigned char)raw[7],(unsigned char)raw[6],(unsigned char)raw[5],(unsigned char)raw[4]);
  header->image->hauteur = char_to_int((unsigned char)raw[11],(unsigned char)raw[10],(unsigned char)raw[9],(unsigned char)raw[8]);
  header->image->plan = char_to_short((unsigned char)raw[13],(unsigned char)raw[12]);
  header->image->profondeur = char_to_short((unsigned char)raw[15],(unsigned char)raw[14]);
  header->image->compression = char_to_int((unsigned char)raw[19],(unsigned char)raw[18],(unsigned char)raw[17],(unsigned char)raw[16]);
  header->image->tailleImage = char_to_int((unsigned char)raw[23],(unsigned char)raw[22],(unsigned char)raw[21],(unsigned char)raw[20]);
  header->image->resolutionHorizontale = char_to_int((unsigned char)raw[27],(unsigned char)raw[26],(unsigned char)raw[25],(unsigned char)raw[24]);
  header->image->resolutionVerticale = char_to_int((unsigned char)raw[31],(unsigned char)raw[30],(unsigned char)raw[29],(unsigned char)raw[28]);
  header->image->nombreCouleurs = char_to_int((unsigned char)raw[35],(unsigned char)raw[34],(unsigned char)raw[33],(unsigned char)raw[32]);
  header->image->nombreCouleursImportantes = char_to_int((unsigned char)raw[39],(unsigned char)raw[38],(unsigned char)raw[37],(unsigned char)raw[36]);
}

void show_struct(bitmap* header)
/*Ecrit les données de l'en-tête du fichier "transporteur.bmp" dans le fichier Ex2_1.txt*/
{
  FILE* Out;
  do {
    Out = fopen("Ex2_1.txt","w");
  } while(test_succes(Out) != YES);

  fichierEntete* fichier = header->fichier;
  fprintf(Out,"%x\t%x\t%x\t%x\n",fichier->signature,fichier->tailleFichier,fichier->reserve,fichier->offset);
  imageEntete* image = header->image;
  fprintf(Out,"%x\t%x\t%x\t%x\t%x\t%x\t%x\t%x\t%x\t%x\t%x\n",image->tailleEntete,image->largeur,image->hauteur,image->plan,image->profondeur,image->compression,image->tailleImage,image->resolutionHorizontale,image->resolutionVerticale,image->nombreCouleurs,image->nombreCouleursImportantes);
  fclose(Out);
}

void exo_2_2(bitmap* header)
/*Sténographie : Cette fonction prend chaque octet de la fonction (quid de l'en-tête),
  y applique un modulo 2 (bit de poids faible à 0 ou 1) et l'écrit dans le fohoer qu'il faut
  (après l'avoir rassemnler en octet) */
{
  FILE *In,*Out;
  do {
      In = fopen("transporteur.bmp","rb");
      Out = fopen("Ex2_2.jpg","wb");
     }while(test_succes(In) != YES || test_succes(Out) != YES);

  for(int cursor = 0 ; cursor < header->size_header ; cursor++)
      {
        getc(In);
      }
  unsigned int character = '\0';
  int power = 7;
  unsigned int buffer = 0;
  do {
      character = getc(In);
      if(character%2 == 1)
        buffer += my_pow(2,power);
      power--;
      if(power == -1)
        {
          power = 7;
          fprintf(Out,"%c",buffer);
          buffer = 0;
        }
      }while(character != EOF);
  fclose(In);
  fclose(Out);
}

void exo_2_3(bitmap* header)
/*Recréation du fichier transporteur à partir de l'image originel et de l'image de l'homme démasqué*/
{
  FILE *Source,*Transporteur,*Out;
  do{
      Source = fopen("Ex2_2.jpg","rb");
      Transporteur = fopen("originel.bmp","rb");
      Out = fopen("Ex2_3.bmp","wb");
      // printf("%p::%p:%p\n",Source,Transporteur,Out);
    }while(test_succes(Transporteur) != YES || test_succes(Source) != YES || test_succes(Out) != YES);

  int character_source = '\0';
  int character_transporteur = '\0';
  int bits[8] = {0};

  for(int cursor = 0 ; cursor < header->size_header ; cursor++)
  //Recopie de l'en-tête dans le fichier en sortie
    {
        fprintf(Out,"%c",getc(Transporteur));
    }

  do {
    character_source = getc(Source);

    //Enregistrement des valeurs binaires pour chaque octet du fichier source (l'hommr démasqué) :
    bits[0] = (character_source&MSB)>>7;
    bits[1] = (character_source&SSSSSB)>>6;
    bits[2] = (character_source&SSSB)>>5;
    bits[3] = (character_source&FFSB)>>4;
    bits[4] = (character_source&FSB)>>3;
    bits[5] = (character_source&TSB)>>2;
    bits[6] = (character_source&SSB)>>1;
    bits[7] = (character_source&LSB);

    /*Pour chaque octet du fichier originel, on force le dernier bit à 0 et
      on y ajoute la valeur binaire actuelle de la série stockée dans le tableau "bits" (soit 0 ou 1).*/
    for(int cursor = 0 ; cursor < 8 ; cursor++)
      {
        character_transporteur = getc(Transporteur);
        character_transporteur = character_transporteur&254;
        fprintf(Out,"%c",character_transporteur+bits[cursor]);
      }
  } while(character_source!= EOF);

  fclose(Source);
  fclose(Transporteur);
  fclose(Out);
}

/* -------------Exo 2------------- */


void test_my_pow(void)
{
  for (int depth = 0; depth < 10; depth++)
    {
        printf("[My_pow]Pour %d : %d , %d , %d , %d\n",depth,my_pow(depth,0),my_pow(depth,1),my_pow(depth,2),my_pow(depth,3));
    }
}
