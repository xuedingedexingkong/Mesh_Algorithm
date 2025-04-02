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

bool operator==(const T& triangle1, const T& triangle2)
{
	auto edge1 = triangle1->getEdges();
	auto edge2 = triangle2->getEdges();

	for(auto& edge: edge1)
	{
		if(std::find(edge2.begin(), edge2.end(), edge) == edge2.end())
		{
			return false;
		}
	}

	return true;
}

size_t Point::Hash::operator() (const P& point) const
{
	return std::hash<double>()(point->getx()) ^ std::hash<double>()(point->gety());
}

size_t Edge::Hash::operator()(const E& edge) const
{
	size_t h1 = std::hash<P>()(edge->getNode1());
	size_t h2 = std::hash<P>()(edge->getNode2());

	return h1 ^ h2;
}

std::size_t Triangle::operator()(const T& triangle)
{
	auto edges = triangle->getEdges();
	size_t h1 = std::hash<E>()(edges[0]);
	size_t h2 = std::hash<E>()(edges[1]);
	size_t h3 = std::hash<E>()(edges[2]);

	return h1 ^ h2 ^ h3;
}


double Point::distance(P point)
{
	auto x1 = point->getx() - this->getx();
	auto y1 = point->gety() - this->gety();
	auto z1 = point->getz() - this->getz();

	return sqrt(x1 * x1 + y1 * y1 + z1 * z1);
}

bool Edge::findNode(const P& node)
{
	if(this->node1 == node || this->node2 == node)
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

bool Triangle::findEdge(const E& edge)
{
	if(edge == this->edge1 || edge == this->edge2 || edge == this->edge3)
	{
		return true;
	}

	return false;
}

bool Triangle::findNode(const P& node)
{
	auto edges = this->getEdges();
	bool inEdge = false;
	for(auto& edge: edges)
	{
		inEdge = edge->findNode(node);
		if (inEdge == true)
			return true;
	}

	return false;
}


void Mesh::setTriangle(std::vector<T>& tri)
{
	Physicaltriangle = std::move(tri);

	//update Physicalnode
	for(auto& tri: Physicaltriangle)
	{
		inserTriangle(tri);
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

void Mesh::inserTriangle(T& triangle)
{
	Physicaltriangle.emplace_back(triangle);

	auto nodes = triangle->getNodes();
	for (auto& node : nodes)
	{
		Physicalnode.insert(node);
	}
}
