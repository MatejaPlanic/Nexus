#pragma once

#include <random>

class Random
{
public:
	static void Init()
	{
		std::random_device rd;
		s_RandomEngine.seed(rd());
	}

	static float Float()
	{
		return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}

private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};