#include "vec4.h"

namespace nat {
	Vec4::Vec4()
	{
		memset(elements, 0, 4 * sizeof(float));
	}

	Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Vec4::~Vec4() {}

	void Vec4::add(const Vec4& other)
	{
		elements[0] += other[0];
		elements[1] += other[1];
		elements[2] += other[2];
		elements[3] += other[3];
	}

	void Vec4::subtract(const Vec4& other)
	{
		elements[0] -= other[0];
		elements[1] -= other[1];
		elements[2] -= other[2];
		elements[3] -= other[3];
	}

	void Vec4::multiply(const Vec4& other)
	{
		elements[0] *= other[0];
		elements[1] *= other[1];
		elements[2] *= other[2];
		elements[3] *= other[3];
	}

	void Vec4::divide(const Vec4& other)
	{
		elements[0] /= other[0];
		elements[1] /= other[1];
		elements[2] /= other[2];
		elements[3] /= other[3];
	}

	const float& Vec4::operator[](int index) const
	{
		if (index < 4 && index >= 0) {
			return elements[index];
		}
		ERROR("ACCESS VIOLATION");
	}

	float& Vec4::operator[](int index)
	{
		if (index < 4 && index >= 0) {
			return elements[index];
		}
		ERROR("ACCESS VIOLATION");
	}

	void Vec4::operator+=(const Vec4& other)
	{
		add(other);
	}

	void Vec4::operator-=(const Vec4& other)
	{
		subtract(other);
	}

	void Vec4::operator*=(const Vec4& other)
	{
		multiply(other);
	}

	void Vec4::operator/=(const Vec4& other)
	{
		divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, Vec4& vector)
	{
		stream << "[ " << vector[0] << ", " << vector[1] << ", " << vector[2] << ", " << vector[3] << " ]";
		return stream;
	}

	Vec4 operator+(Vec4 left, const Vec4& right)
	{
		left.add(right);
		return left;
	}

	Vec4 operator-(Vec4 left, const Vec4& right)
	{
		left.subtract(right);
		return left;
	}

	Vec4 operator*(Vec4 left, const Vec4& right)
	{
		left.multiply(right);
		return left;
	}

	Vec4 operator/(Vec4 left, const Vec4& right)
	{
		left.divide(right);
		return left;
	}
}