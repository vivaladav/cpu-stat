#include "CPUStatsPrinter.h"

#include "CPUSnapshot.h"

#include <iostream>

CPUStatsPrinter::CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2)
	: mS1(s1)
	, mS2(s2)
	, mPrecision(2) // default precision
{

}

void CPUStatsPrinter::PrintActivePercentageTotal()
{
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(mPrecision);
	std::cout << GetPercActiveTotal() << std::endl;
}

void CPUStatsPrinter::PrintActivePercentageAll()
{
	// PRINT TOTAL
	PrintActivePercentageTotal();

	// PRINT ALL CPUS
	const unsigned int NUM_ENTRIES = mS1.GetNumEntries();

	for(unsigned int i = 0; i < NUM_ENTRIES; ++i)
	{
		std::cout.setf(std::ios::fixed, std::ios::floatfield);
		std::cout.precision(mPrecision);
		std::cout << GetPercActive(i) << std::endl;
	}
}

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
