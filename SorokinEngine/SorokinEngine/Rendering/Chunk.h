#include "glad/glad.h"
#pragma once

#define CX 16
#define CY 16
#define CZ 16

/* A x by y by z rendering of a cube that
 * will be represented in a collection of cubes. */
struct chunk {

	uint8_t blk[CX][CY][CZ];
	GLuint vbo;
	bool changed;
	int elements;

	chunk() {
		memset(blk, 0, sizeof(blk));
		//Generates space for a vbo
		glGenBuffers(1, &vbo);
		elements = 0;
	}

	~chunk() {
		glDeleteBuffers(1, &vbo);
	}

	uint8_t get(int x, int y, int z) {
		return blk[x][y][z];
	}

	void set(int x, int y, int z, uint8_t type) {
		blk[x][y][z] = type;
		changed = true;
	}

	typedef glm::tvec4<GLbyte> byte4;

	void update() {
		changed = false;

		byte4 vertex[CX * CY * CZ * 6 * 6];
		int i = 0;

		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					uint8_t type = blk[x][y][z];

					if (!type)
						continue;

					bool[6] faceFlags = {
							blocks[getIndex(x, y, z - 1)] == 0, // north face
							blocks[getIndex(x, y, z + 1)] == 0, // south face
							blocks[getIndex(x + 1, y, z)] == 0, // east face
							blocks[getIndex(x - 1, y, z)] == 0, // west face
							blocks[getIndex(x, y + 1, z)] == 0, // top face
							blocks[getIndex(x, y - 1, z)] == 0, // bottom face
					};

					//View from negative x
					vertex[i++] = byte4(x, y, z, type);
					vertex[i++] = byte4(x, y, z + 1, type);
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x, y + 1, z, type);
					vertex[i++] = byte4(x, y, z + 1, type);
					vertex[i++] = byte4(x, y + 1, z + 1, type);

					//View from positive x
					vertex[i++] = byte4(x + 1, y, z, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);
					vertex[i++] = byte4(x + 1, y + 1, z, type);
					vertex[i++] = byte4(x + 1, y + 1, z + 1, type);
					vertex[i++] = byte4(x + 1, y, z + 1, type);


					std::cout << i << std::endl;
				}
			}
		}

		elements = i;
		
		std::cout << elements << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, elements * sizeof * vertex, vertex, GL_STATIC_DRAW);
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
};