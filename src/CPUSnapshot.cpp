#include "CPUSnapshot.h"

#include <fstream>

const int CPUSnapshot::INDEX_TOT = 0;

// == PUBLIC FUNCTIONS ==

CPUSnapshot::CPUSnapshot()
{
	timeTaken = std::chrono::high_resolution_clock::now();

	std::ifstream fileStat("/proc/stat");

	std::string line;

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
		if(CPUData::IsDataCPUStats(line))
		{
			// store entry
			mEntries.emplace_back(CPUData());
			CPUData & entry = mEntries.back();

			entry.ReadData(line);
		}
	}

	fileStat.close();
}

double CPUSnapshot::GetDurationFromConstruct()
{
	auto currentTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms_double = currentTime - timeTaken;

	return ms_double.count();
}

bool CPUSnapshot::didPassDurationFromConstructMs(double durationMs)
{
    return (durationMs > GetDurationFromConstruct()) ;
}

