//THITIPUN SRINARMWONG A20501320
#include <stdio.h>
#include "employee.h"
#include "readfile.h"

extern Employee database[MAX_EMPLOYEES];
extern int employeeCount;
static FILE* currentFile = NULL;

// Open the file and reads worker data
// checks 4 fields separated by a space
// loads the data into the employee array
// sort data with ID in ascending order
// Return 0 if successful, or -1 when error.
int open_file(const char* filename) {
    currentFile = fopen(filename, "r");

    if (currentFile != NULL) {
        // File opened successfully, check its format        
        while ( employeeCount < MAX_EMPLOYEES && // Avoid Buffer overflow
               
                read_int(&database[employeeCount].id) == 0 && 
                read_string(database[employeeCount].first_name) == 0 &&
                read_string(database[employeeCount].last_name) == 0 && 
                read_int(&database[employeeCount].salary) == 0) {

                // Check if data ID and Salary is valid 
                if (isValidEmployee(&database[employeeCount])) {
                    employeeCount++; // increment if valid employee data
                } else {
                    close_file();
                    return -1;  // return error if not
                }
        }
        
        sortEmployeesByID();
        close_file();
        return 0; // Success
    } else {
        close_file();
        return -1; // File could not be opened or have wrong format
    }
}

int read_int(int *value) {
    if (fscanf(currentFile, "%d", value) == 1) {
        return 0; // Success
    } else {
        return -1; // EOF or error
    }
}

int read_float(float *value){
    if (fscanf(currentFile, "%f", value) == 1) {
        return 0; // Success
    } else {
        return -1; // EOF or error
    }
    // we don't have float to read Why need so ?_?
}    

int read_string(char *str) {
    if (fscanf(currentFile, "%s", str) == 1) {
        return 0; // Success
    } else {
        return -1; // EOF or error
    }
}

void close_file() {
    if (currentFile) {
        fclose(currentFile);
        currentFile = NULL;
    }
}

int isValidEmployee(Employee* emp) {
    // Check ID and Salary constrain
    if (emp->id < MIN_ID || emp->id > MAX_ID || 
        emp->salary < MIN_SALARY || emp->salary > MAX_SALARY) {
        return 0;  // False
    }
    return 1;  // True
}

void merge(Employee arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Employee L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Employee arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void sortEmployeesByID() {
    mergeSort(database, 0, employeeCount - 1);
}
