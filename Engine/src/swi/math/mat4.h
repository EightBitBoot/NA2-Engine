#pragma once

#include<iostream>

#include "vec4.h"

//4 * 4 float matrix
class mat4 {
public:
	union {
		float elements[4 * 4];
		vec4 rows[4];
	};

	vec4& operator[](int index);
	const vec4& operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& stream, mat4& matrix);

	mat4();
	~mat4();
};