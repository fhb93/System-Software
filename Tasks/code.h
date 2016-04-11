#ifndef _CODE_H
#define _CODE_H

int code (char * desc, void * v, FILE * f);

int decode (FILE * f);

void key(char * desc, char * arr);

void value(void * v);

unsigned int zigzag(int n);

#endif
