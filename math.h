#pragma once
#include "precomp.h"

namespace Tmpl8
{
	class math
	{
	public:
		static double DegToRad(float _angle);
		vec2 RotationMatrix(vec2 _position, double _radiant);
		static float Dist(const vec2& _posA, const vec2& _posB);
	};
};