#include <vector>

enum class BlockFace {
	Top, Bottom, Front, Back, Left, Right
};

struct Mesh {

	std::vector<float> vertices, normals, texCoords;

	void update(const Mesh& other, std::size_t x,
		std::size_t y, std::size_t z) {
		for (std::size_t i = 0; i < other.vertices.size() / 3; i++) {
			vertices.push_back(other.vertices[i * 3] + x);
			vertices.push_back(other.vertices[i * 3 + 1] + y);
			vertices.push_back(other.vertices[i * 3 + 2] + z);
		}
		normals.insert(normals.end(), other.normals.begin(), other.normals.end());
		texCoords.insert(texCoords.end(), other.texCoords.begin(), other.texCoords.end());
	}

	std::size_t triangleCount() {
		return vertices.size() / 3;
	}

	static Mesh getMeshFace(BlockFace face) {
		if (face == BlockFace::Top)
			return Mesh{
				{
					-0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f
				},
				{
					0.0f,  1.0f,  0.0f
				},
				{
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f
				}
		};
		else if (face == BlockFace::Bottom)
			return Mesh{
				{
					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f, -0.5f
				},
				{
					0.0f, -1.0f,  0.0f
				},
				{
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f
				}
		};
		else if (face == BlockFace::Front)
			return Mesh{
				{
					-0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f
				},
				{
					0.0f,  0.0f,  1.0f
				},
				{
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f
				}
		};
		else if (face == BlockFace::Back)
			return Mesh{
				{
					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f
				},
				{
					0.0f,  0.0f, -1.0f
				},
				{
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f
				}
		};
		else if (face == BlockFace::Right)
			return Mesh{
				{
					0.5f,  0.5f,  0.5f,
					0.5f,  0.5f, -0.5f,
					0.5f, -0.5f, -0.5f,
					0.5f, -0.5f, -0.5f,
					0.5f, -0.5f,  0.5f,
					0.5f,  0.5f,  0.5f
				},
				{
					1.0f,  0.0f,  0.0f
				},
				{
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f
				}
		};
		else  // face == BlockFace::Left
			return Mesh{
				{
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f
				},
				{
					-1.0f,  0.0f,  0.0f
				},
				{
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f
				}
		};
	}

};