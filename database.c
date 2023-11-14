//THITIPUN SRINARMWONG A20501320
#include "database.h"
#include "readfile.h"
#include "employee.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

Employee database[MAX_EMPLOYEES];
int employeeCount = 0;

void printDatabase() {
    char fullName[128]; // Assuming the combined first name and last name won't exceed 99 characters

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
void removeEmployee() {
    if (employeeCount == 0) {
        printf("The database is empty. No employees to remove.\n");
        return;
    }

    int id;
    printf("Enter the employee ID to remove: ");
    scanf("%d", &id);

    int index = -1; // Initialize to an invalid index

    // Find the index of the employee with the given ID
    for (int i = 0; i < employeeCount; i++) {
        if (database[i].id == id) {
            index = i;
            break;
        }
    }

    // If the employee is found
    if (index != -1) {
        char confirm;
        printf("Are you sure you want to remove %s %s? (y) for Yes, (n) for No: ", database[index].first_name, database[index].last_name);
        scanf(" %s", &confirm); // Note the space before %c to skip any whitespace characters

        if (confirm == 'y' || confirm == 'Y') {
            // Shift all elements to the left to fill the hole, if not the last element
            if (index < employeeCount - 1) {
                for (int i = index; i < employeeCount - 1; i++) {
                    database[i] = database[i + 1];
                }
            }
            employeeCount--; // Decrement the count to reflect the removal
            printf("Employee removed successfully.\n");
        } else if (confirm == 'n' || confirm == 'N') {
            printf("Employee removal cancelled.\n");
        } else {
            printf("Invalid confirmation response. Procedure cancelled.\n");
        }
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}
//4 field = id, first_name, last_name, salary
void updateEmployee() {
    // Check if the database is empty
    if (employeeCount == 0) {
        printf("The database is empty. No employees to update.\n");
        return;
    }

    // Prompt user to enter employee ID number
    int id;
    printf("Enter the employee ID to update: ");
    scanf("%d", &id);

    // Search by ID
    Employee* emp = searchByID(id);

    // If found
    if (emp != NULL) {
        printf("Updating employee: %s %s\n", emp->first_name, emp->last_name);

        int newID, newSalary;
        char newFirstName[MAXNAME], newLastName[MAXNAME];

        // Update ID
        printf("Enter new 6 digits ID (or 0 to keep current): ");
        scanf("%d", &newID);
        if (newID != 0) {
            if (newID >= MIN_ID && newID <= MAX_ID) {
                if (searchByID(newID) == NULL) {
                    emp->id = newID;
                } else {
                    printf("Error: ID %d already exists.\n", newID);
                    return;
                }
            } else {
                printf("Error: ID must be 6 digits and within %d and %d.\n", MIN_ID, MAX_ID);
                return;
            }
        }

        // Update first name
        printf("Enter new first name (or '.' to keep current): ");
        scanf("%s", newFirstName);
        if (strcmp(newFirstName, ".") != 0) {
            strncpy(emp->first_name, newFirstName, MAXNAME - 1);
            emp->first_name[MAXNAME - 1] = '\0'; // Ensure null termination
        }

        // Update last name
        printf("Enter new last name (or '.' to keep current): ");
        scanf("%s", newLastName);
        if (strcmp(newLastName, ".") != 0) {
            strncpy(emp->last_name, newLastName, MAXNAME - 1);
            emp->last_name[MAXNAME - 1] = '\0'; // Ensure null termination
        }

        // Update salary
        printf("Enter new salary between %d and %d (or -1 to keep current): ", MIN_SALARY, MAX_SALARY);
        scanf("%d", &newSalary);
        if (newSalary != -1) {
            if (newSalary >= MIN_SALARY && newSalary <= MAX_SALARY) {
                emp->salary = newSalary;
            } else {
                printf("Error: New salary must be between %d and %d.\n", MIN_SALARY, MAX_SALARY);
                return;
            }
        }

        // Print updated employee details
        printf("\nUpdated Employee Details:\n");
        printf("ID: %d | Name: %s %s | Salary: %d\n", emp->id, emp->first_name, emp->last_name, emp->salary);
        printf("Employee updated successfully.\n");

        // Ensure the database is sorted after ID is updated
        sortEmployeesByID();
    } else {
        // Employee not found error
        printf("Employee with ID %d not found.\n", id);
    }
}
void printMEmployeeTopSalaries() {
    if (employeeCount == 0) {
        printf("The database is empty. No salaries to display.\n");
        return;
    }

    int M;
    printf("Enter the number of top salaries to display: ");
    scanf("%d", &M);

    if (M <= 0 || M > employeeCount) {
        printf("Invalid number. Please enter a value between 1 and %d.\n", employeeCount);
        return;
    }

    // Temporary array to store top M employees
    Employee topSalary[M];
    
    // Initialize all salaries in topSalary to 0
    for (int i = 0; i < M; ++i) {
        topSalary[i].salary = 0;
    }

    // Iterate through the database to find the top M salaries
    for (int i = 0; i < employeeCount; ++i) {
        for (int j = 0; j < M; ++j) {
            if (database[i].salary > topSalary[j].salary) {
                // Shift down the list to make room for the higher salary
                for (int k = M - 1; k > j; --k) {
                    topSalary[k] = topSalary[k - 1];
                }
                topSalary[j] = database[i];
                break; // No need to continue checking the rest of topSalary
            }
        }
    }

    // Printing the top M salaries, which are now in descending order
    printf("Top %d Salaries:\n", M);
    for (int i = 0; i < M; ++i) {
        if (topSalary[i].salary > 0) { // Skip if the slot hasn't been filled
            char fullName[128];
             // Combine first name and last name with a space in between
            sprintf(fullName, "%s %s", topSalary[i].first_name, topSalary[i].last_name);

            printf("| Name: %-30s | Salary: %10d | ID: %10d |\n", 
               fullName, 
               topSalary[i].salary, 
               topSalary[i].id);
        }
    }
}
void lookupAllByLastName() {
    //check if the database is empty?
    if (employeeCount == 0) {
        printf("The database is empty. There are no employees to search.\n");
        return;
    }

    //promt for lastname
    char searchLastName[MAXNAME];
    printf("Enter the last name to search for: ");
    scanf("%s", searchLastName);

    //convert the searchLastName[] to lowercase for case-insensitive comparison
    for (int i = 0; searchLastName[i]; i++) {
        searchLastName[i] = tolower(searchLastName[i]);
    }

    //count how many is found
    int found = 0;
    printf("Employees with the last name '%s':\n", searchLastName);
    //loop to search the lastname
    for (int i = 0; i < employeeCount; i++) {
        char currentLastName[MAXNAME];
        //get current last name
        strcpy(currentLastName, database[i].last_name);

        for (int j = 0; currentLastName[j]; j++) {
            currentLastName[j] = tolower(currentLastName[j]);
        }

        if (strcmp(currentLastName, searchLastName) == 0) {
            found = 1; // Set found flag to 1 if at least one employee is found
            
            // Print the details of the employee            
            char fullName[128];
            sprintf(fullName, "%s %s", database[i].first_name, database[i].last_name);
            printf("| Name: %-30s | Salary: %10d | ID: %10d |\n", 
                   fullName, 
                   database[i].salary, 
                   database[i].id);    
        }
    }

    if (!found) {
        printf("No employees found with the last name '%s'.\n", searchLastName);
    }
}
