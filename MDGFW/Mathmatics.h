#ifndef SHMATH_H
#define SHMATH_H

#include <MDGFW\VectorX.h>

class Math {
public:
	static float constrain(float value, float min, float max) {
		if (value < min) {
			value = min;
		}
		else if (value > max) {
			value = max;
		}
		return value;
	}

	static float map(float value, float min1, float max1, float min2, float max2) {
		return min2 + (max2 - min2)*((value - min1) / (max1 - min1));
	}

	static float pow(float value, int power) {
		float result = value;
		for (int i = 0; i < power; i++) {
			result *= value;
		}
		return result;
	}

	//Linear Interpolation / Linear Bázier Curve (smooth line between 2 points)
	static Vector3 lerp(Vector3 a, Vector3 b, float p) {
		return a + (b - a) * p;
	}

	//Quardratic Bázier Curve  (smooth line between 3 points)
	static Vector3 quadraticCurve(Vector3 a, Vector3 b, Vector3 c, float p) {
		Vector3 P0 = lerp(a, b, p);
		Vector3 P1 = lerp(b, c, p);
		return lerp(P0, P1, p);
	}

	//Cubic Bázier Curve (smooth line between 4 points)
	static Vector3 cubeCurve(Vector3 a, Vector3 b, Vector3 c, Vector3 d, float p) {
		Vector3 P0 = quadraticCurve(a, b, c, p);
		Vector3 P1 = quadraticCurve(b, c, d, p);
		return lerp(P0, P1, p);
	}
	/*FindClosestPoint
	finds the point on a line between point A and B that is closest to the target.
	**/
	static Vector3 findClosestPoint(Vector3 target, Vector3 a, Vector3 b) {
		float p = 0.0f;
		Vector3 closestPoint = lerp(a, b, p);
		float closestdist = closestPoint.distance(target);
		do {
			Vector3 pointOnLine = lerp(a, b, p);
			float dist = pointOnLine.distance(target);
			if (dist < closestdist) {
				closestdist = dist;
				closestPoint = pointOnLine;
			}
			p += 0.01f;
		} while (p < 1.0f);

		return closestPoint;
	}
};

#endif // !SHMATH_H
