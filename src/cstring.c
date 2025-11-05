#include "cstring.h"
#include <stdlib.h>
#include <string.h>

/* Initialize a CString with a specified initial capacity.
   Allocates the chars array and sets all slots to NULL. */
void cstring_init(CString *cstring, unsigned int initialSize) {
  if (cstring == NULL)
    return;

  /* Ensure size is at least 1. */
  cstring->size = (initialSize > 0) ? initialSize : 1;
  cstring->length = 0;

  /* Allocate array of char pointers and initialize all to NULL. */
  cstring->chars = (char **)malloc(cstring->size * sizeof(char *));
  if (cstring->chars != NULL) {
    for (unsigned int i = 0; i < cstring->size; ++i) {
      cstring->chars[i] = NULL;
    }
  }
}

/* Destroy a CString by freeing all allocated character pointers and the chars
 * array. */
void cstring_destroy(CString *cstring) {
  if (cstring == NULL)
    return;

  /* Free each allocated character. */
  if (cstring->chars != NULL) {
    for (unsigned int i = 0; i < cstring->length; ++i) {
      if (cstring->chars[i] != NULL) {
        free(cstring->chars[i]);
        cstring->chars[i] = NULL;
      }
    }
    /* Free the array itself. */
    free(cstring->chars);
    cstring->chars = NULL;
  }

  /* Zero out the struct fields. */
  cstring->size = 0;
  cstring->length = 0;
}

/* Resize the underlying chars array to a new capacity.
   Allocates new memory and NULL-initializes any new slots. */
bool resize(CString *cstring, unsigned int newSize) {
  if (cstring == NULL)
    return false;

  /* Allocate array of char pointers (not char bytes). */
  char **chars = (char **)realloc(cstring->chars, newSize * sizeof(char *));

  if (chars == NULL)
    return false;

  /* Save the old size before updating. */
  unsigned int oldSize = cstring->size;
  cstring->chars = chars;
  cstring->size = newSize;

  /* NULL-initialize any new slots (when growing). */
  if (newSize > oldSize) {
    for (unsigned int i = oldSize; i < newSize; ++i) {
      cstring->chars[i] = NULL;
    }
  }

  /* If shrinking, cap length to new size. */
  if (newSize < cstring->length) {
    cstring->length = newSize;
  }

  return true;
}

/* Add a character to the CString at the first available (NULL) position.
   Grows the array by 1 if full. Increments length on success. */
bool addChar(CString *cstring, char ch) {
  if (cstring == NULL)
    return false;

  /* If no space, grow by 1. */
  if (cstring->length >= cstring->size) {
    if (!resize(cstring, cstring->size + 1))
      return false;
  }

  /* Scan for first NULL slot. */
  for (unsigned int i = 0; i < cstring->size; ++i) {
    if (cstring->chars[i] == NULL) {
      /* Allocate 1 byte for the character. */
      cstring->chars[i] = (char *)malloc(sizeof(char));
      if (cstring->chars[i] == NULL)
        return false;

      /* Store the character and increment length. */
      *(cstring->chars[i]) = ch;
      cstring->length++;
      return true;
    }
  }

  /* Should not reach here, but as fallback, try to grow and append. */
  if (!resize(cstring, cstring->size + 1))
    return false;

  cstring->chars[cstring->size - 1] = (char *)malloc(sizeof(char));
  if (cstring->chars[cstring->size - 1] == NULL)
    return false;

  *(cstring->chars[cstring->size - 1]) = ch;
  cstring->length++;
  return true;
}

/* Remove the character at a given index, shifting subsequent characters left.
   Frees the associated memory and updates length. */
bool removeChar(CString *cstring, unsigned int index) {
  if (cstring == NULL)
    return false;

  /* Validate index and pointers. */
  if (index >= cstring->length)
    return false;

  if (cstring->chars == NULL || cstring->chars[index] == NULL)
    return false;

  /* Free the character at this index. */
  free(cstring->chars[index]);
  cstring->chars[index] = NULL;

  /* Shift all characters after index left by one. */
  for (unsigned int i = index; i < cstring->length - 1; ++i) {
    cstring->chars[i] = cstring->chars[i + 1];
  }

  /* NULL the last slot. */
  cstring->chars[cstring->length - 1] = NULL;

  /* Decrement length. */
  cstring->length--;

  return true;
}

/* Get the current capacity (allocated size) of the CString. */
unsigned int getSize(CString *cstring) {
  if (cstring == NULL)
    return 0;
  return cstring->size;
}

/* Print the contents of a CString by copying all characters into a dynamically
   allocated buffer. Skips NULL slots (compacts output). Caller must free the
   returned buffer. */
char *cprint(CString *cstring) {
  if (cstring == NULL || cstring->length == 0)
    return NULL;

  /* Allocate a buffer for all characters plus null-terminator. */
  char *out = (char *)malloc(cstring->length + 1);
  if (out == NULL)
    return NULL;

  /* Copy characters, skipping NULLs (compact output). */
  unsigned int outIndex = 0;
  for (unsigned int i = 0; i < cstring->size && outIndex < cstring->length;
       ++i) {
    if (cstring->chars[i] != NULL) {
      out[outIndex] = *(cstring->chars[i]);
      outIndex++;
    }
  }

  /* Null-terminate. */
  out[outIndex] = '\0';

  return out;
}
