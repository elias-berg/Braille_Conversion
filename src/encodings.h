/*
 *  File: encodings.h
 *
 *  Description: This header file contains the braille encodings for
 *  all Liblouis* Braille ASCII characters.
 *
 *  Liblouis* Braille ASCII characters were found in the library's translation
 *  tables:
 *    us-table.dis            - non-alphabetic ASCII characters
 *    latinLetterDef6Dots.uti - alphabetic ASCII characters
 *
 *  The Braille ASCII encodings are represented by 6 bits, one bit corresponding
 *  to each dot of a 6-dot braille character:
 *
 *                    o o   1 4
 *                    o o   2 5
 *                    o o   3 6
 *
 *  Author: Eli Berg
 *  History:
 *    1/20/15: Created file with Liblouis* translation encodings.
 *    4/1/15:  Changed file name to encodings.h.
 */
 
#ifndef ENCODINGS_H
#define ENCODINGS_H

typedef struct code {
  char character;
  uint8_t value;
} Encoding;

#define ENCODINGS 64

static const Encoding LOU_ASCII[] = {
/**************************** Standard Letters *****************************/
  { 'a', 0x20 }, /* 0b10 0000 */
  { 'b', 0x30 }, /* 0b11 0000 */
  { 'c', 0x24 }, /* 0b10 0100 */
  { 'd', 0x26 }, /* 0b10 0110 */
  { 'e', 0x22 }, /* 0b10 0010 */
  { 'f', 0x34 }, /* 0b11 0100 */
  { 'g', 0x36 }, /* 0b11 0110 */
  { 'h', 0x32 }, /* 0b11 0010 */
  { 'i', 0x14 }, /* 0b01 0100 */
  { 'j', 0x16 }, /* 0b01 0110 */
  { 'k', 0x28 }, /* 0b10 1000 */
  { 'l', 0x38 }, /* 0b11 1000 */
  { 'm', 0x2C }, /* 0b10 1100 */
  { 'n', 0x2E }, /* 0b10 1110 */
  { 'o', 0x2A }, /* 0b10 1010 */
  { 'p', 0x3C }, /* 0b11 1100 */
  { 'q', 0x3E }, /* 0b11 1110 */
  { 'r', 0x3A }, /* 0b11 1010 */
  { 's', 0x1C }, /* 0b01 1100 */
  { 't', 0x1E }, /* 0b01 1110 */
  { 'u', 0x29 }, /* 0b10 1001 */
  { 'v', 0x39 }, /* 0b11 1001 */
  { 'w', 0x17 }, /* 0b01 0111 */
  { 'x', 0x2D }, /* 0b10 1101 */
  { 'y', 0x2F }, /* 0b10 1111 */
  { 'z', 0x2B }, /* 0b10 1011 */
/**************************** Liblouis Mappings ****************************/
  { '1', 0x10 }, /* 0b01 0000 */
  { '2', 0x18 }, /* 0b01 1000 */
  { '3', 0x12 }, /* 0b01 0010 */
  { '4', 0x13 }, /* 0b01 0011 */
  { '5', 0x11 }, /* 0b01 0001 */
  { '6', 0x1A }, /* 0b01 1010 */
  { '7', 0x1B }, /* 0b01 1011 */
  { '8', 0x19 }, /* 0b01 1001 */
  { '9', 0x0A }, /* 0b00 1010 */
  { '0', 0x0B }, /* 0b00 1011 */

  { '(', 0x3B }, /* 0b11 1011 */
  { '}', 0x37 }, /* 0b11 0111 */
/*{ ']', 1101111 }, invalid 7th braille dot */
  { '?', 0x27 }, /* 0b10 0111 */
  { ':', 0x23 }, /* 0b10 0011 */
  { ')', 0x1F }, /* 0b01 1111 */
  { '!', 0x1D }, /* 0b01 1101 */
  { '{', 0x15 }, /* 0b01 0101 */
/*{ '[', 0101011 }, invalid 7th braille dot */
  { '\'', 0x08 }, /* 0b00 1000 */
  { '-', 0x09 }, /* 0b00 1001 */
  { '.', 0x05 }, /* 0b00 0101 */
  { '"', 0x02 }, /* 0b00 0010 */
  { ';', 0x03 }, /* 0b00 0011 */
  { ',', 0x01 }, /* 0b00 0001 */
  { '&', 0x3D }, /* 0b11 1101 */
  { '$', 0x35 }, /* 0b11 0101 */
  { '|', 0x33 }, /* 0b11 0011 */
/*{ '\\', 1100111 }, invalid 7th braille dot */
  { '%', 0x25 }, /* 0b10 0101 */
  { '*', 0x21 }, /* 0b10 0001 */
  { '#', 0x0F }, /* 0b00 1111 */
  { '`', 0x04 }, /* 0b00 0100 */
  { '_', 0x07 }, /* 0b00 0111 */
/*{ '^', 0001101 }, invalid 7th braille dot */
/*{ '@', 0001001 }, invalid 7th braille dot */
  { '=', 0x3F }, /* 0b11 1111 */
  { '<', 0x31 }, /* 0b11 0001 */
  { '/', 0x0C }, /* 0b00 1100 */
  { '>', 0x0E }, /* 0b00 1110 */
  { '+', 0x0D }, /* 0b00 1101 */
  { '~', 0x06 }, /* 0b00 0110 */
  { ' ', 0x00 }  /* 0b00 0000 */
};
  
#endif
