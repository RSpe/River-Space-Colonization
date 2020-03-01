#include "PerlinNoise.h"

namespace test
{
	PerlinNoise::PerlinNoise()
	{
		for (int i = 0; i < 256; i++)
		{
			srand(time(NULL));
			permutation.push_back(rand() % 256);
		}
		/* To avoid overflow */
		for (int j = 0; j < 512; j++)
		{
			doublePermutation[j] = permutation[j % 256];
		}
	}

	PerlinNoise::~PerlinNoise()
	{

	}


	float PerlinNoise::PerlinResult(float x, float y, float z)
	{
		float total = 0;
		float frequency = 0;

		/* Normalise for range 0.0 - 1.0 */
		float maxValue = 0;

		for (int i = 0; i < oct; i++)
		{
			total += Generation(x * frequency, y * frequency, z * frequency) * amp;
			maxValue += amp;
			amp *= persist;
			frequency *= 2;

		}
		return total / maxValue;
	}

	float PerlinNoise::Generation(float x, float y, float z)
	{
		/* Left bound */
		int x0 = (int)x & 255;
		int y0 = (int)y & 255;
		int z0 = (int)z & 255;
		/* Right bound */
		int x1 = x0 + 1;
		int y1 = y0 + 1;
		int z1 = z0 + 1;

		/* Distance from 0.0 to 1.0 */
		float xd = x - (float)x0;
		float yd = y - (float)y0;
		float zd = z - (float)z0;

		/* Fade (smooth) */
		float u = Fade(xd);
		float v = Fade(yd);
		float w = Fade(zd);

		/* Hash to find unique values for every input and repeat noise */
		int aaa, aba, aab, abb, baa, bba, bab, bbb;
		aaa = doublePermutation[doublePermutation[doublePermutation[x0] + y0] + z0];
		aba = doublePermutation[doublePermutation[doublePermutation[x0] + y1] + z0];
		aab = doublePermutation[doublePermutation[doublePermutation[x0] + y0] + z1];
		abb = doublePermutation[doublePermutation[doublePermutation[x0] + y1] + z1];
		baa = doublePermutation[doublePermutation[doublePermutation[x1] + y0] + z0];
		bba = doublePermutation[doublePermutation[doublePermutation[x1] + y1] + z0];
		bab = doublePermutation[doublePermutation[doublePermutation[x1] + y0] + z1];
		bbb = doublePermutation[doublePermutation[doublePermutation[x1] + y1] + z1];

		float x1f, x2f, y1f, y2f;

		/* Dot product */
		x1f = Lerp(Gradient(aaa, xd, yd, zd), Gradient(baa, xd - 1, yd, zd), u);
		x2f = Lerp(Gradient(aba, xd, yd - 1, zd), Gradient(bba, xd - 1, yd - 1, zd), u);
		/* Lerp weighted average */
		y1f = Lerp(x1f, x2f, v);

		/* Dot product */
		x1f = Lerp(Gradient(aab, xd, yd, zd - 1), Gradient(bab, xd - 1, yd, zd - 1), u);
		x2f = Lerp(Gradient(abb, xd, yd - 1, zd - 1), Gradient(bba, xd - 1, yd - 1, zd - 1), u);
		/* Lerp weighted average */
		y2f = Lerp(x1f, x2f, v);

		return (Lerp(y1f, y2f, w) + 1) / 2;
	}


	void PerlinNoise::SetAmplitude(int amplitude)
	{
		amp = amplitude;
	}

	void PerlinNoise::SetOctave(int octave)
	{
		oct = octave;
	}

	void PerlinNoise::SetPersistence(int persistence)
	{
		persist = persistence;
	}

	float PerlinNoise::Gradient(int hash, float x, float y, float z)
	{
		int h = hash & 15;

		/* 0b1000 - If most significant bit of hash is 0 then set u = x otherwise if false set to y */
		float u = hash < 8 ? x : y;

		float v;

		/* 0b0100 - If first and second significant bits are 0 then set v = y */
		if (h < 4)
			v = y;
		/* 0b1100/0b111 - If first and second significant bits are 1 then set v = x in first case - If first and second significant bits are different then set v = x */
		else if (h == 12 || h == 14)
			v = x;
		/* If first and second significant bits are different then set v = z */
		else
			v = z;

		/* Use the last 2 bits to decide if u and v are positive values and then return their addition */
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);

	}

	//float** PerlinNoise::GenerateMap()
	//{
	//	float** map = new float* [width];
	//
	//	for (int i = 0; i < width; i++) {
	//		map[i] = new float[width];
	//		for (int j = 0; j < mapHeight; j++) {
	//			map[i][j] = 0;
	//		}
	//	}
	//
	//	for (int i = 0; i < width; i++) {
	//		for (int j = 0; j < width; j++) {
	//			float nx = ((float)i / mapWidth) + 0.5f;
	//			float ny = ((float)j / mapHeight) + 0.5f;
	//			auto value = PerlinResult(nx, ny);
	//			map[i][j] += value;
	//		}
	//	}
	//
	//	return map;
	//}

	float PerlinNoise::Lerp(float a, float b, float x)
	{
		return ((1.0f - x) * a) + (x * b);
	}

	float PerlinNoise::Fade(float t)
	{
		/* Smoothing function */
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	void PerlinNoise::OnUpdate(float deltaTime)
	{

	}

	void PerlinNoise::OnRender()
	{

	}

	void PerlinNoise::OnImGuiRender()
	{

	}
}