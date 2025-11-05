#include "cstring.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

CString increaseSize(CString *cstring) {

};

CString decreaseSize(CString *cstring) {

};
CString increaseLength(CString *cstring) {

};
CString decreaseLength(CString *cstring) {

};

void cprint(CString *cstring) {

};

bool resize(CString *cstring, unsigned int newSize) {
  char **chars =
      realloc(cstring->chars, (cstring->size + 1) * sizeof(cstring->chars));

  if (chars == NULL)
    return false;

  return true;
};

bool addChar(CString *cstring, char ch) {
  if (cstring->length > cstring->size) {
    resize(cstring, cstring->size + 1);

    for (int i = 0; i < cstring->length; ++i) {
      if (cstring->chars[i] == NULL) {
        cstring->chars[i] = &ch;
        return true;
      }
    }
  }

  return false;
};

bool removeChar(CString *cstring, unsigned int index) {

};

unsigned int getSize(CString *cstring);
