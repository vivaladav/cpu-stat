#pragma once

// CPUSnapshot - a snapshot of all the CPU data from /proc/stat at a given time

#include "CPUData.h"

#include <vector>

class CPUSnapshot
{
public:
	CPUSnapshot();

	std::size_t GetNumEntries() const;

	const char * GetLabelTotal() const;
	const char * GetLabel(unsigned int cpu) const;

	std::size_t GetActiveTimeTotal() const;
	std::size_t GetActiveTime(unsigned int cpu) const;

	std::size_t GetIdleTimeTotal() const;
	std::size_t GetIdleTime(unsigned int cpu) const;

private:
	std::vector<CPUData> mEntries;

	int mIndexTot;
};

inline std::size_t CPUSnapshot::GetNumEntries() const { return mEntries.size(); }

inline const char * CPUSnapshot::GetLabelTotal() const { return mEntries[mIndexTot].GetLabel().c_str(); }

inline const char * CPUSnapshot::GetLabel(unsigned int cpu) const
{
	if(cpu < mEntries.size())
		return mEntries[cpu].GetLabel().c_str();
	else
		return nullptr;
}

inline std::size_t CPUSnapshot::GetActiveTimeTotal() const { return mEntries[mIndexTot].GetActiveTime(); }

inline std::size_t CPUSnapshot::GetActiveTime(unsigned int cpu) const 
{ 
	if(cpu < mEntries.size())
		return mEntries[cpu].GetActiveTime();
	else
		return 0;
}

inline std::size_t CPUSnapshot::GetIdleTimeTotal() const { return mEntries[mIndexTot].GetIdleTime(); }

inline std::size_t CPUSnapshot::GetIdleTime(unsigned int cpu) const
{ 
	if(cpu < mEntries.size())
		return mEntries[cpu].GetIdleTime();
	else
		return 0;
}

