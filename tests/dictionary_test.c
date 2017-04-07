/*
 *  File: dictionary_test.c
 *
 *  Description: Test file for dictionary.c
 *
 *  Author: Eli Berg
 *  History:
 *    1/14/15: Created basic test.
 *    1/20/15: Fixed test to accomodate change from trie to hash table.
 */
 
#include "../src/dictionary.c"

/***************************** TESTING FUNCTIONS ****************************/

/* Tries to search for an argument character in the table */
void try_search(Dictionary* dict, char c)
{
  uint8_t value = find(dict, c);
  
  if ( value == 0xFF )
    printf("%c not found!\n", c);
  else
    printf("%c found with value %x\n", c, value);
}

/* Tests the header file functions by creating a trie, printing it out, and
then searches for valid and invalid words */
int main()
{
  Dictionary* test;
  printf("Starting dictionary creation test...\n");
  test = create_dictionary();
  printf("Hash Table created...\n");
  
  printf("Searching for characters...\n");
  try_search(test, 'p');
  try_search(test, ']');
  try_search(test, '$');
  try_search(test, '{');
  try_search(test, '\'');
  try_search(test, '[');
  try_search(test, 'z');
  try_search(test, 'w');
  try_search(test, 'A');
  try_search(test, ']');
  
  return 0;
}
