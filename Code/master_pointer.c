#include "header.h"

mp* create_master_pointer(void)
{
  mp* to_return;
  do {
     to_return = malloc(sizeof(mp));
  } while(test_success(to_return) != YES);
  to_return->next = NULL;
  to_return->previous = NULL;
  to_return->pointer = to_return;
  return to_return;
}

int add_pointer_master(void* pointer,mp* master)
{
  mp* buffer = reach_last_cell(master);
  int counter = 0;
  do {
     buffer->next = malloc(sizeof(mp));
     counter++;
  } while(test_success(buffer->next) != YES && counter < MAX_TRY);

  if (counter  == 100 || buffer->next == NULL)
    {
      printf("Ajout du pointeur impossible.\n");
      return NO;
    }
  else
    {
      buffer->next->previous = buffer;
      buffer->next->next = NULL;
      buffer->next->pointer = pointer;
      return YES;
    }
}

mp* reach_last_cell(mp* head)
{
  void* to_return = head;
  while(((mp*)to_return)->next != NULL)
    {
      to_return = ((mp*)to_return)->next;
    }
  return (mp*)to_return;
}

//Libère chacune des cellules d'une liste chaînée en partant de la tête, la structure doit avoir un pointeur next.
void delete_down(mp* head)
{
  mp* buffer;
  int counter = 0;
  do
    {
      buffer = head->next;
      if(head->pointer != head)
        free(head->pointer);
      free(head);
      head = buffer;
      counter += 2;
    }
    while (head != NULL);
  printf("Suppression de %d cellules effectué\n",counter);
}
