#include "AA5.h"

namespace Sphere
{
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	CustomSphere customSphereAA5(1.f, glm::vec3(0.f, 8.f, 0.f), 0.68f);
	bool resetedRadiusAA5 = true;
}

namespace AA5 
{
	// == WAVE ==
	Wave::Wave(glm::vec3 dir = glm::vec3(0.f, 0.f, 1.f), float amp = 0.05f, float wLenght = 0.1f, float freq = 1.f, float ph = 0.1f)
	{
		direction = dir;
		amplitude = amp;
		waveLength = wLenght;
		frequency = freq;
		phase = ph;

		yOffset = 1.f;

		// k = 2 * pi / lambda
		waveK = direction * glm::vec3(2.f * 3.14f / waveLength);
		waveK.y = 0.f;
	}

	glm::vec3 AA5::Wave::GetPositionAtTime(glm::vec3 initialPosition, float time)
	{
		// time is accumulated simulation time (NOT dt)
		glm::vec3 resultingPosition;

		// x = x_0 - summation:(K_i/k_i) * A_i * sin(k_i * x_0 - w_i * t + phi_i)
		resultingPosition = - direction * amplitude * sin(glm::dot(waveK, initialPosition) - frequency * time + phase);

		// y = offsetY + summation:A_i * cos(K_i * x_0 - w_i * t + phi_i)
		resultingPosition.y = amplitude * cos(glm::dot(waveK, initialPosition) - frequency * time + phase);

		return resultingPosition;
	}

	glm::vec3 Wave::SummWaves(glm::vec3 initialPosition, float time)
	{
		return glm::vec3();
	}
	
	
	// == FLUID SIMULATOR ==
	FluidSimulator::FluidSimulator()
	{
		srand(time(NULL));

		renderParticles = false;
		renderCloth = true;
		renderSphere = true;

		meshTest = new MeshTest();

		waves.push_back(Wave());
		waves.push_back(Wave());
		waves.push_back(Wave());
		waves.push_back(Wave(glm::vec3(1.f, 0.f, 0.f)));
		waves.push_back(Wave(glm::vec3(1.f, 0.f, 0.f)));
	}

	FluidSimulator::~FluidSimulator()
	{
		renderCloth = false;
	}

	void FluidSimulator::Update(float dt)
	{
		accumTime += dt;
		sphereAccumTime += dt;

		meshTest->positions = meshTest->initialPos;
		glm::vec3 forceAccum = glm::vec3(0.f);
		glm::vec3 finalPos = glm::vec3(0.f);
		for (int i = 0; i < meshTest->positions.size(); i++)
		{
			for (int j = 0; j < waves.size(); j++)
			{
				forceAccum += waves[j].GetPositionAtTime(meshTest->initialPos[i], accumTime);
				finalPos = meshTest->initialPos[i] + forceAccum;
			}
			meshTest->positions[i] = finalPos;
			forceAccum = glm::vec3(0.f);
		}		 
		
		if (Sphere::customSphereAA5.sphereCenter.y <= meshTest->GetMeshPositionsY())
		{
			Sphere::customSphereAA5.SetCurrentSphereVel(Sphere::customSphereAA5.BuoyancyForce(
				Sphere::customSphereAA5.CalculateSphereCapVolume(
					Sphere::customSphereAA5.CalculateSphereCapHeight(meshTest->GetMeshPositionsY())))/25.f + glm::vec3(0.f, -9.81f, 0.f));
			
		}
		Sphere::customSphereAA5.StepEulerSphere(dt);

		if (sphereAccumTime >= 4.f)
		{
			Sphere::customSphereAA5.sphereCenter = glm::vec3(rand() % 9 - 5, 8.f, rand() % 9 - 5);
			sphereAccumTime = 0;
			Sphere::customSphereAA5.sphereVel = glm::vec3(0.f);
		}
		//printf("\nSphere Y: %f", Sphere::customSphereAA5.GetCurrentSpherePos().y);
	}

	void FluidSimulator::RenderUpdate()
	{
		meshTest->RenderUpdateMesh();
		Sphere::updateSphere(Sphere::customSphereAA5.sphereCenter, Sphere::customSphereAA5.sphereRadius);
	}

	void FluidSimulator::RenderGui()
	{

	}

	float FluidSimulator::GetSphereSubmergedVolume()
	{
		return 0.0f;
	}

	MeshTest::MeshTest()
	{
		for (int i = 0; i < ClothMesh::numCols * ClothMesh::numRows; i++)
		{
			positions.push_back(glm::vec3(0.f));
			initialPos.push_back(glm::vec3(0.f));
		}		
		SetInitialMeshPosition();
	}

	MeshTest::~MeshTest()
	{
		renderCloth = false;
	}

	int MeshTest::GetIndex(int col, int row)
	{
		return col + (row * ClothMesh::numCols);
	}

	void MeshTest::Update()
	{
		for (float row = 0; row < ClothMesh::numRows; row++)
		{
			for (float col = 0; col < ClothMesh::numCols; col++)
			{
				int indx = GetIndex(col, row);
			}
		}
	}

	void MeshTest::RenderUpdateMesh()
	{
		ClothMesh::updateClothMesh(&(positions[0].x));
	}

	void MeshTest::SetInitialMeshPosition()
	{
		for (float row = 0; row < ClothMesh::numRows; row++)
		{
			for (float col = 0; col < ClothMesh::numCols; col++)
			{
				int indx = GetIndex(col, row);
				initialPos[indx] = glm::vec3(((10.5f / ClothMesh::numRows) * row) - 5.f, 3.f, ((10.5f / ClothMesh::numCols) * col) - 5.f);
				positions[indx] = initialPos[indx];
			}
		}
	}

	float MeshTest::GetMeshPositionsY()
	{
		float avg = 0;
		for (float row = 8; row < (ClothMesh::numRows / 2) + 1; row++)
		{
			for (float col = 6; col < (ClothMesh::numCols) + 1; col++)
			{
				int indx = GetIndex(col, row);
				avg += positions[indx].y;
			}
		}
		return avg / 18;
	}
	

}

