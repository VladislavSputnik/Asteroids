#pragma once
class vector2D
{
public:
	float x;
	float y;
	vector2D() {}
	vector2D(float v) : x(v), y(v) {}
	vector2D(float x, float y) : x(x), y(y) {}
	vector2D operator + (const vector2D& addOperand) const { return vector2D(x + addOperand.x, y + addOperand.y); }
	vector2D operator - (const vector2D& operand) const { return vector2D(x - operand.x, y - operand.y); }
	vector2D operator * (const vector2D& operand) const { return vector2D(x * operand.x, y * operand.y); }
	vector2D operator * (float operand) const { return vector2D(x * operand, y * operand); }
	void operator += (const vector2D& a) { x += a.x; y += a.y; }
	void operator *= (const vector2D& a) { x *= a.x; y *= a.y; }
	void Set(float _value) { x = _value; y = _value; }
	void Set(float _x, float _y) { x = _x; y = _y; }
};

