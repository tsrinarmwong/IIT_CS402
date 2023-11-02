#ifndef EMPLOYEE_H
#define EMPLOYEE_H

// Employee constrains
#define MAX_EMPLOYEES 1024
#define MAXNAME 64
#define MIN_ID 100000
#define MAX_ID 999999
#define MIN_SALARY 30000
#define MAX_SALARY 150000

// Define the Employee struct
typedef struct {
    int id;
    char first_name[MAXNAME];
    char last_name[MAXNAME];
    int salary;
} Employee;

#endif // EMPLOYEE_H