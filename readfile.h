#ifndef READFILE_H
#define READFILE_H

#include "employee.h"

int open_file(const char* filename);

int read_int(int* value);
int read_float(float* value);
int read_string(char* str);

// misc function to be used in open_file name should be self-explanatory
void close_file();
int isValidEmployee(Employee* emp);
void sortEmployeesByID();

#endif