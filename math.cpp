#include "math.h"
# define M_PI           3.14159265358979323846  /* pi */

namespace Tmpl8
{
	double math::DegToRad(float _angle) {
		return _angle * M_PI / 180;
	}

	vec2 math::RotationMatrix(vec2 _position, double _radiant) {
		vec2 newPos;
		newPos.x = (_position.x * cos(_radiant)) - (_position.y * sin(_radiant));
		newPos.y = (_position.x * sin(_radiant)) + (_position.y * cos(_radiant));
		return newPos;
	}

	float math::Dist(const vec2& _posA, const vec2& _posB) {
		return pow((_posB.x - _posA.x), 2.f) + pow((_posB.y - _posA.y), 2.f);
	}
};