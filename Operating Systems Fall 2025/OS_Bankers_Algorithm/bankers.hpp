#ifndef BANKERS
#define BANKERS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Slightly renamed configuration constants (same semantics)
inline const int NUM_PROCESSES = 5;
inline const int NUM_RESOURCES = 3;

// Terminal color labels (renamed)
inline const char* COLOR_GREEN = "\033[32m";
inline const char* COLOR_RED = "\033[31m";
inline const char* COLOR_RESET = "\033[0m";

// Global resource state using new names
inline int freeResources[NUM_RESOURCES];
inline int maxDemand[NUM_PROCESSES][NUM_RESOURCES];
inline int currentAlloc[NUM_PROCESSES][NUM_RESOURCES];

// Function prototypes updated to new dimension names
void CalculateNeed(int need[][NUM_RESOURCES]);
bool SafeCheck();

void SafeState(const std::vector<int>& safeSequence);
void UnsafeState();
void DisplaySetting();

#endif