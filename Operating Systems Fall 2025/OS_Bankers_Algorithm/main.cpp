#include "bankers.hpp"

// Parse a whitespace-separated data file into the program's matrices.
// Expected order in file: current allocation matrix, maximum demand matrix, then available counts.
bool ParseDataFile(const char* filename) {
    std::ifstream bankers_file(filename);

    if (!bankers_file) {
        std::cout << "[-] Error: Cannot open " << filename << std::endl;
        return false;
    }

    std::cout << "[*] Reading " << filename << std::endl;

    // Read current allocation matrix
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            bankers_file >> currentAlloc[i][j];
        }
    }

    // Read maximum demand matrix
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            bankers_file >> maxDemand[i][j];
        }
    }

    // Read available (free) resources
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        bankers_file >> freeResources[i];
    }

    bankers_file.close();

    std::cout << "[+] Finished reading " << filename << std::endl;

    return true;
}

void ShowHelp(const char* bin) {
    std::cout << "Usage: " << bin << " [input file]\n\n";
    std::cout << "Examples:" << std::endl;
    std::cout << "  .\/" << bin << " data1.txt" << std::endl;
}

int main(int argc, char** argv) {
    if (argc == 2) {
        if (ParseDataFile(argv[1])) {
            SafeCheck();
        } else {
            return 1;
        }
    } else {
        ShowHelp(argv[0]);
        return 1;
    }

    return 0;
}