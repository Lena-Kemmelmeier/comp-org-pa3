# Computer Organization Assignment 3

Required Files: driver.cpp, assemblyCalculator.cpp, assemblyCalculator.h, Programming-Project-3.txt, makefile (for the assemblySim executable)


Main Overview: To run, first try ./assemblySim Programming-Project-3.txt. If that does not work, run the make clean command, then the make command and try again-- make sure that the txt file is spelled correctly.

The program works by reading the data from Programming-Project-3.txt with ifstream and storing data (operation names and operands) into assemblyCalculator objects.  Each assemblyCalculator object is stored in the calculationsArr (an assemblyCalculator array) for constant-time access later. This is done with the readInstructions() function in the driver, which conveniently returns the number of instructions to run later. Since part 2, I have edited it so that, depending on the type of instruction, a different parameterized constructor creates the assemblyCalculator object to add to the array. This was easier than having just one parameterized constructor, especially since some OPCODE do not require an immediate operand, a destination register, etc., while some do. I have also included registers and register behaviors in my assemblyCalculator class. This was more intuitive to me than creating another class or working with variables in main for the registers. 

We run and display the results of each operation with the runOperations() function, which displays the OPCODE, and any relevant registers/immediate operands. runOperations() calls the performCurrentOperation() method in assemblyCalculator, which runs the appropiate instruction currentOperation on each assemblyCalculator and sets the value of any affected registers (the destination register, if applicable) and any affected flags. The changes in the values for the registers and flags are preserved because of this function (and its use of the copy constructor) -- each new assemblyCalculator object is a copy of the previous one in the array after its calculations have been completed.

Unlike part 2, we are dealing with OPCODE with registers and more flag values. I treated all values of operands and registers as uint_32, per the suggestion in the assignment description. To make the bitwise operations a bit easier for me to handle, I typecasted the hex values as unsigned integers and just converted them back to hex for when I had to display the results back to the user.



FROM PART 2 (this was required then):

Command Breakdown (methods in assemblyCalculator.cpp):

performADD: adds operand1 and operand2 (unsigned) in a bitwise fashion (if either or both of bits are 1, resulting bit is 1; otherwise resulting bit is 0 -- also has carry) with +, returns sum (unsigned)

performAND: 'ands' operand1 and operand2 (unsigned) in a bitwise fashion (if both of the bits are 1, resulting but is 1; otherwise resulting bit is 0) with &, return result (unsigned)

performASR: arithmetically shifts operand 1 (signed) over right n times (operand2, int) (each bit is shifted to right by 1 and LSB bit is tossed out, MSB is filled w/ previous MSB) with >>, returns result (signed)

performLSR: logically shifts operand 1 (signed) over right n times (operand2, int) (each bit is shifted to right by 1 and LSB bit is tossed out, MSB is filled w/ 0) with >>, returns result (unsigned)

performLSL: logically shifts operand 1 (signed) over left n times (operand2, int) (each bit is shifted to left by 1 and MSB bit is tossed out, LSB is filled w/ 0) with <<, returns result (unsigned)

performNOT: 'nots' operand1 (unsigned) in a bitwise fashion (if a bit 0 is, then the resulting bit is 1, and vice versa) with ~, returns result (unsigned)

performORR: performs a bitwie OR oepration on operand1 and operand2 (unsigned) (if either of a certain bit or both are 1, then the resulting bit is 1) with |, returns result (unsigned)

performSUB: subtracts operand2 from operand1 (unsigned) in a bitwise fashion (just the reverse of adding) with -, returns result (unsigned)

performXOR: performs a bitwie XOR oepration on operand1 and operand2 (unsigned) (if either of a certain bit are 1 (exclusively one), then the resulting bit is 1) with ^, returns result (unsigned)



Changing N and Z flags (implemented in driver):

If the result (in hex) of an operation has an MSB greater than 7 (8-0), then it is negative and the N flag is set. If the result is equal to 0, then the result in zero and the Z flag is set. The N and Z flags are attributes of assemblyCalculator, and are accessible via getters and setters. N and Z flags are 0 by default for each instance of assemblyCalculator.
