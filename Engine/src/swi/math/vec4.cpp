#include "vec4.h"

vec4::vec4()
{
	memset(elements, 0, 4 * sizeof(float));
}

vec4::~vec4()
{
	delete[] elements;
}

float& vec4::operator[](int index)
{
	return elements[index];
}

std::ostream& operator<<(std::ostream& stream, vec4& vector)
{
	stream << "[ " << vector[0] << ", " << vector[1] << ", " << vector[2] << ", " << vector[3] << " ]";
	return stream;
}