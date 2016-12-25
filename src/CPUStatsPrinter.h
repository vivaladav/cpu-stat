#pragma once

// CPUStatsPrinter - object which prints stats extracted by 2 CPUSnapshots.

#include "CPUData.h"

class CPUSnapshot;

class CPUStatsPrinter
{
public:
	CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2);

	void PrintActivePercentageTotal();
	void PrintActivePercentageCPU(unsigned int cpu);
	void PrintActivePercentageAll();

	void PrintStatePercentageTotal(unsigned int state);
	void PrintStatePercentageCPU(unsigned int state, unsigned int cpu);
	void PrintStatePercentageAll(unsigned int state);

	void PrintFullStatePercentageTotal();
	void PrintFullStatePercentageCPU(unsigned int cpu);
	void PrintFullStatePercentageAll();

	void SetPrecision(unsigned int prec);

	void SetVerbose(bool val);

private:
	float GetPercActiveTotal();
	float GetPercActive(unsigned int cpu);

	float GetPercStateTotal(unsigned int state);
	float GetPercState(unsigned int state, unsigned int cpu);

	void PrintStatePercentageNoLabelTotal(unsigned int state);
	void PrintStatePercentageNoLabelCPU(unsigned int state, unsigned int cpu);

private:
	static const int CPU_LABEL_W;
	static const int STATE_PERC_BASE_W;

	static const char * STR_STATES[CPUData::NUM_CPU_STATES];

private:
	const CPUSnapshot & mS1;
	const CPUSnapshot & mS2;

	unsigned int mPrecision;

	bool mVerbose;
};

// == INLINE FUNCTIONS ==

inline void CPUStatsPrinter::SetPrecision(unsigned int prec) { mPrecision = prec; }

inline void CPUStatsPrinter::SetVerbose(bool val) { mVerbose = val; }
