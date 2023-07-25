// Author: Lena Kemmelmeier
// Purpose: CS 219 PA3 (Summer '23)

#include "assemblyCalculator.h"

AssemblyCalculator::AssemblyCalculator(){ //sets default values
    secondOperand = 12;
    currentOperation = "DEFAULT";
    firstReg = "DEFAULT";
    secondReg = "DEFAULT";
    destReg = "DEFAULT";

    setToDefaultVals();
}

// we have two registers as operands
AssemblyCalculator::AssemblyCalculator(string newOper, string newDest, string firReg, string secReg){
    currentOperation = newOper;
    destReg = newDest;
    firstReg = firReg;
    secondReg = secReg;
}

// when we have a shift
AssemblyCalculator::AssemblyCalculator(string newOper, string newDest, string firReg, uint32_t newOperand2){
    currentOperation = newOper;
    destReg = newDest;
    firstReg = firReg;
    secondOperand = newOperand2;
}

// when we have a move operation
AssemblyCalculator::AssemblyCalculator(string newOper, string newDest, uint32_t newOperand2){
    currentOperation = newOper;
    destReg = newDest;
    secondOperand = newOperand2;
}

// for cmp/tst
AssemblyCalculator::AssemblyCalculator(string newOper, string firReg, string secReg){
    currentOperation = newOper;
    firstReg = firReg;
    secondReg = secReg;
}


// getters + setters
void AssemblyCalculator::setSecondOperand(const uint32_t newOperand2){
    secondOperand = newOperand2;
}

uint32_t AssemblyCalculator::getSecondOperand() const{
    return secondOperand;
}

void AssemblyCalculator::setCurrentOperation(const string newOper){
    currentOperation = newOper;
}

string AssemblyCalculator::getCurrentOperation() const{
    return currentOperation;
}

void AssemblyCalculator::setZ(const bool newZ){
    Z = newZ;
}

bool AssemblyCalculator::getZ() const{
    return Z;
}

void AssemblyCalculator::setN(const bool newN){
    N = newN;
}

bool AssemblyCalculator::getN() const{
    return N;
}

void AssemblyCalculator::setC(const bool newC){
    C = newC;
}

bool AssemblyCalculator::getC() const{
    return C;
}

void AssemblyCalculator::setV(const bool newV){
    V = newV;
}

bool AssemblyCalculator::getV() const{
    return V;
}

void AssemblyCalculator::displayFlagVals(){
    cout << noshowbase << "N = " << N << " Z = " << Z << " C = " << C << " V = " << V << endl;
}

void AssemblyCalculator::setRegisterVal(int whichRegister, const uint32_t newVal){
    switch(whichRegister){
        case 0:
            r0 = newVal;
            break;
        case 1:
            r1 = newVal;
            break;
        case 2:
            r2 = newVal;
            break;
        case 3:
            r3 = newVal;
            break;
        case 4:
            r4 = newVal;
            break;
        case 5:
            r5 = newVal;
            break;
        case 6:
            r6 = newVal;
            break;
        case 7:
            r7 = newVal;
            break;
    }
}

uint32_t AssemblyCalculator::getRegisterVal(int whichRegister) const{
    switch(whichRegister){
        case 0:
            return r0;
        case 1:
            return r1;
        case 2:
            return r2;
        case 3:
            return r3;
        case 4:
            return r4;
        case 5:
            return r5;
        case 6:
            return r6;
        case 7:
            return r7;
        default:
            return 12;
    }
}

string AssemblyCalculator::getDestReg() const{
    return destReg;
}

string AssemblyCalculator::getFirstReg() const{
    return firstReg;
}

string AssemblyCalculator::getSecondReg() const{
    return secondReg;
}

void AssemblyCalculator::displayRegisterVals(){
    cout << showbase << hex << "R0:" << r0 << "  R1:"  << r1 << "  R2:" << r2 << "  R3:" << r3 << endl;
    cout << showbase << hex << "R4:" << r4 << "  R5:"  << r5 << "  R6:" << r6 << "  R7:" << r7 << endl;
}

void AssemblyCalculator::setToDefaultVals(){
    N = 0;
    Z = 0;
    C = 0;
    V = 0;

    r0 = 0;
    r1 = 0;
    r2 = 0;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
}

void AssemblyCalculator::getStartingVals(const AssemblyCalculator& previousCalc){
    N = previousCalc.N;
    Z = previousCalc.Z;
    C = previousCalc.C;
    V = previousCalc.V;

    r0 = previousCalc.r0;
    r1 = previousCalc.r1;
    r2 = previousCalc.r2;
    r3 = previousCalc.r3;
    r4 = previousCalc.r4;
    r5 = previousCalc.r5;
    r6 = previousCalc.r6;
    r7 = previousCalc.r7;
}

// calculating behaviors

