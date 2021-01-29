#pragma once
#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer() : m_start{ highres_clock_t::now() } {}

	const double elapsedSeconds() const
	{
		const std::chrono::duration<double, std::ratio<1>> elapsedseconds = highres_clock_t::now() - m_start;
		return elapsedseconds.count();
	}

	std::string elapsedInfo() const
	{
		std::string str = "Elapsed seconds : ";
		const std::chrono::duration<double, std::ratio<1>> elapsedseconds = highres_clock_t::now() - m_start;

		str += std::to_string(elapsedseconds.count());
		str += "\n";
		return str;
	}

	friend std::ostream& operator<<(std::ostream& out, const Timer& t)
	{
		const std::chrono::duration<double, std::ratio<1>> elapsed = highres_clock_t::now() - t.m_start;
		return out
			<< "\n----- Timer Metrics -----\n"
			<< "Elapsed seconds : " << elapsed.count() << "\n"
			<< "-------------------------\n\n";
	}

	void restart()
	{
		m_start = highres_clock_t::now();
	}
private:
	using highres_clock_t = std::chrono::high_resolution_clock;
	std::chrono::time_point<highres_clock_t> m_start;
};