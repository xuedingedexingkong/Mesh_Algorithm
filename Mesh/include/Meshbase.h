#pragma once
#include<memory>


class Point;
class Edge;
class Triangle;

class Halfedge
{
public:
	using P = std::shared_ptr<Point>;
	using E = std::shared_ptr<Edge>;
	using H = std::shared_ptr<Halfedge>;
private:
	P origin = nullptr;
	P end = nullptr;
	E oppsite = nullptr;
	H next = nullptr;
	H prev = nullptr;
};












