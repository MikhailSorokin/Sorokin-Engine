#include "glad/glad.h"
#pragma once

#define CX 16
#define CY 16
#define CZ 16

/* A x by y by z rendering of a cube that
 * will be represented in a collection of cubes. */
struct chunk {

	//Array of bytes reduces memory usage
	uint8_t blk[CX][CY][CZ];
	GLuint vbo;
	bool changed;
	int elements;
	glm::vec3 chunkPos;
	unsigned int VAOs[1];

	//If not active, don't render this chunk
	bool bIsActive;

	chunk(int x, int y, int z) {
		memset(blk, 0, sizeof(blk));
		//Generates space for a vbo
		glGenBuffers(1, &vbo);

		elements = 0;
		changed = true;

		chunkPos = glm::vec3(x, y, z);
		createChunk();
	}

	void createChunk() {
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					//We will just assume 1 is "grass" texture
					set(x, y, z, 1);
				}
			}
		}
	}

	~chunk() {
		glDeleteVertexArrays(1, &VAOs[0]);
		glDeleteBuffers(1, &vbo);
	}

	uint8_t get(int x, int y, int z) {
		return blk[x][y][z];
	}

	void set(int x, int y, int z, uint8_t type) {
		blk[x][y][z] = type;
	}

	typedef glm::tvec4<GLbyte> byte4;

	/*byte4[] createTriangleVertices(int x, int y, int z) {

	}*/

	void update() {

		//We multiply by 6 for every triangle needed
		//Multiply by 6 again for (+x, -x, -y, +y, -z, +z) - 6 faces

		byte4 vertex[CX * CY * CZ * 6 * 6];
		int i = 0;

		//Builds this right off the origin
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					//View from negative x (back)
					vertex[i++] = byte4(x, y, z, type);
					vertex[i++] = byte4(x, y, z + 1, type);
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x, y, z + 1, type);
					vertex[i++] = byte4(x, y + 1, z + 1, type);
				}
			}
		}
		//Builds this right off the origin
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					//View from positive x (front)
					vertex[i++] = byte4(x + 1, y, z, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y + 1, z + 1, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);
				}
			}
		}

		//Builds this right off the origin
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					//View from negative y (bottom)
					vertex[i++] = byte4(x, y, z, type);
					vertex[i++] = byte4(x + 1, y, z, type);
					vertex[i++] = byte4(x, y, z + 1, type);
					vertex[i++] = byte4(x + 1, y, z, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);
					vertex[i++] = byte4(x, y, z + 1, type);
				}
			}
		}

		//Builds this right off the origin
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					//View from positive y (top)
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x, y + 1, z + 1, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x, y + 1, z + 1, type);
					vertex[i++] = byte4(x + 1, y + 1, z + 1, type);
				}
			}
		}

		//Builds this right off the origin
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					//View from negative z (left)
					vertex[i++] = byte4(x, y, z, type);
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y, z, type);
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y, z, type);

				}
			}
		}

		//Builds this right off the origin
		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					//View from positive z (right)
					vertex[i++] = byte4(x, y, z + 1, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);
					vertex[i++] = byte4(x, y + 1, z + 1, type);
					vertex[i++] = byte4(x, y + 1, z + 1, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);
					vertex[i++] = byte4(x + 1, y + 1, z + 1, type);
				}
			}
		}

		changed = false;
		elements = i;
		
		std::cout << "Num elements: " << elements << std::endl;

		//Upload vertices
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, i * sizeof *vertex, vertex, GL_STATIC_DRAW);
	}

	void render() {
		if (changed)
			update();

		//If chunk empty, no draw
		if (!elements)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//0 is the Position Attribute, 8 will be size of the vertices array
		glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, elements);
	}

	//TODO - rebuild function (when moving)
};