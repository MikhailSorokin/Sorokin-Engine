#include "Mesh.h"
#include <iostream>

#define CX 16
#define CY 16
#define CZ 16

struct chunk {

	bool blocks[CX][CY][CZ];
	Mesh mesh;
	int VAO;

	chunk() {
		initChunk();
		initMesh();
	}

	void initChunk() {
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					blocks[x][y][z] = true;
				}
			}
		}
	}

	void initMesh() {

		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					mesh.update(Mesh::getMeshFace(BlockFace::Back), x - 1, y, z);
					mesh.update(Mesh::getMeshFace(BlockFace::Bottom), x, y - 1, z);
					mesh.update(Mesh::getMeshFace(BlockFace::Left), x, y, z - 1);
					mesh.update(Mesh::getMeshFace(BlockFace::Front), x, y, z);
					mesh.update(Mesh::getMeshFace(BlockFace::Top), x, y, z);
					mesh.update(Mesh::getMeshFace(BlockFace::Right), x, y, z);
				}
			}
		}

		std::cout << mesh.vertices.size() << " vertices" << std::endl;
	

		// creating vertices
		/*std::vector<float> temp_vertices;
		for (std::size_t i = 0; i < mesh.vertices.size() / 3; ++i)  // we will move from one line to another
		{
			temp_vertices.push_back(mesh.vertices[i * 3]);
			temp_vertices.push_back(mesh.vertices[1 + i * 3]);
			temp_vertices.push_back(mesh.vertices[2 + i * 3]);

			temp_vertices.push_back(mesh.texCoords[i * 3]);
			temp_vertices.push_back(mesh.texCoords[1 + i * 3]);
		}

		temp_vertices.reserve();*/

		//VAO, VBO
		Loader loader;
		loader.createAttributes(mesh.vertices);

		VAO = loader.getVAO(0);
	}

	int getTriangleCount() {
		return mesh.triangleCount();
	}

	int getVAO() {
		return VAO;
	}

};