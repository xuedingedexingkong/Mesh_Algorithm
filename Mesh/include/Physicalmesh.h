#pragma once
#include<vector>
#include<cmath>

#include"Meshbase.h"

class Point
{
public:
	Point(float X = 0, float Y = 0, float Z = 0) :x(X), y(Y), z(Z) {};
	inline float getx() { return x; };
	inline float gety() { return y; };
	inline float getz() { return z; };
private:
	float x, y, z;
};

class Edge
{
public:
	using P = std::shared_ptr<Point>;
	Edge(P a, P b) :node1(a), node2(b) {};
	inline P getNode1() { return node1; };
	inline P getNode2() { return node2; };
private:
	P node1 = nullptr;
	P node2 = nullptr;
};

class Triangle
{
public:
	using P = std::shared_ptr<Point>;
	using E = std::shared_ptr<Edge>;
	Triangle(E a, E b, E c) :edge1(a), edge2(b), edge3(c) {};
	std::vector<P> getNodes();
	std::vector<E> getEdges();
private:
	E edge1;
	E edge2;
	E edge3;
};

class Mesh
{
public:
	using T = std::shared_ptr<Triangle>;
	Mesh() {};
	
private:
	std::vector<T>Physicaltriangle;
};