/*
 *  File: dictionary.c
 *
 *  Description: This file contains the implementation of the structs and
 *  methods from the corresponding header file.
 *
 *  Author: Eli Berg
 *  History:
 *    1/6/15: Implemented the trie dictionary structure.
 *    1/9/15: Finished basic trie implementation with light testing.
 *    1/10/15: Added more visually appealing comment blocks.
 *    1/14/15: Changed name to dictionary from braille_dict
 *    1/20/15: The trie is now a hash table of characters used by Liblouis*
 *    1/27/15: The dictionary is now global and untouchable outside the program.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
#include "util.h"
#include "encodings.h"
#include "dictionary.h"

/* Global dictionary. Untouchable by outside forces. */
Dictionary* dictionary = NULL;

/****************************** UTILITY FUNCTIONS ***************************/

/* Create the entire braille dictionary hash table */
Dictionary* create_dictionary()
{
  int i;
  
  /* create the table */
  Dictionary* dict = CREATE( sizeof(Dictionary) );
  
  /* initialize the table to all NOT_DEFINED macro */
  for ( i = 0; i < TABLE_SIZE; i++ )
    dict->table[i] = NOT_DEFINED;
  
  /* insert all of the Liblouis* encoded characters */
  for ( i = 0; i < ENCODINGS; i++ )
  {
    Encoding cur = LOU_ASCII[i]; /* from lou_config.h */
    dict->table[ (int)cur.character ] = cur.value;
  }
  
  return dict;
}

/*************************** HEADER FILE FUNCTIONS **************************/

/* Given the dictionary, checks to see if the argument letter is in the table */
uint8_t DICTIONARY_FIND(char letter)
{  
  uint8_t value;
  
  if ( dictionary == NULL )
  {
    dictionary = create_dictionary();
    /* DEBUG */ LOG("Created dictionary!\n");
  }
  
  /* If ASCII value is not valid; not between 0 to 131 */
  if ( (int)letter < 0 || (int)letter > TABLE_SIZE )
       return NOT_DEFINED;
  
  value = dictionary->table[ (int)letter ];
  return value;
}
