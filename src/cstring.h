#pragma once

#include <stdbool.h>

typedef struct {
  unsigned int size;
  unsigned int length;
  char **chars;
} CString;

/* Initialize a CString with a specified initial capacity.
   Sets size to max(1, initialSize), length to 0, and allocates the chars array
   with all slots set to NULL. */
void cstring_init(CString *cstring, unsigned int initialSize);

/* Destroy a CString by freeing all allocated character pointers and the chars
 * array itself. */
void cstring_destroy(CString *cstring);

/* Print the contents of a CString into a dynamically allocated string (caller
 * must free). */
char *cprint(CString *cstring);

/* Resize the underlying chars array to a new capacity. */
bool resize(CString *cstring, unsigned int newSize);

/* Add a character to the first available NULL slot in the CString. */
bool addChar(CString *cstring, char ch);

/* Remove the character at a given index and shift remaining characters left. */
bool removeChar(CString *cstring, unsigned int index);

/* Get the current capacity (allocated size) of the CString. */
unsigned int getSize(CString *cstring);
