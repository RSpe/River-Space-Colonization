#pragma once

#include <vector>
#include <ctime>
#include <iostream>

#include "Test.h"

namespace test
{
	class PerlinNoise : public Test
	{
	public:
		PerlinNoise();
		~PerlinNoise();

		float PerlinResult(float x, float y, float z);
		void SetOctave(int octave);
		void SetPersistence(int persistence);
		void SetAmplitude(int amplitude);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		int width = 640;
		int height = 480;

		int oct;
		float persist;
		float amp;

		std::vector<int> permutation;
		int doublePermutation[512];

		float Gradient(int hash, float x, float y, float z);
		float Lerp(float a, float b, float x);
		float Fade(float t);
		float Generation(float x, float y, float z);
	};
}