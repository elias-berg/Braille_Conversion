/*
 *  File: reading_list.h
 *
 *  Description: This header file contains functions and struct to define a 
 *  "reading list" for the Braille data to be stored in.
 *
 *  A Reading List is essentially just a potentially infinite list (based on
 *  the number of lines the Braille Pad supports) of Braille lines, where
 *  each line is a byte array, limited by the number of braille characters
 *  supported for each line on the pad.
 *
 *  Author: Eli Berg
 *  History:
 *    1/24/15: Created initial reading list idea.
 *    2/2/15: Capacity added during testing to help make code easier to follow.
 *    4/1/15: Moved LINE_CHARS macro to the new config.h file.
 */

#ifndef READING_LIST_H
#define READING_LIST_H

/* A line is an array of 8-bit characters. Because lines are stored in a list,
they all need a next and previous reference. This makes for scrolling through
lines. The size variable is to keep track of how full the line is before it
gets added to the reading list. */ 
typedef struct line {
  int size;
  int capacity;
  uint8_t character[CHARS_PER_LINE];
  struct line* next;
  struct line* prev;
} Reading_Line;

/* Creates an EMPTY reading line with no next or prev references set. */
Reading_Line* CREATE_READING_LINE();

/* Returns either TRUE or FALSE depending on if the word got added to the line.
If the word doesn't get added to the line (FALSE):
  The line is filled with spaces.
  The line MUST be added to the reading list.
  A new line MUST be started.
Else (TRUE)
  The word is added to the line. */
int ADD_WORD_TO_LINE(Reading_Line* line, int* word, int word_size);

/* Adds a space to the given line. Doesn't return anything because if the
line is full, the space is just ignored and not actually added. */
void ADD_SPACE_TO_LINE(Reading_Line* line);

/* The reading list is just a list of reading lines. */
typedef struct rlist {
  Reading_Line* head;
  Reading_Line* tail;
} Reading_List;

/* Creates an EMPTY reading list; no reading lines yet. */
Reading_List* CREATE_READING_LIST();

/* Adds the argument line to the list of lines. */
void ADD_LINE_TO_LIST(Reading_List* list, Reading_Line* line);

#endif
