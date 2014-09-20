#ifndef LANTERN_MATRIX3X3_H
#define LANTERN_MATRIX3X3_H

#include <cmath>
#include "vector3.h"

namespace lantern
{
	/** Class representing 3x3 matrix.
	*	Coordinate system assumed to be left-handed. Values are accessed as [row][column].
	*/
	class matrix3x3
	{
	public:
		float values[3][3];

		matrix3x3();
		matrix3x3(
			float const m00, float const m01, float const m02,
			float const m10, float const m11, float const m12,
			float const m20, float const m21, float const m22);

		matrix3x3 operator*(matrix3x3 const& m) const;

		static matrix3x3 scale(float const x, float const y, float const z);
		static matrix3x3 uniform_scale(float const s);
		static matrix3x3 rotation_around_x_axis(float const radians);
		static matrix3x3 rotation_around_y_axis(float const radians);
		static matrix3x3 rotation_around_z_axis(float const radians);
		static matrix3x3 rotation_around_axis(vector3 const& axis, float const radians);

		static const matrix3x3 IDENTITY;
	};

	inline  matrix3x3::matrix3x3()
		: values {0}
	{
	}

	inline matrix3x3::matrix3x3(
		float const m00, float const m01, float const m02,
		float const m10, float const m11, float const m12,
		float const m20, float const m21, float const m22)
	{
		values[0][0] = m00;
		values[0][1] = m01;
		values[0][2] = m02;

		values[1][0] = m10;
		values[1][1] = m11;
		values[1][2] = m12;

		values[2][0] = m20;
		values[2][1] = m21;
		values[2][2] = m22;
	}

	inline matrix3x3 matrix3x3::operator*(matrix3x3 const& m) const
	{
		return matrix3x3{
			values[0][0] * m.values[0][0] + values[0][1] * m.values[1][0] + values[0][2] * m.values[2][0],
			values[0][0] * m.values[0][1] + values[0][1] * m.values[1][1] + values[0][2] * m.values[2][1],
			values[0][0] * m.values[0][2] + values[0][1] * m.values[1][2] + values[0][2] * m.values[2][2],

			values[1][0] * m.values[0][0] + values[1][1] * m.values[1][0] + values[1][2] * m.values[2][0],
			values[1][0] * m.values[0][1] + values[1][1] * m.values[1][1] + values[1][2] * m.values[2][1],
			values[1][0] * m.values[0][2] + values[1][1] * m.values[1][2] + values[1][2] * m.values[2][2],

			values[2][0] * m.values[0][0] + values[2][1] * m.values[1][0] + values[2][2] * m.values[2][0],
			values[2][0] * m.values[0][1] + values[2][1] * m.values[1][1] + values[2][2] * m.values[2][1],
			values[2][0] * m.values[0][2] + values[2][1] * m.values[1][2] + values[2][2] * m.values[2][2]};
	}

	inline matrix3x3 matrix3x3::scale(float const x, float const y, float const z)
	{
		return matrix3x3{
			x, 0.0f, 0.0f,
			0.0f, y, 0.0f,
			0.0f, 0.0f, z};
	}

	inline  matrix3x3 matrix3x3::uniform_scale(float const s)
	{
		return matrix3x3{
			s, 0.0f, 0.0f,
			0.0f, s, 0.0f,
			0.0f, 0.0f, s};
	}

	inline matrix3x3 matrix3x3::rotation_around_x_axis(float const radians)
	{
		return matrix3x3{
			1.0f, 0.0f, 0.0f,
			0.0f, std::cos(radians), std::sin(radians),
			0.0f, -std::sin(radians), std::cos(radians)};
	}

	inline matrix3x3 matrix3x3::rotation_around_y_axis(float const radians)
	{
		return matrix3x3{
			std::cos(radians), 0.0f, -std::sin(radians),
			0.0f, 1.0f, 0.0f,
			std::sin(radians), 0.0f, std::cos(radians)};
	}

	inline matrix3x3 matrix3x3::rotation_around_z_axis(float const radians)
	{
		return matrix3x3{
			std::cos(radians), std::sin(radians), 0.0f,
			-std::sin(radians), std::cos(radians), 0.0f,
			0.0f, 0.0f, 1.0f};
	}

	inline matrix3x3 matrix3x3::rotation_around_axis(vector3 const& axis, float const radians)
	{
		vector3 axis_normalized{axis.normalized()};

		float const cos_value{std::cos(radians)};
		float const sin_value{std::sin(radians)};

		return matrix3x3{
			axis_normalized.x * axis_normalized.x * (1.0f - cos_value) + cos_value,
			axis_normalized.x * axis_normalized.y * (1.0f - cos_value) + axis_normalized.z * sin_value,
			axis_normalized.x * axis_normalized.z * (1.0f - cos_value) - axis_normalized.y * sin_value,

			axis_normalized.x * axis_normalized.y * (1.0f - cos_value) - axis_normalized.z * sin_value,
			axis_normalized.y * axis_normalized.y * (1.0f - cos_value) + cos_value,
			axis_normalized.y * axis_normalized.z * (1.0f - cos_value) + axis_normalized.x * sin_value,

			axis_normalized.x * axis_normalized.z * (1.0f - cos_value) + axis_normalized.y * sin_value,
			axis_normalized.y * axis_normalized.z * (1.0f - cos_value) - axis_normalized.x * sin_value,
			axis_normalized.z * axis_normalized.z * (1.0f - cos_value) + cos_value};
	}

	inline vector3 operator*(vector3 const& v, matrix3x3 const& m)
	{
		return vector3{
			v.x * m.values[0][0] + v.y * m.values[1][0] + v.z * m.values[2][0],
			v.x * m.values[0][1] + v.y * m.values[1][1] + v.z * m.values[2][1],
			v.x * m.values[0][2] + v.y * m.values[1][2] + v.z * m.values[2][2]};
	}
}

#endif
