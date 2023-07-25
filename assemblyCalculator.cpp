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
AssemblyCalculator::AssemblyCalculator(string newOper, string newDest, string firReg, unsigned int newOperand2){
    currentOperation = newOper;
    destReg = newDest;
    firstReg = firReg;
    secondOperand = newOperand2;
}

// when we have a move operation
AssemblyCalculator::AssemblyCalculator(string newOper, string newDest, unsigned int newOperand2){
    currentOperation = newOper;
    destReg = newDest;
    secondOperand = newOperand2;
}


// getters + setters
void AssemblyCalculator::setSecondOperand(const unsigned int newOperand2){
    secondOperand = newOperand2;
}

unsigned int AssemblyCalculator::getSecondOperand() const{
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

void AssemblyCalculator::setRegisterVal(int whichRegister, const unsigned int newVal){
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

unsigned int AssemblyCalculator::getRegisterVal(int whichRegister) const{
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
    string operation = getCurrentOperation();
    int registerNum = destReg.back() - '0';

    if (operation.back() == 'S' || operation.back() == 's'){ // treat operation as being the operation without the S
        operation = operation.substr(0, operation.size()-1);
    }

    if(operation == "ADD" || operation == "add"){  
        setRegisterVal(registerNum, performADD());
    }
    else if(operation == "AND" || operation == "and"){
        setRegisterVal(registerNum, performAND());
    }
    else if(operation == "LSR" || operation == "lsr"){
        setRegisterVal(registerNum, performLSR());
    }
    else if(operation == "LSL" || operation == "lsl"){
        setRegisterVal(registerNum, performLSL());
    }
    else if (operation == "ORR" || operation == "orr"){
        setRegisterVal(registerNum, performORR());
    }
    else if (operation == "XOR" || operation == "xor"){
        setRegisterVal(registerNum, performXOR());
    }
    else if (operation == "SUB" || operation == "sub"){
        setRegisterVal(registerNum, performSUB());
    }
    else if (operation == "MOV" || operation == "mov"){
        performMOV();
    }
}

unsigned int AssemblyCalculator::performADD(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) + getRegisterVal(secRegNum);
}

unsigned int AssemblyCalculator::performAND(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) & getRegisterVal(secRegNum);
}

unsigned int AssemblyCalculator::performLSR(){
    int firstRegNum = firstReg.back() - '0';
    int numShifts = secondOperand;

    cout << "first register num: " << firstRegNum << endl;
    cout << "number of shifts: " << numShifts << endl;

    return getRegisterVal(firstRegNum) >> numShifts;
}

unsigned int AssemblyCalculator::performLSL(){
    int firstRegNum = firstReg.back() - '0';
    int numShifts = secondOperand;

    return getRegisterVal(firstRegNum) << numShifts;
}

unsigned int AssemblyCalculator::performORR(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) | getRegisterVal(secRegNum);
}

unsigned int AssemblyCalculator::performSUB(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) - getRegisterVal(secRegNum);
}

unsigned int AssemblyCalculator::performXOR(){
    int firstRegNum = firstReg.back() - '0';
    int secRegNum = secondReg.back() - '0';

    return getRegisterVal(firstRegNum) ^ getRegisterVal(secRegNum);
}

void AssemblyCalculator::performMOV(){
    int registerNum = destReg.back() - '0';
    setRegisterVal(registerNum, secondOperand);
}

// // checking for overflow with performADD()
// bool AssemblyCalculator::isThereOverFlow(){
//     bool hasOverflowOccured = false;
//     unsigned int sum = performADD();

//     // if the sum result is less than either of the two operands (unsigned), then overflow has occured
//     if (sum < firstOperand || sum < secondOperand){
//         return hasOverflowOccured = true;
//     }
//     return hasOverflowOccured;
// }