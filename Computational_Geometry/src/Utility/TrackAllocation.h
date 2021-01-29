#pragma once
#include <cstdlib>

struct AllocationMetrics
{
	size_t TotalAllocated{ 0 };
	size_t TotalFreed{ 0 };
	size_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
	s_AllocationMetrics.TotalAllocated += size;
	return malloc(size);
}

void operator delete(void* allocMem, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;
	free(allocMem);
}

static void printMemoryUsage()
{
	std::cout
		<< "\n----- Allocation Metrics -----\n"
		<< "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes \n";
}

static void printMemoryInfo()
{
	std::cout
		<< "\n----- Allocation Metrics -----\n"
		<< "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes \n"
		<< "Allocated Memory: " << s_AllocationMetrics.TotalAllocated << " bytes\n"
		<< "Freed Memory: " << s_AllocationMetrics.TotalFreed << " bytes\n"
		<< "------------------------------\n\n";
}