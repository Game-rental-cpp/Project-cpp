// Log.cpp
#include "Log.h"
#include <fstream>

// This function is used to add data to the program performance log
void Log::write(std::string update) {
    // Open the file for writing
    std::ofstream log("log.txt", std::ios_base::app);
    if (log.is_open()) {
        log << update << std::endl;
        log.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open log.txt for writing." << std::endl;
        return;
    }
}