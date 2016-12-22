/*
 *	cpu-stat - a simple program to get CPU stats on Linux
 *
 *	by Davide Coppola - http://www.davidecoppola.com
 *
 *	0.00.01		19-Dec-2016		First basic version.
 *	0.00.02		21-Dec-2016		New code design.
 *	0.00.03		22-Dec-2016		Introduced options.
 *
*/

#include "CPUSnapshot.h"
#include "CPUStatsPrinter.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// -- PROGRAM DATA --
const char * STR_APP_NAME				= "cpp-stat";
const char * STR_APP_VERSION			= "0.00.03";

// -- SHORT OPTIONS --
const char * STR_OPT_ALL				= "-a";
const char * STR_OPT_HELP				= "-h";

// -- LONG OPTIONS --
const char * STR_LONGOPT_ALL			= "--all";
const char * STR_LONGOPT_HELP			= "--help";
const char * STR_LONGOPT_VERSION		= "--version";

void PrintHelp();
void PrintUsage();
void PrintVersion();

int main(int argc, char * argv[])
{
	// -- PARSE OPTIONS --
	bool printAll = false;

	// skip program name
	int index = 1;

	while(index < argc)
	{
		std::string arg(argv[index]);

		if(STR_OPT_ALL == arg || arg == STR_LONGOPT_ALL)
			printAll = true;
		else if(STR_OPT_HELP == arg || STR_LONGOPT_HELP == arg)
		{
			PrintHelp();
			return 0;
		}
		else if(STR_LONGOPT_VERSION == arg)
		{
			PrintVersion();
			return 0;
		}
		else
		{
			PrintUsage();
			return 0;
		}

		++index;
	}

	// -- GET SNAPSHOTS --
	// snapshot 1
	CPUSnapshot s1;

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// snapshot 2
	CPUSnapshot s2;

	// -- PRINT STATS --
	CPUStatsPrinter printer(s1, s2);

	if(printAll)
		printer.PrintActivePercentageAll();
	else
		printer.PrintActivePercentageTotal();

	return 0;
}

void PrintHelp()
{
	PrintUsage();

	const char * STR_LMARGIN = "    ";

	std::cout << std::endl;

	std::cout << "launching the program with no options will print the active time percentage of the total CPU" << std::endl;

	std::cout << std::endl;

	std::cout << "PRINT OPTIONS" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_ALL << " | " << STR_LONGOPT_ALL << "\t\t" << "print active time percentage for all CPUs, starting with total. " << std::endl;

	std::cout << std::endl;

	std::cout << "OTHER OPTIONS" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_HELP << " | " << STR_LONGOPT_HELP << "\t\t" << "print this help." << std::endl;
	std::cout << STR_LMARGIN << STR_LONGOPT_VERSION << "\t\t" << "print the version number" << std::endl;

	std::cout << std::endl;
}

void PrintUsage()
{
	std::cout << "usage: " << STR_APP_NAME << " [" << STR_LONGOPT_VERSION << "] [" << STR_OPT_HELP << " | " << STR_LONGOPT_HELP << "] [" << STR_OPT_ALL << " | " << STR_LONGOPT_ALL << "]" << std::endl;
}

void PrintVersion()
{
	std::cout << STR_APP_NAME << " - version " << STR_APP_VERSION << std::endl;
}
