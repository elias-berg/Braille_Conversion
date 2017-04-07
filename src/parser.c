/*
 *  File: parser.c
 *
 *  Description: This file contains the implemented functions needed to parse a 
 *  file into translated encodings.
 *
 *  Author: Eli Berg
 *  History:
 *    1/14/15: Implemented the parse_file function.
 *    1/15/15: Finished the parse_file function to read only alpha characters.
 *    1/24/15: Restarted this implementation for use of the hash table.
 *    2/9/15: The code splits words up by any kind of white space instead of
 *            just spaces now.
 *    3/7/15: Moved main.c functions into here.
 *    4/1/15: Removed all use of Encoded_Word types.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
 
#include "util.h"
#include "config.h"
#include "dictionary.h"
#include "reading_list.h"
#include "parser.h"

/****************************** UTILITY FUNCTIONS ***************************/

/* Returns the length of a file given it's file id */
int file_len(int fid)
{
  int length = lseek( fid, 0, SEEK_END ); /* seek the end of file */
  lseek( fid, 0, SEEK_SET ); /* reset the pointer to the beginnning */
  
  /* DEBUG */ LOG("Size of file: %d\n", length);
  
  return length;
}

/* Testing function to print entire encoded words */
void print_word(int* word, int word_size)
{
  int i;
  
  LOG("Printing word of size %d: ", word_size);
  for ( i = 0; i < word_size; i++ )
    LOG("%.2x ", word[i]);
    
  LOG("...end of word\n");
}

/* Utility function that converts the current word in the buffer into an integer
pointer that is the same size as the word */
int get_word(char* buffer, int idx, int buf_len, int** word)
{
  int i, word_size = 0;
  uint8_t encoding;
  
  /* get the size of the next word */
  while ( idx < buf_len && !isspace(buffer[idx]) )
  {
    word_size++;
    idx++;
  }
  
  /* create the word pointer */
  *word = CREATE( sizeof(int)*word_size );
  
  idx -= word_size;
  for ( i = 0; i < word_size; i++ )
  {
    encoding = DICTIONARY_FIND( buffer[idx] );
    if ( encoding == NOT_DEFINED ) /* if theres no standard encoding... */
    {
      LOG("UE: ");
      encoding = DICTIONARY_FIND( ' ' ); /* space represents undefined */
    }
    LOG("%c @ %x = %.2x\n", buffer[idx], buffer[idx], encoding);
    
    (*word)[i] = encoding;
    
    idx++;
  }
  
  return word_size;
}

/*************************** HEADER FILE FUNCTIONS **************************/

/* Returns a Reading List */
Reading_List* PARSE_BRAILLE_BUFFER(char* buffer, int buf_len)
{
  int idx = 0, word_added, *cur_word = NULL, word_size;
  Reading_Line* line = CREATE_READING_LINE();
  Reading_List* RLIST = CREATE_READING_LIST();
  
  while ( idx < buf_len )
  {
    word_size = get_word( buffer, idx, buf_len, &cur_word );
    
    print_word( cur_word, word_size );
    
    /* The index increases by the number of characters we just read */
    idx += word_size;
    
    word_added = ADD_WORD_TO_LINE( line, cur_word, word_size );
    
    if ( word_added == FALSE ) /* The line is full */
    {
      ADD_LINE_TO_LIST( RLIST, line );
      line = CREATE_READING_LINE();
      word_added = ADD_WORD_TO_LINE( line, cur_word, word_size );
      
      if ( word_added == FALSE )
        LOG_ERROR("CANNOT ADD WORD TO LINE!!!!!!!!\n", TRUE);
    }
    
    free( cur_word );
    ADD_SPACE_TO_LINE( line );
    
    idx += 1; /* since we're skipping the next space */
  }
  
  return RLIST;
}

/* Translation loop function. Whenever a document is scanned, this function must
be run. */
int* PARSE_DOCUMENT(char* TESS_IN, int* buf_len)
{
  int fid, *buffer;

  /* REMOVE NOISE */
  /* subprocess( 4, "convert", TESS_IN, "-morphology thicken '1x3>:1,0,1'", 
  TESS_IN ); */

  SUBPROCESS( 3, TESSER_CMD, TESS_IN, TESS_OUT );

  /***************** DEBUG ****************************************************/
    fid = open(LOU_IN, O_RDONLY);
	  if ( fid == -1 ) /* READ ERROR */
      LOG_ERROR("Cannot open Tesseract-OCR output file!\n", TRUE);

	  *buf_len = file_len( fid );
    buffer = CREATE( sizeof(char) * (*buf_len) );
    
    if ( read(fid, buffer, *buf_len) == -1 )
      LOG_ERROR("Couldn't read file!", TRUE);
	  close( fid );
	
	  LOG("Tesser reading says:\n%s", (char*)buffer);
	  free( buffer );
	  buffer = NULL;
  /***************** DEBUG ****************************************************/
  
  SUBPROCESS( 6, LOU_CMD, GRADE_2, "<", LOU_IN, ">", LOU_OUT);
  
	SUBPROCESS( 2, "rm", LOU_IN );
  
  fid = open(LOU_OUT, O_RDONLY);
	if ( fid == -1 ) /* READ ERROR */
    LOG_ERROR("Cannot open Liblouis* output file!\n", TRUE);

	*buf_len = file_len( fid );
  buffer = CREATE( sizeof(char) * (*buf_len) );
  
  if ( read(fid, buffer, *buf_len) == -1 )
    LOG_ERROR("Couldn't read file!", TRUE);
	close( fid );
	
	/* DEBUG */ LOG("Liblouis* reading says:\n%s", (char*)buffer);
	
	SUBPROCESS( 2, "rm", LOU_OUT );
	
	return buffer;
}

