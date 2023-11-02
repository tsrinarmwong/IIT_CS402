# IIT_CS402
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
_1-Database can only contain 1024 employees._

2-Database can only contain ID upto 999999. If an attempt to add employee is made when the highest ID is 999999, it will return error.

3-Printing combines first name and last name and separate them with a space. This is to reflect the requirement from instruction.

THANK YOU! XD
