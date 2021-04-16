#ifndef VALIDATION_H
#define VALIDATION_H

char *diag[128];
char *ver_and_hor[128];

int get_validation(char *v[], int c, int n);
int validation(char *f, char *t, bool r);

#endif