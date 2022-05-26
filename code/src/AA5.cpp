#include "AA5.h"

namespace AA5 {
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

	// == WAVE ==
	glm::vec3 AA5::Wave::GetPositionAtTime(glm::vec3 initialPosition, float time)
	{
		glm::vec3 resultingPosition;
		glm::vec3 waveVectorK;
		float offsetY = 5.f;

		// k = 2 * pi / lambda
		waveVectorK = direction * glm::vec3(2.f * 3.14f / waveLength);

		// x = x_0 - summation:(K_i/k_i) * A_i * sin(k_i * x_0 - w_i * t + phi_i)
		resultingPosition.x = initialPosition.x - direction.x * amplitude * sin(waveVectorK.x * initialPosition.x - frequency * time + fase);

		// y = offsetY + summation:A_i * cos(K_i * x_0 - w_i * t + phi_i)
		resultingPosition.y = offsetY + amplitude * cos(waveVectorK.y * initialPosition.y - frequency * time + fase);

		return resultingPosition;
	}

	// == FLUID SIMULATOR ==
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
		positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
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

