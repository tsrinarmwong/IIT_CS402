#include "database.h"
#include "readfile.h"
#include "employee.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Employee database[MAX_EMPLOYEES];
int employeeCount = 0;

void printDatabase() {
    char fullName[100]; // Assuming the combined first name and last name won't exceed 99 characters

    printf("+--------------------------------+------------+------------+\n");
    printf("| NAME                           |     SALARY |         ID |\n");
    printf("+--------------------------------+------------+------------+\n");
    for (int i = 0; i < employeeCount; i++) {
        // Combine first name and last name with a space in between
        sprintf(fullName, "%s %s", database[i].first_name, database[i].last_name);

        printf("| %-30s | %10d | %10d |\n", 
               fullName, 
               database[i].salary, 
               database[i].id);
    }
    printf("+--------------------------------+------------+------------+\n");
    printf("Number of Employees: %d\n", employeeCount);
}



Employee* searchByID(int id) {
    // LINEAR SEARCH
    for (int i = 0; i < employeeCount; i++) {
        if (database[i].id == id) {
            return &database[i];
        }
    }
    return NULL;
}

void lookupByID() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    if (id < MIN_ID || id > MAX_ID) {
        printf("Invalid ID. Please enter an ID between %d and %d.\n", MIN_ID, MAX_ID);
        return;
    }

    Employee* emp = searchByID(id);
    if (emp != NULL) {
        printf("-------------------------\n");
        printf("Name: %s %s\n", emp->first_name, emp->last_name);
        printf("Salary: %d\n", emp->salary);
        printf("ID: %d\n", emp->id);
        printf("-------------------------\n");
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}

void mergeLastName(Employee arr[], int l, int m, int r) {
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
        // Compare last_name using strcmp
        if (strcmp(L[i].last_name, R[j].last_name) <= 0) {
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

void mergeLastNameSort(Employee arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeLastNameSort(arr, l, m);
        mergeLastNameSort(arr, m + 1, r);

        mergeLastName(arr, l, m, r);
    }
}

void sortEmployeesByLastName() {
    mergeLastNameSort(database, 0, employeeCount - 1);
}

Employee* searchByLastName(const char *last_name) {
    sortEmployeesByLastName();
    
    // BINARY SEARCH
    int low = 0;
    int high = employeeCount - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int comparison = strcmp(database[mid].last_name, last_name);

        if (comparison == 0) {  // Found a match
            return &database[mid];
        } else if (comparison < 0) {  // Search in right
            low = mid + 1;
        } else {  // Search in left
            high = mid - 1;
        }
    }

    return NULL;
}

void lookupByLastName() {
    char last_name[MAXNAME];
    printf("Enter Last Name: ");
    scanf("%s", last_name);

    Employee* emp = searchByLastName(last_name);
    if (emp != NULL) {
        printf("-------------------------\n");
        printf("Name: %s %s\n", emp->first_name, emp->last_name);
        printf("Salary: %d\n", emp->salary);
        printf("ID: %d\n", emp->id);
        printf("-------------------------\n");

    } else {
        printf("Employee with Last Name %s not found.\n", last_name);
    }

    sortEmployeesByID();
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("The database is full. Cannot add more employees.\n");
        return;
    }

    Employee newEmployee;
    int confirmation;

    // Get first name
    while(1) {
        printf("Enter employee's first name (Max length %d): ", MAXNAME - 1); // Last is Null terminator
        scanf("%s", newEmployee.first_name);
        if(strlen(newEmployee.first_name) < MAXNAME) {
            break;
        } else {
            printf("Name too long. Please try again.\n");
        }
    }

    // Get last name
    while(1) {
        printf("Enter employee's last name (Max length %d): ", MAXNAME - 1);
        scanf("%s", newEmployee.last_name);
        if(strlen(newEmployee.last_name) < MAXNAME) {
            break;
        } else {
            printf("Name too long. Please try again.\n");
        }
    }

    // Get and validate salary
    while (1) {
        printf("Enter employee's salary (between %d and %d): ", MIN_SALARY, MAX_SALARY);
        scanf("%d", &newEmployee.salary);
        if (newEmployee.salary >= MIN_SALARY && 
            newEmployee.salary <= MAX_SALARY) {
            break;
        } else {
            printf("Invalid salary. Please enter again.\n");
        }
    }

    // Generate ID
    if (employeeCount == 0) {
        newEmployee.id = MIN_ID;
    } else if (database[employeeCount - 1].id < MAX_ID) {
        newEmployee.id = database[employeeCount - 1].id + 1;
    } else {
        printf("No more available IDs. Cannot add new employee.\n");
        return;
    }

    // Confirm details
    printf("\nNew Employee Details:\n");
    printf("Name: %s %s\n", newEmployee.first_name, newEmployee.last_name);
    printf("Salary: %d\n", newEmployee.salary);
    printf("ID: %d\n", newEmployee.id);

    printf("\nDo you want to add this employee? (1 for Yes, 0 for No): ");
    scanf("%d", &confirmation); 

    if (confirmation == 1) {
        database[employeeCount] = newEmployee;
        employeeCount++;
        printf("Employee added successfully!\n");
    } else {
        printf("Employee addition canceled.\n");
    }
}

void quitProgram() {
    printf("Exiting...\n");
    printf("Thank you for using the Employee Database system.\n");
    printf("Good Bye.\n");
    exit(0);
}