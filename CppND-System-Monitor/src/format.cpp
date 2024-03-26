#include <string>
#include <iomanip>
#include <sstream> 

#include "format.h"

using std::string;
 
/**
 * INPUT: Long int measuring seconds
 * OUTPUT: HH:MM:SS
 */
string Format::ElapsedTime(long seconds) {
    // Calculate hours, minutes, and remaining seconds
    long hours = seconds / 3600;
    long minutes = (seconds % 3600) / 60;
    long remainingSeconds = seconds % 60;

    // Use std::ostringstream to format the string
    std::ostringstream formattedTime;
    formattedTime << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << remainingSeconds;

    return formattedTime.str();
}