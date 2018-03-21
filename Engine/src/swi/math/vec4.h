#pragma once

#include <iostream>

#include "error.h"

namespace nat {
	//4 float vector
	class Vec4 {
	public:
		union {
			float elements[4];
			struct { float x; float y; float z; float w; };
		};

		Vec4();
		Vec4(float x, float y, float z, float w);
		~Vec4();

		void add(const Vec4& other);
		void subtract(const Vec4& other);
		void multiply(const Vec4& other);
		void divide(const Vec4& other);

		const float& operator[](int index) const;
		float& operator[](int index);

		void operator+=(const Vec4& other);
		void operator-=(const Vec4& other);
		void operator*=(const Vec4& other);
		void operator/=(const Vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, Vec4& vector);

		friend Vec4 operator+(Vec4 left, const Vec4& right);
		friend Vec4 operator-(Vec4 left, const Vec4& right);
		friend Vec4 operator*(Vec4 left, const Vec4& right);
		friend Vec4 operator/(Vec4 left, const Vec4& right);

	};
}