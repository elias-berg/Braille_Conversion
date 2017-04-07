/*
 *  File: util.c
 *
 *  Description: Utilitiy function file.
 *
 *  Author: Eli Berg
 *  History:
 *    1/14/15: Created .c file to avoid compilation problems.
 *    2/2/15: Replaced printing functions with logging functions.
 *    3/7/15: Added subprocess function from main.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"
 
/* Prototypes to avoid compilation warnings. */
extern FILE* popen(const char *command, const char *modes);
extern int* pclose(int *stream);
 
/* For information logging */
FILE* log_file = NULL;
 
/* Malloc-checking function. */
void* CREATE(size_t size)
{
  void* obj;
  obj = malloc( size );
  if ( obj == NULL )
    perror("Error malloc'ing object");
  return obj;
}

/* Logging function. Written like the original DEBUG function but includes file 
opening but no closing; the file will be closed when the program exits.

The code is copied from an online implementation of printf. */
void LOG(const char *format, ...)
{
  va_list arg;
  
  if ( log_file == NULL )
    log_file = fopen( LOG_FILE, "w" );

  va_start( arg, format );
  vfprintf(log_file, format, arg);
  va_end( arg );
  
  #if DEBUG
    va_start( arg, format );
    vfprintf(stderr, format, arg);
    va_end( arg );
  #endif
}

/* Logs and error much like the LOG function, but has an option to quit the 
program for extreme cases of failure. */
void LOG_ERROR(char* msg, int quit)
{
  if ( log_file == NULL )
    log_file = fopen( LOG_FILE, "w" );

  fprintf(log_file, "%s\n", msg);
  #if DEBUG
    fprintf(stderr, "%s\n", msg);
  #endif
  if ( quit == TRUE )
    exit(1);
}

/* Creates a subprocess with variable arguments. Constructs the command string
from the variable arguments, executes the subprocess, then deletes the
allocated command string */
void SUBPROCESS( int argc, ... )
{
  int i, *fp, *status;
  char* arg, *cmd = CREATE( sizeof(char) * CMD_LEN );
  
  va_list argv;
  va_start( argv, argc );
  
  /* The following for-loop gets rid of the 'jump depends on unitialised value'
  valgrind error */
  for ( i = 0; i < CMD_LEN; i++ )
    cmd[i] = '\0';
  
  /* Add the arguments to the command */  
  for ( i = 0; i < argc; i++ )
  {
    arg = va_arg( argv, char* );
    strcat( cmd, arg );
    if ( i < argc-1 )
      strcat( cmd, " " );
  }
  va_end ( argv );
  
  /* Start the subprocess with the concatenated command */
  fp = (int*) popen( cmd, "r" );
  if ( fp == NULL )
    LOG_ERROR("Could not create subprocess!\n", TRUE);
    
  status = (int*) pclose( fp );
  if ( status != 0 )
    LOG_ERROR("Error closing opened process...\n", FALSE);
    
  free( cmd );
}
