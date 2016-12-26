#include "CPUStatsPrinter.h"

#include "CPUSnapshot.h"

#include <iostream>

const int CPUStatsPrinter::CPU_LABEL_W				= 3;
const int CPUStatsPrinter::STATE_PERC_BASE_W		= 4;

const char * CPUStatsPrinter::STR_STATES[CPUData::NUM_CPU_STATES]	= {	"usr",
																		"sys",
																		"nic",
																		"idl",
																		"iow",
																		"hir",
																		"sir",
																		"ste",
																		"gue",
																		"gun" };


// == PUBLIC FUNCTIONS ==

CPUStatsPrinter::CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2)
	: mS1(s1)
	, mS2(s2)
	, mPrecision(2)
	, mVerbose(false)
{

}

void CPUStatsPrinter::PrintActivePercentageTotal()
{
	if(mVerbose)
		std::cout << mS1.GetLabelTotal() << "] ";

	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(mPrecision);
	std::cout << GetPercActiveTotal();

	if(mVerbose)
		std::cout << "%";

	std::cout << std::endl;
}

void CPUStatsPrinter::PrintActivePercentageCPU(unsigned int cpu)
{
	if(cpu >= mS1.GetNumEntries())
	{
		std::cout << "ERROR - CPU " << cpu << " not available." << std::endl;
		return ;
	}

	if(mVerbose)
	{
		std::cout.width(CPU_LABEL_W);
		std::cout << mS1.GetLabel(cpu) << "] ";
	}

	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(mPrecision);
	std::cout << GetPercActive(cpu);

	if(mVerbose)
		std::cout << "%";

	std::cout << std::endl;
}

void CPUStatsPrinter::PrintActivePercentageAll()
{
	// PRINT TOTAL
	PrintActivePercentageTotal();

	// PRINT ALL CPUS
	const unsigned int NUM_ENTRIES = mS1.GetNumEntries();

	for(unsigned int i = 0; i < NUM_ENTRIES; ++i)
		PrintActivePercentageCPU(i);
}

void CPUStatsPrinter::PrintStatePercentageTotal(unsigned int state)
{
	if(mVerbose)
		std::cout << mS1.GetLabelTotal() << "] ";

	PrintStatePercentageNoLabelTotal(state);

	std::cout << std::endl;
}

void CPUStatsPrinter::PrintStatePercentageCPU(unsigned int state, unsigned int cpu)
{
	if(cpu >= mS1.GetNumEntries())
	{
		std::cout << "ERROR - CPU " << cpu << " not available." << std::endl;
		return ;
	}

	if(mVerbose)
	{
		std::cout.width(CPU_LABEL_W);
		std::cout << mS1.GetLabel(cpu) << "] ";
	}

	PrintStatePercentageNoLabelCPU(state, cpu);

	std::cout << std::endl;
}

void CPUStatsPrinter::PrintStatePercentageAll(unsigned int state)
{
	// PRINT TOTAL
	PrintStatePercentageTotal(state);

	// PRINT ALL CPUS
	const unsigned int NUM_ENTRIES = mS1.GetNumEntries();

	for(unsigned int i = 0; i < NUM_ENTRIES; ++i)
		PrintStatePercentageCPU(state, i);
}

void CPUStatsPrinter::PrintFullStatePercentageTotal()
{
	if(mVerbose)
		std::cout << mS1.GetLabelTotal() << "] ";

	for(int s = 0; s < CPUData::NUM_CPU_STATES; ++s)
	{
		PrintStatePercentageNoLabelTotal(s);
		std::cout << " | ";
	}

	std::cout << std::endl;
}

void CPUStatsPrinter::PrintFullStatePercentageCPU(unsigned int cpu)
{
	if(mVerbose)
	{
		std::cout.width(CPU_LABEL_W);
		std::cout << mS1.GetLabel(cpu) << "] ";
	}

	for(int s = 0; s < CPUData::NUM_CPU_STATES; ++s)
	{
		PrintStatePercentageNoLabelCPU(s, cpu);
		std::cout << " | ";
	}

	std::cout << std::endl;
}

void CPUStatsPrinter::PrintFullStatePercentageAll()
{
	// PRINT TOTAL
	PrintFullStatePercentageTotal();

	// PRINT ALL CPUS
	const unsigned int NUM_ENTRIES = mS1.GetNumEntries();

	for(unsigned int i = 0; i < NUM_ENTRIES; ++i)
		PrintFullStatePercentageCPU(i);
}

// == PRIVATE FUNCTIONS ==

float CPUStatsPrinter::GetPercActiveTotal()
{
	const float ACTIVE_TIME		= mS2.GetActiveTimeTotal() - mS1.GetActiveTimeTotal();
	const float IDLE_TIME		= mS2.GetIdleTimeTotal() - mS1.GetIdleTimeTotal();
	const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

	return 100.f * ACTIVE_TIME / TOTAL_TIME;
}

float CPUStatsPrinter::GetPercActive(unsigned int cpu)
{
	const float ACTIVE_TIME		= mS2.GetActiveTime(cpu) - mS1.GetActiveTime(cpu);
	const float IDLE_TIME		= mS2.GetIdleTime(cpu) - mS1.GetIdleTime(cpu);
	const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

	return 100.f * ACTIVE_TIME / TOTAL_TIME;
}

float CPUStatsPrinter::GetPercStateTotal(unsigned int state)
{
	const float STATE_TIME	= mS2.GetStateTimeTotal(state) - mS1.GetStateTimeTotal(state);
	const float TOTAL_TIME	= mS2.GetTotalTimeTotal() - mS1.GetTotalTimeTotal();

	return 100.f * STATE_TIME / TOTAL_TIME;
}

float CPUStatsPrinter::GetPercState(unsigned int state, unsigned int cpu)
{
	const float STATE_TIME	= mS2.GetStateTime(state, cpu) - mS1.GetStateTime(state, cpu);
	const float TOTAL_TIME	= mS2.GetTotalTime(cpu) - mS1.GetTotalTime(cpu);

	return 100.f * STATE_TIME / TOTAL_TIME;
}

void CPUStatsPrinter::PrintStatePercentageNoLabelTotal(unsigned int state)
{
	if(mVerbose)
	{
		std:: cout << STR_STATES[state] << ": ";
		std::cout.width(STATE_PERC_BASE_W + mPrecision);
	}

	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(mPrecision);
	std::cout << GetPercStateTotal(state);

	if(mVerbose)
		std::cout << "%";
}

void CPUStatsPrinter::PrintStatePercentageNoLabelCPU(unsigned int state, unsigned int cpu)
{
	if(mVerbose)
	{
		std::cout << STR_STATES[state] << ": ";
		std::cout.width(STATE_PERC_BASE_W + mPrecision);
	}

	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(mPrecision);
	std::cout << GetPercState(state, cpu);

	if(mVerbose)
		std::cout << "%";
}
