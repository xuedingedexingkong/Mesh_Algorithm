#include"Physicalmesh.h"


std::vector<Triangle::P> Triangle::getNodes()
{
	std::vector<Triangle::P>nodes;
	nodes.emplace_back(edge1->getNode1());
	nodes.emplace_back(edge1->getNode2());
	nodes.emplace_back(edge2->getNode2());
	return nodes;
}

std::vector<Triangle::E> Triangle::getEdges()
{
	std::vector<Triangle::E>edges;
	edges.emplace_back(edge1);
	edges.emplace_back(edge2);
	edges.emplace_back(edge3);
	return edges;
}
