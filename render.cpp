#include "render.h"
#include "chars.h"

#define X_OFFSET 3

namespace Tmpl8
{
	void render::Draw(vec2* _vectors, int _length, float _xPos, float _yPos, float _angle, vec2 _scale) {

		math math;
		double radiant = math.DegToRad(_angle);

		for (int i = 0; i < _length; i++)
		{
			vec2 xy1 = vec2(0, 0);
			vec2 xy2 = vec2(0, 0);

			xy1 = (math.RotationMatrix(_vectors[i], radiant));

			if (i == _length - 1)
				xy2 = (math.RotationMatrix(_vectors[0], radiant));
			else
				xy2 = (math.RotationMatrix(_vectors[i + 1], radiant));

			xy1 *= _scale;
			xy2 *= _scale;

			screen->Line(xy1.x + _xPos, xy1.y + _yPos, xy2.x + _xPos, xy2.y + _yPos, 0xffffff);
		}
	}
	void render::Draw(vec2* _vectors, int _length, float _xPos, float _yPos, float _angle, vec2 _scale, Tmpl8::Pixel _pixel) {

		math math;
		double radiant = math.DegToRad(_angle);

		for (int i = 0; i < _length; i++)
		{
			vec2 xy1 = vec2(0, 0);
			vec2 xy2 = vec2(0, 0);

			xy1 = (math.RotationMatrix(_vectors[i], radiant));

			if (i == _length - 1)
				xy2 = (math.RotationMatrix(_vectors[0], radiant));
			else
				xy2 = (math.RotationMatrix(_vectors[i + 1], radiant));

			xy1 *= _scale;
			xy2 *= _scale;

			screen->Line(xy1.x + _xPos, xy1.y + _yPos, xy2.x + _xPos, xy2.y + _yPos, _pixel);
		}
	}
	void render::Draw(vec2* _vectors, int _length, float _xPos, float _yPos, vec2 _scale) {

		for (int i = 0; i < _length; i++)
		{
			vec2 xy1 = vec2(0, 0);
			vec2 xy2 = vec2(0, 0);

			xy1 = _vectors[i];

			if (i == _length - 1)
				xy2 = _vectors[0];
			else
				xy2 = _vectors[i + 1];

			xy1 *= _scale;
			xy2 *= _scale;

			screen->Line(xy1.x + _xPos, xy1.y + _yPos, xy2.x + _xPos, xy2.y + _yPos, 0xffffff);
		}
	}

	void render::Text(char* _a, int _len, const vec2& _offset, const vec2& _scale, Pixel _pixel, bool _center) {

		float XPos = 0;
		if (_center)
			XPos = _offset.x - (((X_OFFSET * _scale.x) * _len) / 2);
		else
			XPos = _offset.x;

		for (int i = 0; i < _len; i++) {
			switch (_a[i])
			{
			case 'a':
				Draw(char_A, charPolygonLength[0], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'b':
				Draw(char_B, charPolygonLength[1], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'c':
				Draw(char_C, charPolygonLength[2], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'd':
				Draw(char_D, charPolygonLength[3], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'e':
				Draw(char_E, charPolygonLength[4], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'f':
				Draw(char_F, charPolygonLength[5], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'g':
				Draw(char_G, charPolygonLength[6], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'h':
				Draw(char_H, charPolygonLength[7], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'i':
				Draw(char_I, charPolygonLength[8], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'j':
				Draw(char_J, charPolygonLength[9], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'k':
				Draw(char_K, charPolygonLength[10], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'l':
				Draw(char_L, charPolygonLength[11], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'm':
				Draw(char_M, charPolygonLength[12], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'n':
				Draw(char_N, charPolygonLength[13], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'o':
				Draw(char_O, charPolygonLength[14], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'p':
				Draw(char_P, charPolygonLength[15], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'q':
				Draw(char_Q, charPolygonLength[16], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'r':
				Draw(char_R, charPolygonLength[17], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 's':
				Draw(char_S, charPolygonLength[18], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 't':
				Draw(char_T, charPolygonLength[19], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'u':
				Draw(char_U, charPolygonLength[20], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'v':
				Draw(char_V, charPolygonLength[21], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'w':
				Draw(char_W, charPolygonLength[22], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'x':
				Draw(char_X, charPolygonLength[23], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'y':
				Draw(char_Y, charPolygonLength[24], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case 'z':
				Draw(char_Z, charPolygonLength[25], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '0':
				Draw(char_ZERO, charPolygonLength[26], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '1':
				Draw(char_ONE, charPolygonLength[27], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '2':
				Draw(char_TWO, charPolygonLength[28], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '3':
				Draw(char_THREE, charPolygonLength[29], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '4':
				Draw(char_FOUR, charPolygonLength[30], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '5':
				Draw(char_FIVE, charPolygonLength[31], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '6':
				Draw(char_SIX, charPolygonLength[32], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '7':
				Draw(char_SEVEN, charPolygonLength[33], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '8':
				Draw(char_EIGHT, charPolygonLength[34], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '9':
				Draw(char_NINE, charPolygonLength[35], XPos, _offset.y, 0, _scale, _pixel);
				break;
			case '_':
				Draw(char_EMPTY, charPolygonLength[36], XPos, _offset.y, 0, _scale, _pixel);
				break;
			default:
				break;
			}
			XPos += X_OFFSET * _scale.x;
		}
	}

	void render::Number(int _number, const vec2& _offset, const vec2& _scale, Pixel _pixel, bool _center) {
		char intChars[10];
		int length = ceil(log10(_number + 1));
		sprintf(intChars, "%i", _number);
		Text(intChars, length, _offset, _scale, _pixel, _center);
	}

	void render::Circle(float _radius, vec2 _pos, Pixel _pixel) {

		if (_radius != 0) {
			math math;

			for (int i = 0; i < 360; i++)
			{
				vec2 pixelPos = _pos;
				pixelPos.x += _radius * sin(math.DegToRad(i));
				pixelPos.y += _radius * cos(math.DegToRad(i));
				screen->Plot(pixelPos.x, pixelPos.y, _pixel);
			}
		}
	}
};
