#ifndef VALIDATION_H
#define VALIDATION_H

extern char *diag[128];
extern char *verhor[128];

int get_validation(char *v[], int c, int n);
int validation(char *f, char *t, bool r);

#endif