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
    prt.print(Printer::NameServer, 'S');
    for ( ;; ) {
        _Accept(~NameServer) {
            break;
        } or _Accept(VMregister) {
            // Book keeping
            assert(registeredVMIndex < numVendingMachines);

            prt.print(Printer::NameServer, 'R', previousRegisteredVM->getId());
            machines[registeredVMIndex] = previousRegisteredVM;
            registeredVMIndex ++;
        } or _Accept(getMachine) {
            // Book kepping
            assert(previousStudentID < numStudents);
            assert(previousStudentID >= 0);

            prt.print(Printer::NameServer, 'N', previousStudentID, machines[studentsVMMap[previousStudentID]]->getId());
            // assign student to the next vending machine in the list
            studentsVMMap[previousStudentID] = (studentsVMMap[previousStudentID] + 1) % numVendingMachines;

            assert(studentsVMMap[previousStudentID] < numVendingMachines);
            assert(studentsVMMap[previousStudentID] >= 0);
        } or _Accept(getMachineList) {
		} //Accept
    }
    prt.print(Printer::NameServer, 'F');
}
