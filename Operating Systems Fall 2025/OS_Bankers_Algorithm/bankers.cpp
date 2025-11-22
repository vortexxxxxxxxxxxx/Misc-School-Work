#include "bankers.hpp"

// compute the remaining need matrix from max demand and current allocation
void CalculateNeed(int need[][NUM_RESOURCES]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            // remaining need for process i on resource j
            need[i][j] = maxDemand[i][j] - currentAlloc[i][j];
        }
    }
}

// determine if system is in a safe state (Banker's safety algorithm)
bool SafeCheck() {
    DisplaySetting();

    int need[NUM_PROCESSES][NUM_RESOURCES];

    // build the need matrix
    CalculateNeed(need);

    bool finish[NUM_PROCESSES] = {false};
    std::vector<int> safeSequence;

    // snapshot of available (work) resources
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = freeResources[i];
    }

    // count of processes that have finished
    int completed = 0;

    while (completed < NUM_PROCESSES) {
        bool found = false;

        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                // check if process i's needs can be satisfied by work
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) { 
                        // cannot satisfy this process yet
                        can_allocate = false;
                        break;
                    }
                }

                // if it can be satisfied, simulate its completion
                if (can_allocate) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        // release the process's allocated resources back to work
                        work[j] += currentAlloc[i][j];
                    }

                    // add to the safe sequence
                    safeSequence.push_back(i);

                    finish[i] = true; completed++;
                    found = true;
                }
            }
        }

        // no progress can be made -> unsafe
        if (!found) {
            UnsafeState();
            return false;
        }
    }

    // reached safe state; print safe ordering
    SafeState(safeSequence);

    return true;
}

// print basic environment configuration
void DisplaySetting() {
    std::cout << "-Running Environment" << std::endl;
    std::cout << "      Processes configured -> " << NUM_PROCESSES << std::endl;
    std::cout << "      Resource types -> " << NUM_RESOURCES << std::endl;
}

// print safe-state with the computed safe sequence
void SafeState(const std::vector<int>& safeSequence) {
    std::cout << COLOR_GREEN << "-System is in a Safe state." << std::endl;
    std::cout << "    safe-sequence: ";

    for (size_t i = 0; i < safeSequence.size(); ++i) {
        std::cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << COLOR_RESET << std::endl;
}

// print when the system cannot be placed into a safe state
void UnsafeState() {
    std::cout << COLOR_RED << "-System is in an Unsafe state!" << COLOR_RESET << std::endl;
}