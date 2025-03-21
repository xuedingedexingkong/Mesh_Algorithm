#pragma once


//数据结构类-point
class Point_base {
public:
	Point_base(float X = 0, float Y = 0, float Z = 0) :x(X), y(Y), z(Z) {};
	inline float getcoorx() {
		return this->x;
	};
	inline float getcoory() {
		return this->y;
	}
	inline float getcoorz() {
		return this->z;
	}
private:
	float x, y, z;
};

class Point :public Point_base {

};









class Edge {
public:

private:

};

class Tranigle {
public:

private:

};