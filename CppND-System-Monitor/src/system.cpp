#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

/*
*  brief: Return the system's CPU
*/
Processor& System::Cpu() { return cpu_; }

/*
*  brief: Return a container composed of the system's processes
*/
vector<Process>& System::Processes() { 
    // Read process IDs from the file system and generate a vector
    vector<int> process_ids = LinuxParser::Pids();

    for (int process_id : process_ids) {
        Process process(process_id);
        processes_.emplace_back(process);
    }
    // sort process based on CPU usage
    std::sort(processes_.begin(), processes_.end());
    return processes_; 
}

/*
*  brief: Return the system's kernel identifier (string)
*/
std::string System::Kernel() { return LinuxParser::Kernel(); }

/*
*  brief: Return the system's memory utilization
*/
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

/*
*  brief: Return the operating system name
*/
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

/*
*  brief: Return the number of processes actively running on the system
*/
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

/*
*  brief: Return the total number of processes on the system
*/
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

/*
*  brief: Return the number of seconds since the system started running
*/
long System::UpTime() { return LinuxParser::UpTime(); }
