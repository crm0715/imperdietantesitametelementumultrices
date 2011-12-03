#ifndef __PRINTER_H
#define __PRINTER_H

#include <uC++.h>
#include <vector>

_Monitor Printer {
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );

  private:
	struct Buffer {
		bool override;
		char state;
		int val1;
		int val2;
	};
	std::vector<Buffer> buffers;
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	unsigned int total;

	void flushBuffer ( bool finished );
	void printHelper ( Kind kind, unsigned int lid, char state, int val1, int val2);
	int getId ( Kind kind, unsigned int id );
};

#endif
