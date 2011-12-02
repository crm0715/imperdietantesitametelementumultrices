#include <cstdlib>
#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    prt(prt),
    numVendingMachines(numVendingMachines),
    numStudents(numStudents)
{
    machines = new VendingMachine*[numVendingMachines];
    registeredVMIndex = 0;

    studentsVMMap= new unsigned int[numStudents];
    for (unsigned int i = 0 ; i < numStudents; i++) {
        // assign inital vending machine
        studentsVMMap[i] = i % numVendingMachines;
    } // for
} // NameServer::NameServer

NameServer::~NameServer(){
    delete[] machines;
    delete[] studentsVMMap;
} // NameServer::~NameServer

void NameServer::VMregister( VendingMachine * vendingmachine) {
    previousRegisteredVM = vendingmachine;
} // NameServer::VMregister

VendingMachine* NameServer::getMachine( unsigned int id ) {
    previousStudentID = id;
    return machines[ studentsVMMap[id] ];
} // NameServer::getMachine

VendingMachine** NameServer::getMachineList() {
    return machines;
} // NameServer::getMachineList


void NameServer::main() {
    for ( ;; ) {
        _Accept(~NameServer) {
            break;
        } or _Accept(VMregister) {
            // Bookkeeping after VMregister
            assert(registeredVMIndex < numVendingMachines);
            machines[registeredVMIndex] = previousRegisteredVM;
            registeredVMIndex ++;
        } or _Accept(getMachine) {
            // Bookkepping after getMachine
            assert(previousStudentID < numStudents);
            assert(previousStudentID >= 0);
            studentsVMMap[previousStudentID] = (studentsVMMap[previousStudentID] + 1) % numVendingMachines;
            assert(studentsVMMap[previousStudentID] < numVendingMachines);
            assert(studentsVMMap[previousStudentID] >= 0);
        }
    }
}
