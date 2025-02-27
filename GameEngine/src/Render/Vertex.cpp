#include "Render/Vertex.hpp"


Vertex::Vertex(const float x, const float y, const float z, const float r, const float g, const float b, const float a, const float u, const float v) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const glm::vec3 pos, const float r, const float g, const float b, const float a, const float u, const float v) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const float x, const float y, const float z, const Color col, const float u, const float v) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const float x, const float y, const float z, const float r, const float g, const float b, const float a, const glm::vec2 texCoord) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}

Vertex::Vertex(const glm::vec3 pos, const Color col, const float u, const float v) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const glm::vec3 pos, const float r, const float g, const float b, const float a, const glm::vec2 texCoord) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}

Vertex::Vertex(const float x, const float y, const float z, const Color col, const glm::vec2 texCoord) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}

Vertex::Vertex(const glm::vec3 pos, const Color col, const glm::vec2 texCoord) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}

Vertex::Vertex(const float x, const float y, const float z, const float r, const float g, const float b, const float a) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
}

Vertex::Vertex(const glm::vec3 pos, const float r, const float g, const float b, const float a) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
}

Vertex::Vertex(const float x, const float y, const float z, const Color col) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
}

Vertex::Vertex(const glm::vec3 pos, const Color col) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
}


Vertex::Vertex(const float x, const float y, const float z, const float u, const float v) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const glm::vec3 pos, const float u, const float v) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const float x, const float y, const float z, const glm::vec2 texCoord) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}

Vertex::Vertex(const glm::vec3 pos, const glm::vec2 texCoord) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}


Vertex::Vertex(const float r, const float g, const float b, const float a, const float u, const float v) {
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const Color col, const float u, const float v) {
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const float r, const float g, const float b, const float a, const glm::vec2 texCoord) {
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}

Vertex::Vertex(const Color col, const glm::vec2 texCoord) {
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}


Vertex::Vertex(const float r, const float g, const float b) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

Vertex::Vertex(const glm::vec3 pos) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
}


Vertex::Vertex(const float r, const float g, const float b, const float a) {
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
}

Vertex::Vertex(const Color col) {
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
}


Vertex::Vertex(const float u, const float v) {
	data[7] = u;
	data[8] = v;
}

Vertex::Vertex(const glm::vec2 texCoord) {
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}


void Vertex::SetPosition(const float x, const float y, const float z) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

void Vertex::SetPosition(const glm::vec3 pos) {
	data[0] = pos.x;
	data[1] = pos.y;
	data[2] = pos.z;
}


void Vertex::SetColor(const float r, const float g, const float b, const float a) {
	data[3] = r;
	data[4] = g;
	data[5] = b;
	data[6] = a;
}

void Vertex::SetColor(const Color col) {
	data[3] = col.r;
	data[4] = col.g;
	data[5] = col.b;
	data[6] = col.a;
}


void Vertex::SetTextureCoord(const float u, const float v) {
	data[7] = u;
	data[8] = v;
}

void Vertex::SetTextureCoord(const glm::vec2 texCoord) {
	data[7] = texCoord.x;
	data[8] = texCoord.y;
}