#include "header.h"

//Libère chacune des cellules d'une liste chaînée de n'importe quel cellule , voir modèle de structure REPLACE_ME
void delete_up_and_down(REPLACE_ME* cell)
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

//Vérifie si l'allocation a réussi
int test_succes(void* name)
{
  if (name == NULL)
    return NO;
  else
    return YES;
}

/* -------------Exo 1------------- */
void exo_1(mp* master)
{
  FILE* Out;
  do {
    Out = fopen("Ex1.txt","w");
     }while(test_succes(Out) != YES);

  char* filename = "transporteur.txt";
  long max_alpha_char = get_nb_alpha_char(filename);
  char* bits = alpha_filter(filename,max_alpha_char,master);
  int* bytes = merge_bits(bits,max_alpha_char,master);

  for(int cursor = 0 ; cursor < max_alpha_char/8 ; cursor++)
    fprintf(Out,"%c", bytes[cursor]);

  fclose(Out);
}

long get_nb_alpha_char(char* filename)
{
  FILE *In;
  long to_return = 0;
  char character = '\0';
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
{
  FILE* In;
  char* to_return;
  char character;
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
          buffer += bits[cursor]*pow(2,power);
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
  raw_to_imageEntete(header);
  raw_to_fichierEntete(header);
  //
  exo_2_1(header);
  exo_2_2(header,master);
}

void exo_2_1(bitmap* header)
{
  show_struct(header);
}

bitmap* init_header(mp* master)
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

unsigned short char_to_short(unsigned char lsB,unsigned char msB)
{
  unsigned short to_return = 0;
  to_return = lsB+pow(2,8)*msB;
  return to_return;
}

unsigned int char_to_int(unsigned char lsB,unsigned char second,unsigned char third,unsigned char msB)
{
    unsigned int to_return = 0;
    to_return = lsB+pow(2,8)*second+pow(2,16)*third+pow(2,24)*msB;
    return to_return;
}

void raw_to_fichierEntete(bitmap* header)
{
  char* raw = header->raw_fichier;
  header->fichier->signature = char_to_short((unsigned char)raw[1],(unsigned char)raw[0]);
  header->fichier->tailleFichier = char_to_int((unsigned char)raw[5],(unsigned char)raw[4],(unsigned char)raw[3],(unsigned char)raw[2]);
  header->fichier->reserve = char_to_int((unsigned char)raw[9],(unsigned char)raw[8],(unsigned char)raw[7],(unsigned char)raw[6]);
  header->fichier->offset = char_to_int((unsigned char)raw[13],(unsigned char)raw[12],(unsigned char)raw[11],(unsigned char)raw[10]);
}

void raw_to_imageEntete(bitmap* header)
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

void exo_2_2(bitmap* header,mp* master)
{
  couleurPallete* rvb = extract_RVB(header,master);
  rvb = reach_first_cell(rvb);


}

couleurPallete* extract_RVB(bitmap* header,mp* master)
{
  FILE* In;
  do {
    In = fopen("transporteur.bmp","rb");
     }while(test_succes(In) != YES);

  char character = '\0';
  unsigned char hidden_bit = 0;
  for(int cursor = 0 ; cursor < header->size_header ; cursor++)
    {
      character = getc(In);
    }

  unsigned char buffer = 0;
  couleurPallete* couleur = NULL;
  do {
      couleur = new_cell(couleur,master);
      for(int rank = 0 ; rank < 24 ; rank++)
        {
          character = getc(In);
          hidden_bit = (unsigned char)character&LSB;
          if( rank == 7 || rank == 15 || rank == 23)
            {
            buffer += hidden_bit*pow(2,(rank)%8);
            switch (rank) {
                case 7:
                    couleur->R = buffer;
                    buffer = 0;
                    break;
                case 15:
                    couleur->V = buffer;
                    buffer = 0;
                    break;
                case 23:
                    couleur->B = buffer;
                    buffer = 0;
                    break;
              }
          }
        }
      } while(character != EOF);
  fclose(In);
  return couleur;
}

couleurPallete* new_cell(couleurPallete* last_cell,mp* master)
{
  couleurPallete* to_return;
  do{
    to_return = malloc(sizeof(couleurPallete));
    if (test_succes(to_return) == YES)
      add_pointer_master((void*)to_return ,master);
     }while(test_succes(to_return) != YES);

  if (last_cell == NULL)
    {
      to_return->next = NULL;
      to_return->previous = NULL;
    }
  else
    {
      to_return->next = NULL;
      to_return->previous = last_cell;
      last_cell->next = to_return;
    }
  return to_return;
}

couleurPallete* reach_first_cell(couleurPallete* cell)
{
  couleurPallete* to_return = cell;
  while(to_return->previous != NULL)
    {
      to_return = to_return->previous;
    }
  return to_return;
}

/* -------------Exo 2------------- */
