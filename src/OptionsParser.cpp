#include "OptionsParser.h"

#include <iostream>
#include <string>
#include <stdexcept>

// -- SHORT OPTIONS --
const char * OptionsParser::STR_OPT_ALL				= "-a";
const char * OptionsParser::STR_OPT_CPU				= "-c";
const char * OptionsParser::STR_OPT_DELAY			= "-d";
const char * OptionsParser::STR_OPT_FULL			= "-f";
const char * OptionsParser::STR_OPT_HELP			= "-h";
const char * OptionsParser::STR_OPT_PRECISION		= "-p";
const char * OptionsParser::STR_OPT_STATE			= "-s";
const char * OptionsParser::STR_OPT_VERBOSE			= "-v";

// -- LONG OPTIONS --
const char * OptionsParser::STR_LONGOPT_ALL			= "--all";
const char * OptionsParser::STR_LONGOPT_FULL		= "--full-state";
const char * OptionsParser::STR_LONGOPT_HELP		= "--help";
const char * OptionsParser::STR_LONGOPT_VERBOSE		= "--verbose";
const char * OptionsParser::STR_LONGOPT_VERSION		= "--version";

// -- ERRORS --
const int OptionsParser::NO_ERROR					= 0;
const int OptionsParser::ERR_PARAM					= 1;
const int OptionsParser::ERR_UNKNOWN_OPT			= 2;

const char * OptionsParser::STR_ERR					= "ERROR - ";
const char * OptionsParser::STR_ERR_PARAM			= "wrong/missing parameter";
const char * OptionsParser::STR_ERR_UNKNOWN_OPT		= "unknown option.";

const int OptionsParser::MIN_DELAY = 33;

// == PUBLIC FUNCTIONS ==

OptionsParser::OptionsParser(int argc, char * argv[], const char * appName, const char * version)
	: mAppName(appName)
	, mVersion(version)
	, mError(OptionsParser::NO_ERROR)
	, optCPU(-1)
	, optDelay(100)
	, optState(-1)
	, optPrecision(2)
	, optFull(false)
	, optPrintAll(false)
	, optVerbose(false)
	, mExit(false)
{
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

				mError = ERR_PARAM;

				break;
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

				mError = ERR_PARAM;

				break;
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

				mError = ERR_PARAM;

				break;
			}
		}
		else if(STR_OPT_STATE == arg)
		{
			std::string param(argv[++index]);

			try
			{
				optState = std::stoi(param);
			}
			catch(std::logic_error e)
			{
				std::cout << STR_ERR << STR_ERR_PARAM << std::endl;

				PrintUsage();

				mError = ERR_PARAM;

				break;
			}
		}
		else if(STR_OPT_VERBOSE == arg || STR_LONGOPT_VERBOSE == arg)
			optVerbose = true;
		else if(STR_OPT_FULL == arg || STR_LONGOPT_FULL == arg)
			optFull = true;
		else if(STR_OPT_HELP == arg || STR_LONGOPT_HELP == arg)
		{
			PrintHelp();

			mExit = true;

			break;
		}
		else if(STR_LONGOPT_VERSION == arg)
		{
			PrintVersion();

			mExit = true;

			break;
		}
		else
		{
			std::cout << STR_ERR << STR_ERR_UNKNOWN_OPT << std::endl;

			PrintUsage();

			mError = ERR_UNKNOWN_OPT;

			break;
		}

		++index;
	}
}

// == PRIVATE FUNCTIONS ==

void OptionsParser::PrintHelp()
{
	PrintUsage();

	const char * STR_LMARGIN = "    ";

	std::cout << std::endl;

	std::cout << "launching the program with no option will print the active time percentage of the total CPU." << std::endl;

	std::cout << std::endl;

	std::cout << "PRINT OPTIONS" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_ALL << " | " << STR_LONGOPT_ALL << "\t\t" << "print active time percentage for all CPUs, starting with total. " << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_CPU << " <cpu>" << "\t\t" << "print stats only for selected CPU." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_FULL << " | " << STR_LONGOPT_FULL << "\t" << "print time percentage of all states." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_PRECISION << " <precision>" << "\t" << "set the decimal precision of printed numbers. Default is 2." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_STATE << " <state>" << "\t\t" << "print time percentage for specific state [0-9]." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_VERBOSE << " | " << STR_LONGOPT_VERBOSE << "\t" << "enable verbose mode." << std::endl;
	std::cout << std::endl;

	std::cout << "OTHER OPTIONS" << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_DELAY << " <time>" << "\t\t" << "set delay time (in ms) between 2 snapshots of CPU data. Default is 100 ms." << std::endl;
	std::cout << STR_LMARGIN << STR_OPT_HELP << " | " << STR_LONGOPT_HELP << "\t\t" << "print this help." << std::endl;
	std::cout << STR_LMARGIN << STR_LONGOPT_VERSION << "\t\t" << "print the version number." << std::endl;

	std::cout << std::endl;
}

void OptionsParser::PrintUsage()
{
	const char * STR_LMARGIN = "                ";

	std::cout	<< "usage: " << mAppName << " [" << STR_LONGOPT_VERSION << "] [" << STR_OPT_HELP << " | " << STR_LONGOPT_HELP
				<< "] [" << STR_OPT_ALL << " | " << STR_LONGOPT_ALL << "] [" << STR_OPT_DELAY << " <time>] ["
				<< STR_OPT_PRECISION << " <precision>]" << std::endl
				<< STR_LMARGIN << "[" << STR_OPT_CPU << " <cpu>] [" << STR_OPT_FULL << " | " << STR_LONGOPT_FULL << "] ["
				<< STR_OPT_VERBOSE << " | " << STR_LONGOPT_VERBOSE << "] [" << STR_OPT_STATE << " <state>]"
				<< std::endl;
}

void OptionsParser::PrintVersion()
{
	std::cout << mAppName << " - version " << mVersion << std::endl;
}
