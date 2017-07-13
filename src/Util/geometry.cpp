#include "geometry.h"

std::array<int, 3> getVector(const int A[3], const int B[3]) {
	return{ B[0] - A[0], B[1] - A[1], B[2] - A[2] };
}

double getDistance(const int A[3], const int A_[3], const int B[3], const int B_[3]) {
	std::array<int, 3> u = getVector(A, A_);
	std::array<int, 3> v = getVector(B, B_);
	return abs((double)abs((B[0] - A[0]) * u[1] * v[2] + (B[1] - A[1]) * u[2] * v[0] + (B[2] - A[2]) * u[0] * v[1] - (B[2] - A[2]) * u[1] * v[0] - (B[1] - A[1]) * u[0] * v[2] - (B[0] - A[0]) * u[2] * v[1]) / (u[0] * v[1] - u[1] * v[0])) / abs(A[2] - B[2]);
}

std::array<double, 2> getLineEquation(const int A[3], const int B[3]) {
	std::array<int, 3> u = getVector(A, B);
	return{ (double)u[1] / u[0], -((double)(A[0] * u[1]) / u[0]) + A[1] };
}

double getAngle(const int A[3], const int A_[3], const int B[3], const int B_[3]) {
	std::array<int, 3> u = getVector(A, A_);
	std::array<int, 3> v = getVector(B, B_);
	return acos(abs(u[0] * v[0] + u[1] * v[1]) / (sqrt(pow(u[0], 2) + pow(u[1], 2)) * sqrt(pow(v[0], 2) + pow(v[1], 2)))) / (M_PI / 180);
}

std::array<double, 4> getPlaneEquation(const int A[3], const int B[3], const int C[3]) {
	double x = B[1] * C[2] - B[1] * A[2] - A[1] * C[2] - C[1] * B[2] + C[1] * A[2] + A[1] * B[2];
	double y = C[0] * B[2] - C[0] * A[2] - A[0] * B[2] - B[0] * C[2] + B[0] * A[2] + A[0] * C[2];
	double z = B[0] * C[1] - B[0] * A[1] - A[0] * C[1] - C[0] * B[1] + C[0] * A[1] + A[0] * B[1];
	double a = -A[0] * B[1] * C[2] + A[0] * C[1] * B[2] - B[0] * C[1] * A[2] + B[0] * A[1] * C[2] - C[0] * A[1] * B[2] + C[0] * B[1] * A[2];
	return{ x, y, z, a };
}

std::array<double, 2> getLineEquationFromPlane(const std::array<double, 4> P, const int Z) {
	return{ -P[0] / P[1], -(P[2] * Z + P[3]) / P[1] };
}

double getPointLineDistance(const int A[3], const int A_[3], const int P[3]) {
	std::array<double, 2> eq = getLineEquation(A, A_);
	return abs(eq[0] * P[0] - P[1] + eq[1]) / sqrt(pow(eq[0], 2) + 1);
}
