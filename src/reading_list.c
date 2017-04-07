/*
 *  File: reading_list.c
 *
 *  Description: The implementation of the reading list functions to 
 *  appropriately be able to display the Braille information to the output
 *  pad.
 *
 *  Author: Eli Berg
 *  History:
 *    1/24/15: Started reading list function implementations.
 *    2/2/15: Fixed variable name in adding spaces to lines. Capacity added 
 *            during testing to help make code easier to follow.
 *    4/1/15: Included config.h which now contains the board config.
 */
 
#include <stdlib.h>
#include <stdint.h>
 
#include "util.h"
#include "config.h"
#include "reading_list.h"

/****************************** UTILITY FUNCTIONS ***************************/

/* Fills the reading line with 0s (spaces) */
void fill_line(Reading_Line* line)
{
  int i;
  for ( i = line->size; i < CHARS_PER_LINE; i++ )
    line->character[i] = 0x00;
  line->size = CHARS_PER_LINE;
  line->capacity = 0;
}

/*************************** HEADER FILE FUNCTIONS **************************/

/* Creates an EMPTY reading line with no next or prev references set. */
Reading_Line* CREATE_READING_LINE()
{
  Reading_Line* new_line = CREATE( sizeof(Reading_Line) );
  
  new_line->size = 0;
  new_line->capacity = CHARS_PER_LINE;
  new_line->next = NULL;
  new_line->prev = NULL;
  
  return new_line;
}

/* Returns either TRUE or FALSE depending on if the word got added to the 
line. */
int ADD_WORD_TO_LINE(Reading_Line* line, int* word, int word_size)
{  
  int i;

  /* no space left; fill with spaces and return false */
  if ( line->capacity < word_size )
  {
    fill_line( line );
    return FALSE;
  }
  
  /* add the word to the line */
  for ( i = 0; i < word_size; i++ )
  {
    line->character[line->size] = word[i];
    line->size++;
    line->capacity--;
  }
  
  return TRUE;
}

/* Adds a space to the line, regardless of if there's space or not. */
void ADD_SPACE_TO_LINE(Reading_Line* line)
{
  int size = line->size;
  int space_left = CHARS_PER_LINE - size;
  
  if ( space_left < 1 )
    return;
  
  line->character[size] = 0x00;
  line->capacity = space_left-1;
  line->size = size+1;
}

/* Creates an EMPTY reading list; no reading lines yet. */
Reading_List* CREATE_READING_LIST()
{
  Reading_List* new_list = CREATE( sizeof(Reading_List) );
  
  new_list->head = NULL;
  new_list->tail = NULL;
  
  return new_list;
}

/* Adds the argument line to the reading list of lines. */
void ADD_LINE_TO_LIST(Reading_List* list, Reading_Line* line)
{
  if ( list->head == NULL )
  {
    list->head = line;
    list->tail = line;
  }
  else
  {
    list->tail->next = line;
    line->prev = list->tail;
    list->tail = line;
  }
}
