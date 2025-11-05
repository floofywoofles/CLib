#pragma once

#include <stdbool.h>

typedef struct {
  unsigned int size;
  unsigned int length;
  char **chars;
} CString;

CString increaseSize(CString *cstring);
CString decreaseSize(CString *cstring);
CString increaseLength(CString *cstring);
CString decreaseLength(CString *cstring);

void cprint(CString *cstring);

bool resize(CString *cstring, unsigned int newSize);
bool addChar(CString *cstring, char ch);
bool removeChar(CString *cstring, unsigned int index);

unsigned int getSize(CString *cstring);