assemblySim: driver.o assemblyCalculator.o
	g++ driver.o assemblyCalculator.o -o assemblySim
driver.o: driver.cpp assemblyCalculator.h
	g++ -c driver.cpp
assemblyCalculator.o: assemblyCalculator.cpp assemblyCalculator.h
	g++ -c assemblyCalculator.cpp
clean:
	rm *.o assemblySim