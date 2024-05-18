/*
 *	cpu-stat - a simple program to get CPU stats on Linux
 *
 *	by Davide Coppola - http://www.davidecoppola.com
 *
 *	0.00.01		19-Dec-2016		First basic version.
 *	0.00.02		21-Dec-2016		New code design.
 *	0.00.03		22-Dec-2016		Introduced options.
 *	0.01.00		25-Dec-2016		Implemented all basic features.
 *	0.01.01		25-Dec-2016		Introduced OptionsParser and code polishing.
 *	0.01.02		27-Dec-2016		Added scons build system.
 *
*/

#include "CPUSnapshot.h"
#include "CPUStatsPrinter.h"
#include "OptionsParser.h"
#include "CPUStat.h"

#include <chrono>
#include <thread>
#include <iostream>

// -- PROGRAM DATA --
const char * STR_APP_NAME			= "cpu-stat";
const char * STR_APP_VERSION			= "0.01.02";

int main(int argc, char * argv[])
{
	// -- PARSE OPTIONS --
	OptionsParser options(argc, argv, STR_APP_NAME, STR_APP_VERSION);

	// exit after error
	if(options.HasError())
		return options.GetErrorCode();

	// exit after printing help or version
	if(options.ExitRequested())
		return 0;

	CPUStat cpuStat;

	// -- GET SNAPSHOTS --
	// snapshot 1
	CPUSnapshot s1;

	// pause
	std::this_thread::sleep_for(std::chrono::milliseconds(options.GetOptionDelay())	);

	// snapshot 2
	CPUSnapshot s2;

	std::cout << cpuStat.GetActivePercentageCPU(4,5) << std::endl;

	return 0;

	// -- PRINT STATS --
	CPUStatsPrinter printer(s1, s2);

	printer.SetPrecision(options.GetOptionPrecision());
	printer.SetVerbose(options.GetOptionVerbose());

	if(options.GetOptionPrintAll())
	{
		if(options.GetOptionFull())
			printer.PrintFullStatePercentageAll();
		else if(options.GetOptionState() >= 0)
			printer.PrintStatePercentageAll(options.GetOptionState());
		else
			printer.PrintActivePercentageAll();
	}
	else if(options.GetOptionCPU() >= 0)
	{
		if(options.GetOptionFull())
			printer.PrintFullStatePercentageCPU(options.GetOptionCPU());
		else if(options.GetOptionState() >= 0)
			printer.PrintStatePercentageCPU(options.GetOptionState(), options.GetOptionCPU());
		else
			printer.PrintActivePercentageCPU(options.GetOptionCPU());
			std::cout << "GetActivePercentageCPU:" << printer.GetActivePercentageCPU(options.GetOptionCPU()) << std::endl;

	}
	else
	{
		if(options.GetOptionFull())
			printer.PrintFullStatePercentageTotal();
		else if(options.GetOptionState() >= 0)
			printer.PrintStatePercentageTotal(options.GetOptionState());
		else
			printer.PrintActivePercentageTotal();
	}

	return 0;
}
