#pragma once
#include "precomp.h"
#include "math.h"

namespace Tmpl8 
{

	class render
	{
	private:
		Surface* screen;
	public:
		void Draw(vec2* _vectors, int _length, float _xPos, float _yPos, float _angle, vec2 _scale);
		void Draw(vec2* _vectors, int _length, float _xPos, float _yPos, float _angle, vec2 _scale, Pixel _pixel);
		void Draw(vec2* _vectors, int _length, float _xPos, float _yPos, vec2 _scale);

		void Circle(float _radius, vec2 _pos, Pixel _pixel);

		void Text(char* _a, int _len, const vec2& _offset, const vec2& _scale, Pixel _pixel, bool _center);
		void Number(int _number, const vec2& _offset, const vec2& _scale, Pixel _pixel, bool _center);

		void SetTarget(Tmpl8::Surface* _surface) { screen = _surface; }
	};
};