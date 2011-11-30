#ifndef __NAMESERVER_H
#define __NAMESERVER_H

#include <uC++.h>
#include "printer.h"

_Task NameServer {
    Printer &prt;
    unsigned int numVendingMachines;
    unsigned int numStudents;

    VendingMachine **machines;
    unsigned int registeredVMIndex; // used as index to indicate how many VMs registered currently
    int *studentsVMMap; // stores info on which vending machine the student is assigned to

    //Used to pass information to the server
    VendingMachine *previousRegisteredVM;
    unsigned int previousStudentID;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
