/*
 *	cpu-stat - a simple program to get CPU stats on Linux
 *
 *	by Davide Coppola - http://www.davidecoppola.com
 *
 *	0.00.01		19-Dec-2016		First basic version.
 *	0.00.02		21-Dec-2016		New code design.
 *
*/

#include "CPUSnapshot.h"
#include "CPUStatsPrinter.h"

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char * argv[])
{
	// snapshot 1
	CPUSnapshot s1;

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// snapshot 2
	CPUSnapshot s2;

	// -- PRINT STATS --
	CPUStatsPrinter printer(s1, s2);

	// print active percentage of tot
	printer.PrintActivePercentageTotal();

	return 0;
}
