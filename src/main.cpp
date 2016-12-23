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
#include <stdexcept>
#include <thread>

// -- PROGRAM DATA --
const char * STR_APP_NAME				= "cpp-stat";
const char * STR_APP_VERSION			= "0.00.03";

// -- SHORT OPTIONS --
const char * STR_OPT_ALL				= "-a";
const char * STR_OPT_CPU				= "-c";
const char * STR_OPT_DELAY				= "-d";
const char * STR_OPT_HELP				= "-h";
const char * STR_OPT_PRECISION			= "-p";
const char * STR_OPT_VERBOSE			= "-v";

// -- LONG OPTIONS --
const char * STR_LONGOPT_ALL			= "--all";
const char * STR_LONGOPT_HELP			= "--help";
const char * STR_LONGOPT_VERSION		= "--version";

// -- ERRORS --
const char * STR_ERR					= "ERROR - ";
const char * STR_ERR_PARAM				= "wrong/missing parameter";
const char * STR_ERR_UNKNOWN_OPT		= "unknown option.";

void PrintHelp();
void PrintUsage();
void PrintVersion();

int main(int argc, char * argv[])
{
	// -- PARSE OPTIONS --
	bool optPrintAll = false;

	int optDelay = 100;
	const int MIN_DELAY = 33;

	unsigned int optPrecision = 2;

	bool optVerbose = false;

	int optCPU = -1;

	// skip program name
	int index = 1;

	while(index < argc)
	{
		std::string arg(argv[index]);

		if(STR_OPT_ALL == arg || arg == STR_LONGOPT_ALL)
			optPrintAll = true;
		else if(STR_OPT_DELAY == arg)
		{
			std::string param(argv[++index]);

			try
			{
				optDelay = std::stoi(param);

				if(optDelay < MIN_DELAY)
					optDelay = MIN_DELAY;
			}
			catch(std::logic_error e)
			{
				std::cout << STR_ERR << STR_ERR_PARAM << std::endl;

				PrintUsage();
				return 1;
			}
		}
		else if(STR_OPT_PRECISION == arg)
		{
			std::string param(argv[++index]);

			try
			{
				optPrecision = std::stoi(param);
			}
			catch(std::logic_error e)
			{
				std::cout << STR_ERR << STR_ERR_PARAM << std::endl;

				PrintUsage();
				return 1;
			}
		}
		else if(STR_OPT_CPU == arg)
		{
			std::string param(argv[++index]);

			try
			{
				optCPU = std::stoi(param);
			}
			catch(std::logic_error e)
			{
				std::cout << STR_ERR << STR_ERR_PARAM << std::endl;

				PrintUsage();
				return 1;
			}
		}
		else if(STR_OPT_VERBOSE == arg)
			optVerbose = true;
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
			std::cout << STR_ERR << STR_ERR_UNKNOWN_OPT << std::endl;

			PrintUsage();
			return 1;
		}

		++index;
	}

	// -- GET SNAPSHOTS --
	// snapshot 1
	CPUSnapshot s1;

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(optDelay));

	// snapshot 2
	CPUSnapshot s2;

	// -- PRINT STATS --
	CPUStatsPrinter printer(s1, s2);

	printer.SetPrecision(optPrecision);
	printer.SetVerbose(optVerbose);

	if(optPrintAll)
		printer.PrintActivePercentageAll();
	else if(optCPU >= 0)
		printer.PrintActivePercentageCPU(optCPU);
	else
		printer.PrintActivePercentageTotal();

	return 0;
}

void PrintHelp()
{
	PrintUsage();

	const char * STR_LMARGIN = "    ";

	std::cout << std::endl;

	std::cout << "launching the program with no option will print the active time percentage of the total CPU" << std::endl;

	std::cout << std::endl;

	std::cout << "PRINT OPTIONS" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_ALL << " | " << STR_LONGOPT_ALL << "\t\t" << "print active time percentage for all CPUs, starting with total. " << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_CPU << " <cpu>" << "\t\t" << "print active time percentage only for selected CPU." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_PRECISION << " <precision>" << "\t" << "set the deciaml precision of printed numbers. Default is 2." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_VERBOSE << "\t\t\t" << "enable verbose mode." << std::endl;
	std::cout << std::endl;

	std::cout << "OTHER OPTIONS" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_HELP << " | " << STR_LONGOPT_HELP << "\t\t" << "print this help." << std::endl;
	std::cout << STR_LMARGIN << STR_LONGOPT_VERSION << "\t\t" << "print the version number" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_DELAY << " <time>" << "\t\t" << "set delay time (in ms) between 2 snapshots of CPU data. Default is 100 ms." << std::endl;

	std::cout << std::endl;
}

void PrintUsage()
{
	const char * STR_LMARGIN = "                ";

	std::cout	<< "usage: " << STR_APP_NAME << " [" << STR_LONGOPT_VERSION << "] [" << STR_OPT_HELP << " | " << STR_LONGOPT_HELP
				<< "] [" << STR_OPT_ALL << " | " << STR_LONGOPT_ALL << "] [" << STR_OPT_DELAY << " <time>] ["
				<< STR_OPT_PRECISION << " <precision>]" << std::endl
				<< STR_LMARGIN << "[" << STR_OPT_CPU << " <cpu>] [" << STR_OPT_VERBOSE << "]"
				<< std::endl;
}

void PrintVersion()
{
	std::cout << STR_APP_NAME << " - version " << STR_APP_VERSION << std::endl;
}
