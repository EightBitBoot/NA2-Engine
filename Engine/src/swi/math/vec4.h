#pragma once

#include <iostream>

//4 float vector
class vec4 {
public:
	float elements[4];

	vec4();
	~vec4();

	float& operator[](int index);
	const float& operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& stream, vec4& vector);
};