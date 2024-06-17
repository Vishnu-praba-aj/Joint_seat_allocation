<a name="br1"></a> 

**SOFTWARE SYSTEM FOR ENGINEERING JOINT SEAT**

**ALLOCATION**

**UCS2201 – Fundamentals and Practice of Software**

**Development**

**TEAM NUMBER: 8**

**TEAM MEMBERS:**

• Sweety Y 3122 22 5001 146

• Varsha G 3122 22 5001 152

• Vishnu Praba A J 3122 22 5001 164

• Yuvapriya N 3122 22 5001 167



Our Engineering Joint Seat Allocation System consists of several

modules, each serving a specific purpose, and they are linked together

to implement the overall functionality of student and college

preference filling, allocation, and display. Here's how the modules are

linked in the code:



**Main Module:** The main module is the entry point of the program. It

initializes variables and arrays, reads data from

*"studentpreference.txt"* and *"college.txt"* files into corresponding

arrays (studentarr and collegearr). It then enters a loop for stable

matching to allocate students to colleges.

**File-based Data Storage Module:** This module is responsible for

handling file-based data storage. It defines functions like

no\_of\_students(), check\_password(), is\_present(), and

check\_advanced() to read data from different files and check

information like the number of students, student passwords, program

presence, and JEE Advanced status.



<a name="br2"></a> 

**Student Login Module:** This module handles the student login

process. It starts by reading the student's name and password as input.

It then verifies the entered credentials using check\_password() from

the File-based Data Storage Module. If the credentials are correct, it

checks if the student has already given preferences by checking the

*"studentpreference.txt"* file. If not, it prompts the student to choose

between preference filling and allocation. Based on the choice, it

either allows the student to enter preferences and stores them in the

file or displays the allocated program using

display\_alloted\_program().



**College Login Module:** This module is responsible for the college

login process. It reads the college name from the user and then opens

the *"college\_allotment.txt"* file to fetch college information and

assigned students. It iterates through the colleges, compares the

entered college name, and displays the corresponding college's

information along with the assigned students.

**Writing Data Module:** This module includes functions like

write\_clg() and display\_alloted\_program() to write data to files.

write\_clg() writes the allocated program information to the console,

and display\_alloted\_program() reads the *"Allotment.txt"* file to display

the allocated program for a given student.




**COMPILATION OF MODULES:**

The main module reads data from files into arrays.

It enters a loop for stable matching to allocate students to colleges.



<a name="br3"></a> 

During the stable matching process, the main module calls the Student

Login Module for each unassigned student to allow them to fill

preferences or view the allocated program.

The Student Login Module uses functions from the File-based Data

Storage Module to check student credentials, preferences, and JEE

Advanced status.

If a student chooses to fill preferences, the preferences are written to

the "studentpreference.txt" file using the Writing Data Module.

If a student chooses to view the allocated program, the College Login

Module is called to display the assigned students for the chosen

college.

This way, the modules work together to create a system where

students can log in, fill preferences, get allocated programs, and

colleges can log in to see assigned students. The data is stored and

retrieved using file-based storage operations, simulating a basic

database system. However, this approach has limitations in terms of

scalability and data consistency compared to dedicated

database systems.


