CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS =  driver.o bank.o truck.o student.o parent.o nameServer.o bottlingPlant.o printer.o config.o vendingMachine.o watCardOffice.o# add object files here
EXEC = soda # executable name

DEPENDS = ${OBJECT:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : clean

${EXEC} : ${OBJECTS}				# link executable
	${CXX} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} 
