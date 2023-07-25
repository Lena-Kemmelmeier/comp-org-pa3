// Author: Lena Kemmelmeier
// Purpose: CS 219 PA3 (Summer '23)

#ifndef ASSEMBLY_CALCULATOR
#define ASSEMBLY_CALCULATOR

#include <iostream>
#include <string>
using namespace std;

class AssemblyCalculator{
    private:
        string currentOperation;
        unsigned int secondOperand; // for immediate values
        string firstReg, secondReg, destReg;
        unsigned int r0, r1, r2, r3, r4, r5, r6, r7;
        bool N, Z, C, V;

    public:
        //constructors
        AssemblyCalculator(); //default
        AssemblyCalculator(string newOper, string newDest, string firReg, string secReg); // we have two registers as operands
        AssemblyCalculator(string newOper, string newDest, string firReg, unsigned int newOperand2); // when we have a shift
        AssemblyCalculator(string newOper, string newDest, unsigned int newOperand2); // when we have a move operation
    
        // getters + setters
        unsigned int getSecondOperand() const;
        void setSecondOperand(const unsigned int newOperand2);

        void setCurrentOperation(const string newOper);
        string getCurrentOperation() const;

        // flags
        void setZ(const bool newZ);
        bool getZ() const;
        void setN(const bool newN);
        bool getN() const;
        void setC(const bool newC);
        bool getC() const;
        void setV(const bool newV);
        bool getV() const;
        void displayFlagVals();

        //registers
        void setRegisterVal(int whichRegister, const unsigned int newVal);
        unsigned int getRegisterVal(int whichRegister) const;
        string getDestReg() const;
        string getFirstReg() const;
        string getSecondReg() const;
        void displayRegisterVals();

        //misc
        void setToDefaultVals();
        void getStartingVals(const AssemblyCalculator& previousCalc);

        // calculating behaviors
        void performCurrentOperation(); // performs the current operation, ex: calls performLSR()

        unsigned int performADD();
        unsigned int performAND();
        unsigned int performLSR();
        unsigned int performLSL();
        unsigned int performORR();
        unsigned int performSUB();
        unsigned int performXOR();
        void performMOV();

        bool isThereOverFlow();
};

#endif