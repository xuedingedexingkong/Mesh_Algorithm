#pragma once
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "Meshbase.h"


using P = std::shared_ptr<Point>;
using E = std::shared_ptr<Edge>;
using T = std::shared_ptr<Triangle>;

bool operator==(const P& point1, const P& point2);
bool operator==(const E& edge1, const E& edge2);
P operator-(const P& point1, const P& point2);




class Point
{
public:
	Point(double X = 0, double Y = 0, double Z = 0) :x(X), y(Y), z(Z) {};
	struct Hash { std::size_t operator()(const P& point) const; };
	inline double getx() { return x; };
	inline double gety() { return y; };
	inline double getz() { return z; };
	inline void setx(double X) { x = X; };
	inline void sety(double Y) { y = Y; };
	inline void setz(double Z) { z = Z; };

	double distance(P point);
	inline double abs() { return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z); };
	inline double abs(P point) {
		return std::sqrt(point->getx() * point->getx() + point->gety() + point->gety() +
			point->getz() * point->getz());
	};
private:
	double x, y, z;
};

class Edge
{
public:
	
	Edge(P a, P b) :node1(a), node2(b) {};
	struct Hash { std::size_t operator()(const E& edge) const; };
	inline P getNode1() { return node1; };
	inline P getNode2() { return node2; };

	inline void setNode1(P& node)
	{
		node1 = node;
	};
	inline void setNode2(P& node)
	{
		node2 = node;
	};
	inline double length()
	{
		return node1->distance(node2);
	};
	bool findNode(const P& node);
private:
	P node1 = nullptr;
	P node2 = nullptr;
};

class Triangle
{
public:
	Triangle() = default;
	Triangle(P a, P b, P c) 
	{
		edge1 = Smart<Edge>(a, b);
		edge2 = Smart<Edge>(b, c);
		edge3 = Smart<Edge>(c, a);
	}
	Triangle(E a, E b, E c) :edge1(a), edge2(b), edge3(c) {};
	std::size_t operator()(const T& triangle);

	std::vector<P> getNodes();
	std::vector<E> getEdges();
	bool findEdge(const E& edge);
	bool findNode(const P& node);
private:
	E edge1;
	E edge2;
	E edge3;
};

class Mesh
{
public:
	
	Mesh() {};
	const std::vector<T>& getTriangle();
	const std::unordered_set<P>& getNode();

	void setTriangle(std::vector<T>& tri);
	void inserTriangle(T& triangle);

	~Mesh()
	{
		std::cout << "[Mesh] Success to clear mesh.\n";
	}
private:
	std::vector<T> Physicaltriangle;
	std::unordered_set<P> Physicalnode;
};