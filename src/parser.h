/*
 *  File: parser.h
 *
 *  Description: This file contains the functions needed to parse a file into
 *  translated encodings AND to parse the encodings into a board-output list.
 *
 *  Author: Eli Berg
 *  History:
 *    1/14/15: Created basic functions for parsing.
 *    1/24/15: Fixed parser to utilize the new (hash table) dictionary.
 *    3/7/15: Moved main.c function definitions here.
 */

#ifndef PARSER_H
#define PARSER_H
 
#define TESSER_CMD "tesseract"
#define TESS_OUT "tesser_out"

#define LOU_CMD "lou_translate"
#define GRADE_1 "en-us-g1.ctb"
#define GRADE_2 "en-us-g2.ctb"
#define LOU_IN "tesser_out.txt"
#define LOU_OUT "lou_out"
 
/* Parses the document image and returns a char* Braille-ASCII buffer obtained
through TOCR and Liblouis*. The argument is the filename of the document image,
which should be a .png image, but is not checked. Stores the buffer length
in the buf_len argument. */
int* PARSE_DOCUMENT(char* TESS_IN, int* buf_len);
 
/* Parses the buffer obtained from a translated file. Uses the dictionary to
look up the braille encodings. */
Reading_List* PARSE_BRAILLE_BUFFER(char* buffer, int buf_len);

#endif
