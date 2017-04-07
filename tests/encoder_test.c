/*
 *  File: encoder_test.c
 *
 *  Description: Test file for encoder.c
 *
 *  Author: Eli Berg
 *  History:
 *    1/14/15: Created basic test.
 *    1/20/15: Fixed test to accomodate the lou_config file.
 */

#include "../src/encoder.c"
#include "../src/lou_config.h"

/***************************** TESTING FUNCTIONS ****************************/

void print_word(Encoded_Word* word)
{
  Char_List* cur = word->head;
  
  printf("Printing word of size %d...", word->characters);
  while ( cur )
  {
    printf("%x...", cur->code);
    cur = cur->next;
  }
  printf("end of word\n");
}

int main()
{
  Encoded_Word* word;
  printf("Creating a new blank word...\n");
  word = create_new_word();
  
  printf("Adding %x...\n", LOU_ASCII[3].value);
  add_character(word, LOU_ASCII[3].value);
  printf("Adding %x...\n", LOU_ASCII[7].value);
  add_character(word, LOU_ASCII[7].value);
  printf("Adding %x...\n", LOU_ASCII[22].value);
  add_character(word, LOU_ASCII[22].value);
  
  print_word(word);
  
  return 0;
}
