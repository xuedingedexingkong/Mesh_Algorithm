#pragma once
#include<memory>
#include "Physicalmesh.h"

//class Point;
//class Edge;

class Halfedge
{
public:
	using P = std::shared_ptr<Point>;
	using E = std::shared_ptr<Edge>;
	using H = std::shared_ptr<Halfedge>;
private:
	P origin;
	P end;
	E oppsite;
	H next;
	H prev;
};












