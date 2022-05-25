#include "AA5.h"

// == WAVE ==
glm::vec3 AA5::Wave::GetPositionAtTime(glm::vec3 initialPosition, float time)
{
	return glm::vec3();
}

// == FLUID SIMULATOR ==
void AA5::FluidSimulator::Update(float dt)
{
}

void AA5::FluidSimulator::RenderUpdate()
{
}

void AA5::FluidSimulator::RenderGui()
{
}

float AA5::FluidSimulator::GetSphereSubmergedVolume()
{
	return 0.0f;
}
