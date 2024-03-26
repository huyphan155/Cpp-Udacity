#include "processor.h"
#include "linux_parser.h"

/*
* brief : Return the aggregate CPU utilization
* CPU utilization = Active Jiffies / Total Jiffies
*/
float Processor::Utilization() { 
  float cpuUtilization = 0.0;
  long JifValue = LinuxParser::Jiffies();
  long activeJifValue = LinuxParser::ActiveJiffies();
  cpuUtilization = static_cast<float>(activeJifValue)/(JifValue);
  return cpuUtilization;
}

