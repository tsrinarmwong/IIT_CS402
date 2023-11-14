# IIT_CS402
## SP LAB 02 extension of employee database in C
Hello! My name is Thitipun Srinarmwong A20501320.

This assignment extends the previous database I have written. I implemented changes according to the instructions

     1 - Remove Employee
     2 - Update Employee
     3 - Look up M employee(s) with top salaries 
     4 - Look up all employee(s) by last name

Changes are only in database.c and main.c where the database features and menu handling is writen.
The fucntion should be self-explanatory and I also have comments explaining how the code works.

Here's some pseudo drawing about how to remove employees and mainting array. I modified a but more in the actual code but the concept kinda derive from this.
![IMG_3CEE7C690AA2-1](https://github.com/tsrinarmwong/IIT_CS402/assets/125150205/5b37ebaf-bac8-4f7f-9073-ccd1f98ca336)

## SP LAB 01 employee database in C
Hello! My name is Thitipun Srinarmwong A20501320.
The code is for the assignment SP-Lab-1 for IIT course CS402 semester FALL2023.

The code is segmented into 4 parts as follow:
     
     1 - main : where the program is compiled to run and user inputs are mostly handled here
     2 - readfile : where the functions to read the startup file's data and form employee array
     3 - database : where the fucntions to print, search and add employees are declared (also quitting the program)
     4 - employee struct : where the employee information and constrains are declared here

**to run the program please use the compile as follows:**
  `gcc database.c readfile.c main.c -o workerDB`

**And to run the program, please input the text file that contains the data after the executable**
  `./workerDB mediumEmp.txt`

The code are commented and organized. I also include the log file to reference the program behaviour.

### Limitations

     1-Database can only contain 1024 employees.
     2-Database can only contain ID upto 999999. If an attempt to add employee is made when the highest ID is 999999, it will return error.
     3-Printing combines first name and last name and separate them with a space. This is to reflect the requirement from instruction.
     4-Using scanf() may risk buffer overflow from user input... please don't do that.

### Early (Top-down) Design
Here's the early design I skecthed. I designed to write specific functions in specific files. That way I can maintain modularity and is readable.
![workerDB overall design](https://github.com/tsrinarmwong/IIT_CS402/assets/125150205/e461810f-1d9e-4460-9439-d6a2ea64814c)

THANK YOU! XD
