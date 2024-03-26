#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

/*
* Read and return the system memory utilization
* Total used memory : calTotalMem = MemTotal - MemFree
* Cached memory : calCatchedMem = Cached + SReclaimable - Shmem
* Non cache/buffer memory : calUsedMem = calTotalMem - (Buffers + calCatchedMem)
*/
float LinuxParser::MemoryUtilization() { 
    std::string line;
    std::string key;
    float memPercen = 0.5;
    int calTotalMem = 0;
    int calCatchedMem = 0;
    int calUsedMem = 0;
    int MemTotal = 0;
    int MemFree = 0;
    int Buffers = 0;
    int Cached = 0;
    int SReclaimable = 0;
    int Shmem = 0;
    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "MemTotal") 
                {
                    linestream >> MemTotal;
                } 
                else if (key == "MemFree") 
                {
                    linestream >> MemFree;
                }
                else if (key == "Buffers") 
                {
                    linestream >> Buffers;
                }
                else if (key == "Cached") 
                {
                    linestream >> Cached;
                }
                else if (key == "SReclaimable") 
                {
                    linestream >> SReclaimable;
                }
                else if (key == "Shmem") 
                {
                    linestream >> Shmem;
                }
                else 
                {
                    /* Do nothing */
                }
            }
        }
    }
    calTotalMem = MemTotal - MemFree;
    calCatchedMem = Cached + SReclaimable - Shmem;
    calUsedMem = calTotalMem - (Buffers + calCatchedMem);
    memPercen = calUsedMem / (float) calTotalMem;
    return memPercen;
  }

/**
 * brief : Read and return the system uptime
 */
long LinuxParser::UpTime() { 
  long upTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
  }
  return upTime;
 }

/*
* brief :Read and return the number of jiffies for the system
* Jiffies value = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice
*/
long LinuxParser::Jiffies() { 
  vector<string> bridge = LinuxParser::CpuUtilization();
  long JifValue = 0;
  JifValue = stol(bridge[kUser_]) + stol(bridge[kNice_]) + stol(bridge[kSystem_]) + stol(bridge[kIdle_])
  + stol(bridge[kIOwait_]) + stol(bridge[kIRQ_]) + stol(bridge[kSoftIRQ_])
  + stol(bridge[kSteal_]) + stol(bridge[kGuest_]) + stol(bridge[kGuestNice_]);
  return JifValue;
  }

/*
* brief : Read and return the number of active jiffies for the system
* Active Jiffies value = user + nice + system + irq + softirq + steal + guest + guest_nice
*/
long LinuxParser::ActiveJiffies() { 
  vector<string> bridge = LinuxParser::CpuUtilization();
  long activeJifValue = 0;
  activeJifValue = stol(bridge[kUser_]) + stol(bridge[kNice_]) 
  + stol(bridge[kSystem_]) + stol(bridge[kIRQ_]) + stol(bridge[kSoftIRQ_])
  + stol(bridge[kSteal_]) + stol(bridge[kGuest_]) + stol(bridge[kGuestNice_]);
  return activeJifValue;
 }

/*
* brief : Read and return the number of idle jiffies for the system
* Idel Jiffies value = idle + iowait
*/
long LinuxParser::IdleJiffies() { 
  vector<string> bridge = LinuxParser::CpuUtilization();
  long IdleJifValue = 0;
  IdleJifValue = stol(bridge[kIdle_])+ stol(bridge[kIOwait_]);
  return IdleJifValue;
 }
 
/*
* brief :Read and return CPU utilization
* Read the first line and store CPU values into the vector
*/
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuStatus;
  string cpuKeyWorld;
  string value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    /* Discard the world "cpu" */
    linestream >> cpuKeyWorld;
    while(linestream >> value)
    {
      cpuStatus.push_back(value);
    }
  }
  return cpuStatus;
  }


/*
* brief : Read and return the total number of processes
*/
int LinuxParser::TotalProcesses() {
    std::string line;
    std::string key;
    int processes = 0;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "processes") {
                    if (linestream >> processes) {
                        // Successfully read the value, return it
                        return processes;
                    } else {
                        // Failed to read the value, return 0 or handle the error accordingly
                        return 0;
                    }
                }
            }
        }
    }
    // Return 0 if the key is not found or there is an issue with the file
    return 0;
}

/*
* brief : Read and return the number of running processes
*/
int LinuxParser::RunningProcesses() { 
    std::string line;
    std::string key;
    int runProcesses = 0;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "procs_running") {
                    if (linestream >> runProcesses) {
                        // Successfully read the value, return it
                        return runProcesses;
                    } else {
                        // Failed to read the value, return 0 or handle the error accordingly
                        return 0;
                    }
                }
            }
        }
    }
    // Return 0 if the key is not found or there is an issue with the file
    return 0;
 }

/*
* brief : Read and return the command associated with a process
*/ 
string LinuxParser::Command(int pid) { 
  string command;
  string line;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;
  }
  return command;
  }

/*
* brief : Read and return the memory used by a process
*/
string LinuxParser::Ram(int pid) { 
    string line;
    string key;
    string VmSize;
    int intValue;
    int result;
    std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "VmSize") 
                {
                    linestream >> VmSize;
                }
            }
        }
    }
    // Converting the memory utilization from KB to megabytes
    intValue = std::stoi(VmSize);
    result = intValue/1000;
    return std::to_string(result);
  }

/*
* brief : Read and return the user ID associated with a process
*/
string LinuxParser::Uid(int pid) { 
    string line;
    string key;
    string Uid;
    std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "Uid") 
                {
                    linestream >> Uid;
                }
            }
        }
    }
  return Uid; 
}

/*
* brief : Read and return the user associated with a process
*/
string LinuxParser::User(int pid) { 
    string line;
    string key;
    string user;
    string dummy;
    std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> user >> dummy >> key) {
                if (key == LinuxParser::Uid(pid)) 
                {
                    return user; 
                }
            }
        }
    }
  // return empty string in case of fail
  return user; 
} 

/*
* brief : Read and return the uptime of a process
*/
long LinuxParser::UpTime(int pid) { 
    string line;
    string key;
    long dumpTemp;
    long clockTick;
    long upTime;
    std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
    if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    /* Discard 21 first number */
    for (int i=0; i <= 20;i++)
      {
          linestream >> dumpTemp;
      }
    // take the value of clock tick in position 22
    linestream >> clockTick;
    // convert clock tick to second, 
    // caculate upTime for proccess = overall system uptime - process start time
    upTime = LinuxParser::UpTime() - (clockTick/sysconf(_SC_CLK_TCK));
    }
    return upTime; 
}

// Read and return the number of active jiffies for a PID. 
/*
* In ./proc/[PID]/stat
* #14 utime - CPU time spent in user code, measured in clock ticks
* #15 stime - CPU time spent in kernel code, measured in clock ticks
* #16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
* #17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
* total time for process in clocktick = utime + stime + cutime + cstime
*/
// User for caculate  CpuUtilization
long LinuxParser::ActiveJiffies(int pid) { 
    string line;
    string key;
    long totalTime;
    vector<string> statDirValue(22);
    std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
    if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    /* Store 22 first number */
    for (int i=0; i < 22;i++)
      {
          linestream >> statDirValue[i];
      }
    // totalTime for process in clock tick = utime + stime + cutime + cstime
    totalTime =  stol(statDirValue[13]) +  stol(statDirValue[14]) +  stol(statDirValue[15]) +  stol(statDirValue[16]);
    }
    // return total time in second
    return (totalTime/sysconf(_SC_CLK_TCK)); 
}