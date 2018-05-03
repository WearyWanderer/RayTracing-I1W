#pragma once

#ifndef DISTRIBUTIONH
#define DISTRIBUTIONH

#include <random>

template <typename T>
struct single_instance
{
	static T& instance()
	{
		static T theinstance{};
		return theinstance;
	}
};

class Distribution 
{
private:
	std::default_random_engine m_engine;
	std::uniform_real_distribution<float> m_randomFloat = std::uniform_real_distribution<float>(0.0f, 1.0f);
public:
	Distribution() {};

	float GetRandomUnitFloat()
	{
		return m_randomFloat(m_engine);
	}
};


#endif