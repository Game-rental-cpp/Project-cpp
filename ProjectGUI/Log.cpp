// Log.cpp

#include "Log.h"
#include <fstream>

void writeToLog(std::string update) {
    // Open the file for writing
    std::wofstream log("log.txt", std::ios_base::app);
    std::wstring wUpdate(update.begin(), update.end());
    if (log.is_open()) {
        log << wUpdate << std::endl;
        log.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open log.txt for writing." << std::endl;
        return;
    }
}

