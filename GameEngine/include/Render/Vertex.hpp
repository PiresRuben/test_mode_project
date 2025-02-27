#pragma once

#include <Core/Maths/vec3.hpp>
#include <Core/Maths/vec2.hpp>

#include "Color.hpp"


/**
 * \brief Primitive Vertex class
 */
struct Vertex {
	/**
	 * \brief Union field allowing to access same variables using different names
	 */
	union {
		struct { float x, y, z, r, g, b, a, u, v; };
		struct { struct { float x, y, z; } position; struct { float r, g, b, a; } color; struct { float u, v; } textureCoord; };
		float data[9]{ .0f, .0f, .0f, 1.0f, 1.0f, 1.0f, 1.0f, .0f, .0f };
	};

	/**
	 * \brief Default Ctor
	 */
	Vertex() = default;
	/**
	 * \brief Default Dtor
	 */
	~Vertex() = default;

	/**
	 * \brief Ctor with 9 floats
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const float x, const float y, const float z, const float r, const float g, const float b, const float a, const float u, const float v);
	/**
	 * \brief Ctor with glm::vec3 and 6 floats
	 * \param pos -> Vertex Position as glm::vec3
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const glm::vec3 pos, const float r, const float g, const float b, const float a, const float u, const float v);
	/**
	 * \brief Ctor with 3 floats and Color
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param col -> Vertex Color as Color
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const float x, const float y, const float z, const Color col, const float u, const float v);
	/**
	 * \brief Ctor with 7 floats and glm::vec2
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const float x, const float y, const float z, const float r, const float g, const float b, const float a, const glm::vec2 texCoord);
	/**
	 * \brief Ctor with glm::vec3, Color and 2 floats
	 * \param pos -> Vertex Position as glm::vec3
	 * \param col -> Vertex Color as Color
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const glm::vec3 pos, const Color col, const float u, const float v);
	/**
	 * \brief Ctor with glm::vec3, 4 floats and glm::vec2
	 * \param pos -> Vertex Position as glm::vec3
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const glm::vec3 pos, const float r, const float g, const float b, const float a, const glm::vec2 texCoord);
	/**
	 * \brief Ctor with 3 floats, Color and glm::vec2
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param col -> Vertex Color as Color
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const float x, const float y, const float z, const Color col, const glm::vec2 texCoord);
	/**
	 * \brief Ctor with glm::vec3, Color and glm::vec2
	 * \param pos -> Vertex Position as glm::vec3
	 * \param col -> Vertex Color as Color
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const glm::vec3 pos, const Color col, const glm::vec2 texCoord);

	/**
	 * \brief Ctor with 7 floats
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 */
	Vertex(const float x, const float y, const float z, const float r, const float g, const float b, const float a);
	/**
	 * \brief Ctor with glm::vec3 and 4 floats
	 * \param pos -> Vertex Position as glm::vec3
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 */
	Vertex(const glm::vec3 pos, const float r, const float g, const float b, const float a);
	/**
	 * \brief Ctor with 3 floats
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param col -> Vertex Color as Color
	 */
	Vertex(const float x, const float y, const float z, const Color col);
	/**
	 * \brief Ctor with glm::vec3 and Color
	 * \param pos -> Vertex Position as glm::vec3
	 * \param col -> Vertex Color as Color
	 */
	Vertex(const glm::vec3 pos, const Color col);

	/**
	 * \brief Ctor with 5 floats
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const float x, const float y, const float z, const float u, const float v);
	/**
	 * \brief Ctor with glm::vec3 and 2 floats
	 * \param pos -> Vertex Position as glm::vec3
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const glm::vec3 pos, const float u, const float v);
	/**
	 * \brief Ctor with 3 floats and glm::vec2
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const float x, const float y, const float z, const glm::vec2 texCoord);
	/**
	 * \brief Ctor with glm::vec3 and glm::vec2
	 * \param pos -> Vertex Position as glm::vec3
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const glm::vec3 pos, const glm::vec2 texCoord);

	/**
	 * \brief Ctor with 6 floats
	 * \param pos -> Vertex Position as glm::vec3
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const float r, const float g, const float b, const float a, const float u, const float v);
	/**
	 * \brief Ctor with Color and 2 floats
	 * \param col -> Vertex Color as Color
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const Color col, const float u, const float v);
	/**
	 * \brief Ctor with 4 floats and glm::vec2
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const float r, const float g, const float b, const float a, const glm::vec2 texCoord);
	/**
	 * \brief Ctor with Color and glm::vec2
	 * \param col -> Vertex Color as Color
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const Color col, const glm::vec2 texCoord);

	/**
	 * \brief Ctor with 3 floats
	 * \param x -> Vertex Position on the X axis
	 * \param y -> Vertex Position on the Y axis
	 * \param z -> Vertex Position on the Z axis
	 */
	Vertex(const float r, const float g, const float b);
	/**
	 * \brief Ctor with glm::vec3
	 * \param pos -> Vertex Position as glm::vec3
	 */
	Vertex(const glm::vec3 pos);

	/**
	 * \brief Ctor with 4 floats
	 * \param pos -> Vertex Position as glm::vec3
	 * \param r -> Amount of Red in the Vertex Color
	 * \param g -> Amount of Green int the Vertex Color
	 * \param b -> Amount of Blue in the Vertex Color
	 * \param a -> Alpha of the Vertex Color
	 */
	Vertex(const float r, const float g, const float b, const float a);
	/**
	 * \brief Ctor with Color
	 * \param col -> Vertex Color as Color
	 */
	Vertex(const Color col);

	/**
	 * \brief Ctor with 2 floats
	 * \param u -> Texture Horizontal pixel position
	 * \param v -> Texture Vertical pixel position
	 */
	Vertex(const float u, const float v);
	/**
	 * \brief Ctor with glm::vec2
	 * \param texCoord -> Texture pixel position
	 */
	Vertex(const glm::vec2 texCoord);

	void SetPosition(const float x, const float y, const float z);
	void SetPosition(const glm::vec3 pos);

	void SetColor(const float r, const float g, const float b, const float a);
	void SetColor(const Color col);

	void SetTextureCoord(const float u, const float v);
	void SetTextureCoord(const glm::vec2 texCoord);
};