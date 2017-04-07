/*
 *  File: dictionary.h
 *
 *  Description: This header file contains all the functions and the struct
 *  required to store the entire braille conversion dictionary.
 *  The braille dictionary is a trie.
 *
 *  Author: Eli Berg
 *  History:
 *    1/6/15: Created file with initial trie structs.
 *    1/14/15: Changed name to dictionary from braille_dict
 *    1/20/15: The dictionary is now a hash table for Liblouis* translation.
 *    1/27/15: The dictionary is now only created inside the actual
 *             implementation.
 *    4/1/15: Added NOT_DEFINED macro from util.h.
 */
 
#ifndef DICTIONARY_H
#define DICTIONARY_H

/* 131 is the closest prime number above 128 (being the number of ASCII 
characters */
#define TABLE_SIZE 131

  
/* Not defined reference in dictionary */
#define NOT_DEFINED 0xFF
  
/* The dictionary is just a table of braille values mapped by ascii characters
that are found in the text. */
typedef struct dict {
  uint8_t table[TABLE_SIZE];
} Dictionary;

/* Looks in the hash table for the argument character. Creates a dictionary
if it hasn't been created yet. Returns  */
uint8_t DICTIONARY_FIND(char c);

#endif
