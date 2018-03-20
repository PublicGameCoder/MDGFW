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
	static Vector3 cubeCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, float p ) {
		Vector3 P0 = quadraticCurve( a, b, c, p );
		Vector3 P1 = quadraticCurve( b, c, d, p );
		return lerp( P0, P1, p );
	}

	//Quartic Bázier Curve (smooth line between 5 points)
	static Vector3 quarticCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, float p ) {
		Vector3 P0 = cubeCurve( a, b, c, d, p );
		Vector3 P1 = cubeCurve( b, c, d, e, p );
		return lerp( P0, P1, p );
	}

	//Quintic Bázier Curve (smooth line between 6 points)
	static Vector3 quinticCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, float p ) {
		Vector3 P0 = quarticCurve( a, b, c, d, e, p );
		Vector3 P1 = quarticCurve( b, c, d, e, f, p );
		return lerp( P0, P1, p );
	}

	//Sextic Bázier Curve (smooth line between 7 points)
	static Vector3 sexticCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, float p ) {
		Vector3 P0 = quinticCurve( a, b, c, d, e, f, p );
		Vector3 P1 = quinticCurve( b, c, d, e, f, g, p );
		return lerp( P0, P1, p );
	}

	//Septic Bázier Curve (smooth line between 8 points)
	static Vector3 septicCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, Vector3 h, float p ) {
		Vector3 P0 = sexticCurve( a, b, c, d, e, f, g, p );
		Vector3 P1 = sexticCurve( b, c, d, e, f, g, h, p );
		return lerp( P0, P1, p );
	}

	//Octic Bázier Curve (smooth line between 9 points)
	static Vector3 octic( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, Vector3 h, Vector3 i, float p ) {
		Vector3 P0 = septicCurve( a, b, c, d, e, f, g, h, p );
		Vector3 P1 = septicCurve( b, c, d, e, f, g, h, i, p );
		return lerp( P0, P1, p );
	}

	//Nonic Bázier Curve (smooth line between 10 points)
	static Vector3 nonicCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, Vector3 h, Vector3 i, Vector3 j, float p ) {
		Vector3 P0 = octic( a, b, c, d, e, f, g, h, i, p );
		Vector3 P1 = octic( b, c, d, e, f, g, h, i, j, p );
		return lerp( P0, P1, p );
	}

	//Decic Bázier Curve (smooth line between 11 points)
	static Vector3 decicCurve( Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, Vector3 h, Vector3 i, Vector3 j, Vector3 k, float p ) {
		Vector3 P0 = nonicCurve( a, b, c, d, e, f, g, h, i, j, p );
		Vector3 P1 = nonicCurve( b, c, d, e, f, g, h, i, j, k, p );
		return lerp( P0, P1, p );
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
