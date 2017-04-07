/*
 *  File: parser_test.c
 *
 *  Description: Test file for parser.c
 *
 *  Author: Eli Berg
 *  History:
 *    1/14/15: Created basic test.
 */
 
#include "../parser.c"

/***************************** TESTING FUNCTIONS ****************************/

/* This code was lifted from the encoder_test.c file */

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

/* Tests a hard-coded text file */
int main()
{
  int file = open( "test2.txt", O_RDONLY ); /* open a test file */
    
  if ( file == -1 ) /* READ ERROR */
  {
    fprintf( stderr, "Cannot open file test2.txt!\n");
    return 1;
  }
  
  Dict_Node* dict = create_dict();
  Queue* Q = parse_file(file, dict);
  
  // test the queue
  while ( Q ) 
  {
    Encoded_Word* cur = dequeue( &Q );
    print_word( cur );
  }
}