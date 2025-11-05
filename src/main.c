#include "cstring.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* Initialize a CString with initial capacity of 4. */
  CString cstr;
  cstring_init(&cstr, 4);

  /* Add some characters. */
  addChar(&cstr, 'c');
  addChar(&cstr, 'a');
  addChar(&cstr, 't');

  /* Print the CString. */
  char *out = cprint(&cstr);
  if (out != NULL) {
    printf("%s\n", out);
    free(out);
  }

  /* Clean up. */
  cstring_destroy(&cstr);

  return 0;
}
