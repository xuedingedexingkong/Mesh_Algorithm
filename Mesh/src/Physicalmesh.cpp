#include"Physicalmesh.h"

P operator-(const P& point1, const P& point2)
{
	P point3;
	point3->setx(point1->getx() - point2->getx());
	point3->sety(point1->gety() - point2->gety());
	point3->setz(point1->getz() - point2->getz());

	return point3;
}

bool operator==(const P& point1, const P& point2)
{
	if (point1->getx() == point2->getx() && point1->gety() == point2->gety())
		return true;

	return false;
}


bool operator==(const E& edge1, const E& edge2)
{
	if(edge1->getNode1() == edge2->getNode1() && edge1->getNode2() == edge2->getNode2())
	{
		return true;
	}

	if(edge1->getNode2() == edge2->getNode1() && edge1->getNode1() == edge2->getNode2())
	{
		return true;
	}

	return false;
}


std::vector<P> Triangle::getNodes()
{
	std::vector<P>nodes;
	nodes.emplace_back(edge1->getNode1());
	nodes.emplace_back(edge1->getNode2());
	nodes.emplace_back(edge2->getNode2());
	return nodes;
}

std::vector<E> Triangle::getEdges()
{
	std::vector<E>edges;
	edges.emplace_back(edge1);
	edges.emplace_back(edge2);
	edges.emplace_back(edge3);
	return edges;
}
