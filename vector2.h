#pragma once

struct vector2 {
	double x;
	double y;
	vector2(double x, double y) {
		vector2::x = x;
		vector2::y = y;
	}
	vector2 normalize() {
		double len = sqrt((x * x) + (y * y));
		x /= len;
		y /= len;
		return *this;
	}
	vector2 normalize(double magnitude) {
		vector2::normalize();
		x *= magnitude;
		y *= magnitude;
		return *this;
	}
};