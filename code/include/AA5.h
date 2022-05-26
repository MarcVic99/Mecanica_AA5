#pragma once
#include "Simulator.h"
#include <vector>
#include <glm/glm.hpp>
#include <time.h>

extern bool renderParticles;
extern bool renderSphere;
extern bool renderCloth;

namespace ClothMesh
{
	extern void updateClothMesh(float* aray_data);
	extern const int numCols;
	extern const int numRows;
}
namespace AA5 
{
	
	class Wave 
	{
	public:
		Wave(glm::vec3 dir, float amp, float wLenght, float freq, float ph);
		
		glm::vec3 GetPositionAtTime(glm::vec3 initialPosition, float time);
	
	private:
		glm::vec3 direction;
		float amplitude;
		float waveLength;

		float frequency;
		float phase;
	};

	class Sphere 
	{
	public:
		glm::vec3 position;
		float radius;
		float density;
	};

	class MeshTest
	{
	public:
		MeshTest();
		~MeshTest();

		int GetIndex(int col, int row);

		void RenderUpdateMesh();

		void Update();

		void SetInitialMeshPosition();
		void SetInitialMeshParticlePositionAndVelocity();

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> initialPos;
	};

	class FluidSimulator : public Simulator 
	{
	public:
		FluidSimulator();
		~FluidSimulator();
		void Update(float dt);
		void RenderUpdate();
		void RenderGui();

	private:
		float GetSphereSubmergedVolume();
		float accumTime;

		std::vector<Wave> waves;
		//std::vector<glm::vec3> positions; // 18 x 14 mesh
		Sphere sphere;
		MeshTest *meshTest;
	};

	


}