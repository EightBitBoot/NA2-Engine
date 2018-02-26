#include "mat4.h"

mat4::mat4()
{
	memset(elements, 0, 4 * 4 * sizeof(float));
}

mat4::~mat4() {}

vec4& mat4::operator[](int index)
{
	return rows[index];
}

const vec4& mat4::operator[](int index) const
{
	return rows[index];
}

std::ostream& operator<<(std::ostream& stream, mat4& matrix)
{
	stream << matrix[0] << std::endl << matrix[1] << std::endl << matrix[2] << std::endl << matrix[3];
	return stream;
}