// Author: Lena Kemmelmeier
// Purpose: CS 219 PA3 (Summer '23)

#include <fstream>
#include <iostream>
#include "assemblyCalculator.h"

#define MAX_OPS 40

int readInstructions(AssemblyCalculator* calcArr, string fileName); // reads in data into calcArr, returns how many instructions total
void runOperations(int numCals, AssemblyCalculator* calcArr); //runs the operations for all the calc objects in calcArr, displays outputs to user

int main(int argc, char* argv[]){ // requires a file argument

    if (argc > 1){ //user must specifiy a file (here, Programming-Project-3.txt)
        AssemblyCalculator calculationsArr[MAX_OPS];
        int numOperations = readInstructions(calculationsArr, argv[1]); //numOperations is the 'size' of our array
        runOperations(numOperations, calculationsArr);

        return 0;
    }
    return 1;
}

void runOperations(int numCals, AssemblyCalculator* calcArr){

    for (int i = 0; i < numCals; i++){

        // for the first object, all the registers and flags are at default value
        if(i == 0){
            calcArr[i].setToDefaultVals();
        }
        else{  // get vals from registers/flags using the previous calcObject in array
            calcArr[i].getStartingVals(calcArr[i-1]);
        }

        string operation = calcArr[i].getCurrentOperation();
        calcArr[i].performCurrentOperation();

        // formatted output
        if(operation == "MOV" || operation == "mov"){
            cout << operation << " " << calcArr[i].getDestReg() << ", #" << hex << showbase << uppercase << calcArr[i].getSecondOperand() << endl;
        }
        else if(operation == "LSR" || operation == "LSRS" || operation == "LSL" || operation == "LSLS" || operation == "lsr" || operation == "lsrs" || operation == "lsl" || operation == "lsls"){
            cout << operation << " " << calcArr[i].getDestReg() << ", " << calcArr[i].getFirstReg() << ", #" << noshowbase << calcArr[i].getSecondOperand() << endl;
        }
        else{
            cout << operation << " " << calcArr[i].getDestReg() << ", " << calcArr[i].getFirstReg() << ", " << calcArr[i].getSecondReg() << endl;
        }

        // // if the instruction ends in an S, set the flags
        // if (operation.back() == 'S'){

        //     // get the MSB
        //     while(result >= 16){
        //         result = result/16;
        //     }
            
        //     // set the N flag if the MSB is 1
        //     if(result > 7){
        //         calcArr[i].setN(1);
        //     }
        //     // set the Z flag if result is 0
        //     else if(result == 0){
        //         calcArr[i].setZ(1);
        //     }
        //     // set the C flag

        //     // set the V flag
        //     if(calcArr[i].getN() || calcArr[i].getC()){
        //         calcArr[i].setV(1);
        //     }
            
        //}

        calcArr[i].displayRegisterVals();
        calcArr[i].displayFlagVals();
    }
}

int readInstructions(AssemblyCalculator* calcArr, string fileName){
    int numOperationsPerform = 0; //will increment as we read in from file - equal to the number of lines/instructions
    string operation, destR, firstR, secondR;
    char buffer; // allows us the skip over '#' and ',' in the txt
    unsigned int oper2;

    ifstream file(fileName);

    if (file.is_open() == false){
        throw "could not find the file";
        return numOperationsPerform;
    }

    while((file >> operation)){ // read in the values from txt, make calc objects and store back into array
        if(operation == "MOV" || operation == "mov"){
            file >> destR >> buffer >> hex >> oper2;
            destR = destR.substr(0, destR.size()-1); // take comma off of destR
            calcArr[numOperationsPerform] = AssemblyCalculator(operation, destR, oper2);
        }
        else if (operation == "lsrs" || operation == "LSRS" || operation == "lsr" || operation == "LRS" || operation == "lsls" || operation == "LSLS" || operation == "lsl" || operation == "LSL"){
            file >> destR >> firstR >> buffer >> oper2;
            destR = destR.substr(0, destR.size()-1); // take comma off of destR
            firstR = firstR.substr(0, firstR.size()-1); // take comma off of firstR
            calcArr[numOperationsPerform] = AssemblyCalculator(operation, destR, firstR, oper2);
        } 
        else{
            file >> destR >> firstR >> secondR;
            destR = destR.substr(0, destR.size()-1); // take comma off of destR
            firstR = firstR.substr(0, firstR.size()-1); // take comma off of firstR
            calcArr[numOperationsPerform] = AssemblyCalculator(operation, destR, firstR, secondR);
        }
        numOperationsPerform++;
    }

    file.close();
    return numOperationsPerform;
}