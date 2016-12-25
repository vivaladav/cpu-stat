#include "CPUData.h"

#include <sstream>

const std::string CPUData::STR_CPU("cpu");
const std::string CPUData::STR_TOT("tot");

const std::size_t CPUData::LEN_STR_CPU = 3;

// == PUBLIC FUNCTIONS ==

void CPUData::ReadData(const std::string & line)
{
	std::istringstream ss(line);

	// read cpu label
	ss >> mLabel;

	// remove "cpu" from the label when it's a processor number
	if(mLabel.size() > LEN_STR_CPU)
	    mLabel.erase(0, LEN_STR_CPU);
	// replace "cpu" with "tot" when it's total values
	else
	    mLabel = STR_TOT;

	// read times
	for(int i = 0; i < NUM_CPU_STATES; ++i)
    	ss >> mTimes[i];
}
