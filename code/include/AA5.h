#pragma once
#include "Simulator.h"
#include <vector>
#include <glm/glm.hpp>

namespace AA5 
{
	class Wave 
	{
	public:
		glm::vec3 GetPositionAtTime(glm::vec3 initialPosition, float time);
	private:
		glm::vec3 direction;
		float amplitude;
		float wavelength;
	};

	class Sphere 
	{
	public:
		glm::vec3 position;
		float radius;
		float density;
	};

	class FluidSimulator : public Simulator 
	{
	public:
		void Update(float dt);
		void RenderUpdate();
		void RenderGui();
	private:
		float GetSphereSubmergedVolume();

		std::vector<Wave> waves;
		Sphere sphere;
	};
}