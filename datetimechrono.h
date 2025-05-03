#ifndef DATETIMEPARSER_H
#define DATETIMEPARSER_H

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>


// function to parse a date or time string.
std::chrono::system_clock::time_point GFG(const std::string& datetimeString, const std::string& format)
{
    tm tmStruct = {};
    std::istringstream ss(datetimeString);
    ss >> std::get_time(&tmStruct, format.c_str());
    return std::chrono::system_clock::from_time_t(mktime(&tmStruct));
}

// Function to format a time_t value into a date or time string.
static std::string DateTime(const std::chrono::system_clock::time_point &timePoint, const std::string &format)
{
    time_t time = std::chrono::system_clock::to_time_t(timePoint);
    tm* timeinfo = localtime(&time);
    char buffer[70];
    strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);

    return buffer;
}

static std::string convertTmToString(tm &tm)
{
    time_t date = mktime(&tm);

    // Output the parsed date using std::asctime
    return asctime(localtime(&date));
}

/* Test Code
int main()
{
    const string datetimeString = "2023-05-22 12:24:52";
    const string format = "%Y-%m-%d %H:%M:%S";

    chrono::system_clock::time_point parsedTime = GFG(datetimeString, format);
    string formattedTime = DateTime(parsedTime, format);

    cout << "Parsed Time---> " << chrono::system_clock::to_time_t(parsedTime) << endl;
    cout << "Formatted Time---> " << formattedTime << endl;

    return 0;
}
*/

#endif


