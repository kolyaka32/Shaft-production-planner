#pragma once

// File for setting flags for all test for program
// Debuging modifiers
#define DEBUG true
#define CHECK_CORRECTION DEBUG

// Defing path to file
#if DEBUG
#define RESOURCE_PATH (std::string)"../resources/"
#else
#define RESOURCE_PATH (std::string)"resources/"
#endif
