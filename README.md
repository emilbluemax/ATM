## ATM Simulator 


+ Terminal based front end
+ File systems are used for the backend data persistence

2 main users - **ADMIN** and **USER**

---

The file names are the account ID of the user <br>
The User file contains 
+ Password
+ Account ID
+ Name of the account holder
+ Balance amount

The Admin file contains
+ Password
+ 100Rs count
+ 500Rs count
+ 2000Rs count

---

+ The file values are stored in global attributes for access throughout the program
+ Admin file is read by default to read the note(2000, 500, 100) counts and store them in global variables - As they will help maintain the money present in the ATM
+ The function choices are driven by a integer switch case which redirects to specific functions based choice values
---

### USER
The main functionalities displayed by the user are : 
+ View account details
  + The global parameters read from the user file are displayed
+ Withdraw Money
  + Ensure that the money requested to withdraw is less than the account balance and the amount present in the atm machine
  + Money withdrawn can be paid in the denominations of 100,500,2000 only. Hence enter appropriate withdrawal amount
  + Deduct the amount requested from the account balance and the atm machine.
  + Display message of success
+ Deposit Money
  + Number of notes of different denominations prompted to enter
  + Ensures number of notes entered >= 0
  + Update the global note count attributes
  + Update the balance of the account
  + Success message displayed
+ Change password/pin
  + Validate the current password/PIN
  + Prompt entry of new PIN on successfull validation of old PIN
  + Success message displayed
+ Quit

A valid Account ID needs to be provided to access the account functionalities
On providing the account ID, the respective account file is read if present - password is obtained on the read and verified to ensure legetimate access.
Password pin is of size 4
The user is given 2 chances to enter the valid ID/valid PIN in case of entering an INVALID ID/PIN, after which the program terminates.

---

### ADMIN
The main functionalities displayed by the Admin are : 
+ View denomination count
  + The global parameters of the note counts are displayed
+ Deposit notes
  + Number of notes of different denominations prompted to enter
  + Ensures number of notes entered >= 0
  + Update the global note count attributes
  + Success message displayed
+ Quit

--- 

+ After all the operations executed, before exiting, all the global attributes are written back to the opened files
+ Message is sent to the user conveying all changes made have been persisted to the files
+ All open files are closed

---

## Executing the ATM Simulator
1. Clone/Download the source code along with the admin and user account files
    + Can create more account files if required following the same format as given in the example files
    + Ensure all the files are in the same location
2. compile the .c file using gcc
3. Run the executable generated