// performs the current operation - calls the appropiate behavior
void AssemblyCalculator::performCurrentOperation(){
    string operation = getCurrentOperation(), oper;
    int registerNum = destReg.back() - '0';
    uint32_t result, newResult;

    if (operation.back() == 'S' || operation.back() == 's'){ // treat operation as being the operation without the S
        oper = operation.substr(0, operation.size()-1);
    }
    else{
        oper = operation;
    }

    if(oper == "ADD" || oper == "add"){  
        result = performADD();
    }
    else if(oper == "AND" || oper == "and" || oper == "TST" || oper == "tst"){
        result = performAND();
    }
    else if(oper == "LSR" || oper == "lsr"){
        result = performLSR();
    }
    else if(oper == "LSL" || oper == "lsl"){
        result = performLSL();
    }
    else if (oper == "ORR" || oper == "orr"){
        result = performORR();
    }
    else if (oper == "XOR" || oper == "xor"){
        result = performXOR();
    }
    else if (oper == "SUB" || oper == "sub" || oper == "CMP" || oper == "cmp"){
        result = performSUB();
    }


    if (oper == "MOV" || oper == "mov"){
        performMOV();
    }
    else if(oper !=  "TST" && oper != "tst" && oper != "CMP" && oper != "cmp"){
        setRegisterVal(registerNum, result);
    }



    // if the instruction ends in an S, set the flags
    if (operation.back() == 'S' || operation.back() == 's' || oper == "CMP" || oper == "cmp" || oper == "TST" || oper == "tst"){
        bool affectN = false, affectZ = false, affectC = false, affectV = false;

        if(oper == "ADD" || oper == "add" || oper == "SUB" || oper == "sub" || oper == "cmp" || oper == "CMP"){
            affectN = true;
            affectZ = true;
            affectC = true;
            affectV = true;
        }
        else if(oper == "AND" || oper == "and" || oper == "orr" || oper == "ORR" || oper == "tst" || oper == "TST" || oper == "XOR" || oper == "xor"){
            affectN = true;
            affectZ = true;
        }
        else{ // lsr or lsl
            affectN = true;
            affectZ = true;
            affectC = true;
        }

        if(affectN){
            // get the MSB
            newResult = result;
            while(newResult >= 16){
                newResult = newResult/16;
            }

            // set the N flag if the MSB is 1
            if(newResult > 7){
                N = 1;
            }
            else{
                N = 0;
            }
        }

        if(affectZ){
            // set the Z flag if result is 0
            if(result == 0){
                Z = 1;
            }
            else{
                Z = 0;
            }
        }

        if(affectC){
            if(oper == "LSL" || oper == "lsl"){
                if(result < getRegisterVal(firstReg.back() - '0')){
                    C = 1;
                }
                else{
                    C = 0;
                }
            }

             if(oper == "LSR" || oper == "lsr"){
                if(result < getRegisterVal(firstReg.back() - '0')){
                    C = 1;
                }
                else{
                    C = 0;
                }
            }     

            if(oper == "SUB" || oper == "sub" || oper == "CMP" || oper == "cmp"){
                if(getRegisterVal(firstReg.back() - '0') > getRegisterVal(secondReg.back() - '0')){
                    C = 1;
                }
                else{
                    C = 0;
                }      
            }

            if(oper == "ADD" || oper == "add"){
                if(getRegisterVal(firstReg.back() - '0') > result || getRegisterVal(secondReg.back() - '0') > result){
                    C = 1;
                }
                else{
                    C = 0;
                }        
            }      
        }

        if(affectV){
            //set the V flag
            if(oper == "CMP" || oper == "cmp" || oper == "tst" || oper == "TST"){
                if(C){
                    V = 0;
                }
            }
            else if(N || C){
                V = 1;
            }
            else{
                V = 0;
            }
        }
    }
}

uint32_t AssemblyCalculator::performADD(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) + getRegisterVal(secRegNum);
}

uint32_t AssemblyCalculator::performAND(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) & getRegisterVal(secRegNum);
}

uint32_t AssemblyCalculator::performLSR(){
    int firstRegNum = firstReg.back() - '0';
    int numShifts = secondOperand;

    return getRegisterVal(firstRegNum) >> numShifts;
}

uint32_t AssemblyCalculator::performLSL(){
    int firstRegNum = firstReg.back() - '0';
    int numShifts = secondOperand;

    return getRegisterVal(firstRegNum) << numShifts;
}

uint32_t AssemblyCalculator::performORR(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) | getRegisterVal(secRegNum);
}

uint32_t AssemblyCalculator::performSUB(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) - getRegisterVal(secRegNum);
}

uint32_t AssemblyCalculator::performXOR(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) ^ getRegisterVal(secRegNum);
}

void AssemblyCalculator::performMOV(){
    int registerNum = destReg.back() - '0';
    setRegisterVal(registerNum, secondOperand);
}