#pragma once
#include<vector>
#include<cmath>

#include"Meshbase.h"


using P = std::shared_ptr<Point>;
using E = std::shared_ptr<Edge>;
using T = std::shared_ptr<Triangle>;

class Point
{
public:
	Point(double X = 0, double Y = 0, double Z = 0) :x(X), y(Y), z(Z) {};
	inline double getx() { return x; };
	inline double gety() { return y; };
	inline double getz() { return z; };
	inline double setx(double X) { x = X; };
	inline double sety(double Y) { y = Y; };
	inline double setz(double Z) { z = Z; };
private:
	double x, y, z;
};

class Edge
{
public:
	
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
	Triangle(P a, P b, P c) 
	{
		edge1 = std::make_shared<Edge>(a, b);
		edge2 = std::make_shared<Edge>(b, c);
		edge3 = std::make_shared<Edge>(c, a);
	}
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
	
	Mesh() {};
	
private:
	std::vector<T>Physicaltriangle;
};