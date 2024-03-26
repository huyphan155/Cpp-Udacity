#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor initialization
Process::Process(int pid)
{
    pid_ = pid;
}

/*
*  brief: Return this process's ID
*/
int Process::Pid() { return pid_; }

/*
*  brief: Return this process's CPU utilization
*  CPU_usage = total_time / elapsed_time 
*/
float Process::CpuUtilization() { 
    long totalTime = LinuxParser::ActiveJiffies(pid_);
    long int upTime = LinuxParser::UpTime(pid_);
    return totalTime / (float)upTime; 
}

/*
*  brief: Return the command that generated this process
*/
string Process::Command() { return LinuxParser::Command(pid_); }

/*
*  brief: Return this process's memory utilization
*/
string Process::Ram() { return LinuxParser::Ram(pid_); }

/*
*  brief: Return the user (name) that generated this process
*/
string Process::User() { return LinuxParser::User(pid_); }

/*
*  brief: Return the age of this process (in seconds)
*/
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

/*
*  brief: Overload the "less than" comparison operator for Process objects
*/
bool Process::operator<(Process &a) { 
    return CpuUtilization() < a.CpuUtilization(); 
 }
