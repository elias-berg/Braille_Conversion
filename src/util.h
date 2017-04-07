/*
 *  File: util.h
 *
 *  Description: Utilitiy function file.
 *
 *  Author: Eli Berg
 *  History:
 *    1/6/15: Added malloc'ing utility function.
 *    1/14/15: Created error and debug methods, which are essentially the same.
 *    1/27/15: Added not-defined value for hash table use.
 *    2/2/15: Replaced DEBUG and ERROR with log file functions.
 *    3/7/15: Added subprocess function definition from main.c.
 *    4/1/15: Moved NOT_DEFINED macro to dictionary.h.
 */
 
#ifndef UTIL_H
#define UTIL_H

/* Max size for a subprocess command string */
#define CMD_LEN 100

/* Basic boolean values */
#define TRUE 1
#define FALSE 0

/* For stdout and stderr debugging */
#define DEBUG 1

/* The log file name */
#define LOG_FILE "translate.log"

/* A malloc-checking function. */
void* CREATE(size_t size);

/* The logging function that will write output to a log file for review and
debugging */
void LOG(const char *format, ...);

/* The logging function that will write output to a log file for review and
debugging */
void LOG_ERROR(char* msg, int quit);

/* Creates a subprocess with variable arguments. Constructs the command string
from the variable arguments, executes the subprocess, then deletes the
allocated command string */
void SUBPROCESS( int argc, ... );

#endif
