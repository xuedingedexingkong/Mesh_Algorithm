#include"Physicalmesh.h"

P operator-(const P& point1, const P& point2)
{
	auto point3 = Smart<Point>();
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

double Point::distance(P point)
{
	auto x1 = point->getx() - this->getx();
	auto y1 = point->gety() - this->gety();
	auto z1 = point->getz() - this->getz();

	return sqrt(x1 * x1 + y1 * y1 + z1 * z1);
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

void Mesh::setTriangle(std::vector<T>& tri)
{
	Physicaltriangle = std::move(tri);

	//update Physicalnode
	for(auto& tri: Physicaltriangle)
	{
		auto nodes = tri->getNodes();
		for (auto& node : nodes) 
		{
			Physicalnode.insert(node);
		}
	}
}

const std::vector<T>& Mesh::getTriangle()
{
	return Physicaltriangle;
}

const std::unordered_set<P>& Mesh::getNode()
{
	return Physicalnode;
}
