#pragma once

#include <ctime>
#include <chrono>
#include <iostream>
#include <string>

class Log
{
public:
	static void Info(std::string message);
	static void Error(std::string message);

};

// Core log macros
#define GE_CORE_INFO(...) ::Log::Info(__VA_ARGS__)
#define GE_CORE_ERROR(...) ::Log::Error(__VA_ARGS__)

// Client log macros
#define GE_INFO(...) ::Log::Info(__VA_ARGS__)
#define GE_ERROR(...) ::Log::Error(__VA_ARGS__)

#ifdef GE_ENABLE_ASSERTS
#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#else
#define GE_ASSERT(x, ...)
#define GE_CORE_ASSERT(x, ...)
#endif