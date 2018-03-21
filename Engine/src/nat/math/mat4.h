#pragma once

#include<iostream>

#include "vec4.h"

namespace nat {
	//4 * 4 float matrix
	class Mat4 {
	public:
		union {
			float elements[4 * 4];
			Vec4 rows[4];
		};

		Mat4();
		Mat4(float identity);
		~Mat4();

		void add(const Mat4& other);
		void subtract(const Mat4& other);
		void multiply(const Mat4& other);

		const Vec4& operator[](int index) const;
		Vec4& operator[](int index);


		void operator+=(const Mat4& other);
		void operator-=(const Mat4& other);
		void operator*=(const Mat4& other);

		friend std::ostream& operator<<(std::ostream& stream, Mat4& matrix);

		friend Mat4 operator+(Mat4 left, const Mat4& right);
		friend Mat4 operator-(Mat4 left, const Mat4& right);
		friend Mat4 operator*(Mat4 left, const Mat4& right);
	};
}