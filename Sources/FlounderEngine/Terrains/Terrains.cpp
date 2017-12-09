#include "Terrains.hpp"

#include "../Worlds/Worlds.hpp"

namespace Flounder
{
	Terrains::Terrains() :
		IModule(),
		m_terrains(new std::vector<Terrain*>()),
		m_noise1(NoiseFast(326256))
	{
		m_noise1.SetNoiseType(NoiseFast::ValueFractal);
		m_noise1.SetFrequency(0.004f);
		m_noise1.SetInterp(NoiseFast::Hermite);
		m_noise1.SetFractalType(NoiseFast::Fbm);
		m_noise1.SetFractalOctaves(4);
		m_noise1.SetFractalLacunarity(2.0f);
		m_noise1.SetFractalGain(0.5f);
	}

	Terrains::~Terrains()
	{
		for (auto object : *m_terrains)
		{
			delete object;
		}

		delete m_terrains;
	}

	void Terrains::Update()
	{
		for (auto object : *m_terrains)
		{
			// bool inRange = true;
			// bool current = true;
			// if !inRange ? delete
			// if current && !wasCurrent ? addChildren
			object->Update();
		}
	}

	float Terrains::GetHeight(const float &x, const float &z)
	{
		const float height1 = (m_noise1.GetNoise(x, z) * 30.0f) + 15.0f;

		return height1;
	}

	float Terrains::GetSlope(const float &x, const float &z)
	{
		const float squareSize = 0.5f;
		const float heightL = GetHeight(x - squareSize, z);
		const float heightR = GetHeight(x + squareSize, z);
		const float heightD = GetHeight(x, z - squareSize);
		const float heightU = GetHeight(x, z + squareSize);

		Vector3 normal = Vector3(heightL - heightR, 0.5f, heightD - heightU);
		normal.Normalize();
		return 1.0f - normal.m_y;
	}

	Vector3 Terrains::GetPosition(const float &x, const float &z)
	{
		return Vector3(x, GetHeight(x, z), z);
	}
}
