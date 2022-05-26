#include "AA5.h"

namespace AA5 
{

	// == WAVE ==
	glm::vec3 AA5::Wave::GetPositionAtTime(glm::vec3 initialPosition, float time)
	{
		// time is accumulated simulation time (NOT dt)

		glm::vec3 resultingPosition;
		glm::vec3 waveVectorK;
		float offsetY = 5.f;

		// k = 2 * pi / lambda
		waveVectorK = direction * glm::vec3(2.f * 3.14f / waveLength);
		waveVectorK.y = 0.f;

		// x = x_0 - summation:(K_i/k_i) * A_i * sin(k_i * x_0 - w_i * t + phi_i)
		resultingPosition = initialPosition - direction * amplitude * sin(glm::dot(waveVectorK, initialPosition) - frequency * time + phase);

		// y = offsetY + summation:A_i * cos(K_i * x_0 - w_i * t + phi_i)
		resultingPosition.y = offsetY + amplitude * cos(glm::dot(waveVectorK, initialPosition) - frequency * time + phase);

		return resultingPosition;
	}

	// == FLUID SIMULATOR ==
	FluidSimulator::FluidSimulator()
	{
		renderParticles = false;
		renderCloth = true;
		renderSphere = false;

		meshTest = new MeshTest();
	}

	FluidSimulator::~FluidSimulator()
	{
		renderCloth = false;
	}

	void FluidSimulator::Update(float dt)
	{
	}

	void FluidSimulator::RenderUpdate()
	{
		meshTest->RenderUpdateMesh();
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
				positions[indx] = glm::vec3(((10.f/ClothMesh::numRows) * row) - 5, 0, ((10.f / ClothMesh::numCols) * col) - 5.f);
				positions[indx] = positions[indx];
			}
		}
	}
}

