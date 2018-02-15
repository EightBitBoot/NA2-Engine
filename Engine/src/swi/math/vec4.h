#pragma once

#include <iostream>

class vec4 {
public:
	float elements[4];

	vec4();
	~vec4();

	float& operator[](int index);

	friend std::ostream& operator<<(std::ostream& stream, vec4& vector);
};