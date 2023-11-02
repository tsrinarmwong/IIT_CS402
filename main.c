#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "employee.h"
#include "readfile.h"

void displayMenu();
void handleUserSelection(int choice);
void quitProgram();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./workerDB <filename>\n");
        return 1; // Return an error code
    }

    const char* filename = argv[1];

    if (open_file(filename) == 0) {
        printf("File %s opened and read successfully.\n", filename);
        
        int choice;
        do { //loop until quit is called
            displayMenu();
            scanf("%d", &choice);
            handleUserSelection(choice);
        } while (choice != 5);
        
    } else {
        printf("Error opening or reading the file %s.\n", filename);
    }

    return 0;
}

void displayMenu() {
    printf("\nDatabase Menu:\n");
    printf("1. Print the Database\n");
    printf("2. Lookup employee by ID\n");
    printf("3. Lookup employee by last name\n");
    printf("4. Add an Employee\n");
    printf("5. Quit\n");
    printf("Enter your choice: ");
}

void handleUserSelection(int choice) {
    switch (choice) {
        case 1:
            printDatabase();
            break;
        case 2: 
            lookupByID();
            break;
        case 3:
            lookupByLastName();
            break;
        case 4:
            addEmployee();
            break;
        case 5:
            quitProgram();
            break;
        default:
            printf("%d is invalid. Please try again.\n", choice);
            break;
    }
}