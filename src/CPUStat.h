#pragma once

#include "CPUData.h"
#include "CPUSnapshot.h"
#include "CPUStatsPrinter.h"

#include <chrono>


class CPUStat
{
    public:
        CPUStat()
        {
            lastSnapshot = CPUSnapshot();
            steadySnapshot = lastSnapshot;
        };

        std::string GetActivePercentageCPU(unsigned int cpu)
        {

            auto newSnapshot = CPUSnapshot();

            auto cpuStatsPrinter = CPUStatsPrinter(steadySnapshot,newSnapshot);

            auto retrunString = cpuStatsPrinter.GetActivePercentageCPU(cpu);

            if(lastSnapshot.didPassDurationFromConstructMs(100))
                steadySnapshot = lastSnapshot;
                lastSnapshot = newSnapshot;


            return retrunString;
        }

        std::string GetActivePercentageCPU(unsigned int cpuA, unsigned int cpuB)
        {

            auto newSnapshot = CPUSnapshot();

            auto cpuStatsPrinter = CPUStatsPrinter(lastSnapshot,newSnapshot);

            auto retrunString = "CPU" + std::to_string(cpuA)+ ":" + cpuStatsPrinter.GetActivePercentageCPU(cpuA);

            retrunString += ",CPU"  + std::to_string(cpuB) + ":" +cpuStatsPrinter.GetActivePercentageCPU(cpuB);

            lastSnapshot = newSnapshot;

            return retrunString;
        }

        std::string GetActivePercentageCPU(std::vector<unsigned int> cpus)
        {
            auto newSnapshot = CPUSnapshot();

            auto cpuStatsPrinter = CPUStatsPrinter(lastSnapshot,newSnapshot);

            std::string retrunString="";

            for(auto& cpu : cpus)
                retrunString += cpuStatsPrinter.GetActivePercentageCPU(cpu) + ";";

            lastSnapshot = newSnapshot;

            return retrunString;
        }


    private:
        CPUSnapshot lastSnapshot;
        CPUSnapshot steadySnapshot;

};
