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
        uint32_t secondOperand; // for immediate values
        string firstReg, secondReg, destReg;
        uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
        bool N, Z, C, V;

    public:
        //constructors
        AssemblyCalculator(); //default
        AssemblyCalculator(string newOper, string newDest, string firReg, string secReg); // we have two registers as operands
        AssemblyCalculator(string newOper, string newDest, string firReg, uint32_t newOperand2); // when we have a shift
        AssemblyCalculator(string newOper, string newDest, uint32_t newOperand2); // when we have a move operation
        AssemblyCalculator(string newOper, string firReg, string secReg); // for cmp/tst
    
        // getters + setters
        uint32_t getSecondOperand() const;
        void setSecondOperand(const uint32_t newOperand2);

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
        void setRegisterVal(int whichRegister, const uint32_t newVal);
        uint32_t getRegisterVal(int whichRegister) const;
        string getDestReg() const;
        string getFirstReg() const;
        string getSecondReg() const;
        void displayRegisterVals();

        //misc
        void setToDefaultVals();
        void getStartingVals(const AssemblyCalculator& previousCalc);

        // calculating behaviors
        void performCurrentOperation(); // performs the current operation, ex: calls performLSR()

        uint32_t performADD();
        uint32_t performAND();
        uint32_t performLSR();
        uint32_t performLSL();
        uint32_t performORR();
        uint32_t performSUB();
        uint32_t performXOR();
        void performMOV();
};

#endif