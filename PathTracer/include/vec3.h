#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:
	vec3() {};
	vec3(float e0, float e1, float e2) : e0{ e0 }, e1{ e1 }, e2{ e2 } {};

	inline float x() const { return e0; }
	inline float y() const { return e1; }
	inline float z() const { return e2; }
	inline float r() const { return e0; }
	inline float g() const { return e1; }
	inline float b() const { return e2; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e0, -e1, -e2); }

	inline vec3& operator+=(const vec3 &other);
	inline vec3& operator-=(const vec3 &other);
	inline vec3& operator*=(const vec3 &other);
	inline vec3& operator/=(const vec3 &other);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const { return sqrt(e0 * e0 + e1 * e1 + e2 * e2); };
	inline float squared_length() const { return e0 * e0 + e1 * e1 + e2 * e2; };
	inline void make_unit_vector();

	float e0;
	float e1;
	float e2;
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
	is >> t.e0 >> t.e1 >> t.e2;
	is >> t.e0 >> t.e1 >> t.e2;
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
	os << t.e0 << " " << t.e1 << " " << t.e2;
	return os;
}

inline void vec3::make_unit_vector() {
	float k = 1.0 / sqrt(e0 * e0 + e1 * e1 + e2 * e2);
	e0 *= k; e1 *= k; e2 *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e0 + v2.e0, v1.e1 + v2.e1, v1.e2 + v2.e2);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e0 - v2.e0, v1.e1 - v2.e1, v1.e2 - v2.e2);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e0 * v2.e0, v1.e1 * v2.e1, v1.e2 * v2.e2);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e0 / v2.e0, v1.e1 / v2.e1, v1.e2 / v2.e2);
}

inline vec3 operator*(float t, const vec3 &v) {
	return vec3(t*v.e0, t*v.e1, t*v.e2);
}

inline vec3 operator/(vec3 v, float t) {
	return vec3(v.e0 / t, v.e1 / t, v.e2 / t);
}

inline vec3 operator*(const vec3 &v, float t) {
	return vec3(t*v.e0, t*v.e1, t*v.e2);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
	return v1.e0 * v2.e0 + v1.e1 * v2.e1 + v1.e2 * v2.e2;
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3((v1.e1 * v2.e2 - v1.e2 * v2.e1),
		(-(v1.e0 * v2.e2 - v1.e2 * v2.e0)),
		(v1.e0 * v2.e1 - v1.e1 * v2.e0));
}


inline vec3& vec3::operator+=(const vec3 &v) {
	e0 += v.e0;
	e1 += v.e1;
	e2 += v.e2;
	return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
	e0 *= v.e0;
	e1 *= v.e1;
	e2 *= v.e2;
	return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
	e0 /= v.e0;
	e1 /= v.e1;
	e2 /= v.e2;
	return *this;
}

inline vec3& vec3::operator-=(const vec3& v) {
	e0 -= v.e0;
	e1 -= v.e1;
	e2 -= v.e2;
	return *this;
}

inline vec3& vec3::operator*=(const float t) {
	e0 *= t;
	e1 *= t;
	e2 *= t;
	return *this;
}

inline vec3& vec3::operator/=(const float t) {
	float k = 1.0 / t;

	e0 *= k;
	e1 *= k;
	e2 *= k;
	return *this;
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}