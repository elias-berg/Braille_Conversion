/*
 *  File: main.c
 *
 *  Description: This file is the main brain for all of the parsing and 
 *  translating of braille.
 *
 *  Author: Eli Berg
 *  History:
 *    1/20/15: File created to parse Liblouis* output.
 *    3/7/15: Moved the subprocess function to the utilities file. Also moved
 *    the translation loop function into the parser files so this file can be
 *    used as the main brain for sending output to the Pi's GPIO pins.
 *    4/19/15: Added functions to traverse list and interactively print out
 *    the data for an updated testing file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "util.h"
#include "config.h"
#include "dictionary.h"
#include "reading_list.h"
#include "parser.h"

int line_num;

/* LIST OF ALL LINES */
Reading_List* list;

/* CURRENT LOCATION IN THE LIST */
Reading_Line* head;

/* Prints all of the supported lines of the board according to the config.h to
stdout */
void debug_print_lines()
{
  int i, j;
	Reading_Line* cur = head;
	
	for ( i = 0; i < NUM_LINES; i++ )
	{
	  if ( !cur )
	    break;
	  
	  LOG("%d\t", line_num+i);
	  for ( j = 0; j < CHARS_PER_LINE; j++ )
	    LOG("%.2x ", cur->character[j]);
	  LOG("\n");
	  
	  cur = cur->next;
	}
}

void next_line()
{
  if ( !head->next )
    return;
  head = head->next;
  line_num++;
}

void prev_line()
{
  if ( !head->prev )
    return;
  head = head->prev;
  line_num--;
}

/* Command line input loop for terminal navigation of the reading list lines */
void input_loop()
{
  char input;

  while ( TRUE )
  {
    scanf("%c", &input);
    if ( input == 'n' )
      next_line();
    else if ( input == 'p' )
      prev_line();
    else if ( input == 'q' )
      break;
    else
      continue;
    debug_print_lines();
  }
}

/* Basic main to test out the translation loop */
int main(int argc, char** argv)
{
  int buf_len;
  
  /* Obtain the Braille-ASCII buffer */
  int* buffer = PARSE_DOCUMENT("document.png", &buf_len);
  
	/* Now that we've read in the Braille ASCII, parse it into a reading list */
	list = PARSE_BRAILLE_BUFFER( (char*)buffer, buf_len );
	
	line_num = 1;
	head = list->head;
	
	debug_print_lines();
	
	
	/* IF THE USER RAN THE PROGRAM WITH -terminal OPTION */
	if ( argc == 2 && strcmp(argv[1], "-terminal") == 0 )
	  input_loop();
	
  return 0;
}

