#include"MeshAlgorithm.h"
using namespace meshAlorithm;

void meshAlgorithmbase::findBox(const std::vector<P>& points) 
{
	xmin = points[0]->getx();
	xmax = xmin;
	ymin = points[0]->gety();
	ymax = ymin;

	if (dimention == 3) {
		zmin = points[0]->getz();
		zmax = points[0]->getz();
	}

	for (auto& point : points) {
		if (point->getx() > xmax)
			xmax = point->getx();
		if (point->getx() < xmin)
			xmin = point->getx();
		if (point->gety() > ymax)
			ymax = point->gety();
		if (point->gety() < ymin)
			ymin = point->gety();

		if (dimention == 3) {
			if (point->getz() > zmax)
				zmax = point->getz();
			if (point->getz() < zmin)
				zmin = point->getz();
		}

	}
}

std::vector<double>meshAlgorithmbase::getBox() {
	std::vector<double> box;
	box.emplace_back(xmin);
	box.emplace_back(xmax);
	box.emplace_back(ymin);
	box.emplace_back(ymax);

	if(dimention == 3)
	{
		box.emplace_back(zmin);
		box.emplace_back(zmax);
	}
	else
	{
		box.emplace_back(0);
		box.emplace_back(0);
	}

	return box;
}

Circumcircle meshAlgorithmbase::calCircumcircle(T& triangle)
{
	P point;
	auto points = triangle->getNodes();
	double circumcircle = 2 * (points[0]->getx() * (points[1]->gety() - points[2]->gety()) +
		points[1]->getx() * (points[2]->gety() - points[0]->gety()) + points[2]->getx() * (points[0]->gety() - points[1]->gety()));
	double x = ((points[0]->getx() * points[0]->getx() + points[0]->gety() * points[0]->gety()) * (points[1]->gety() - points[2]->gety()) +
		(points[1]->getx() * points[1]->getx() + points[1]->gety() * points[1]->gety()) * (points[2]->gety() - points[0]->gety()) +
		(points[2]->getx() * points[2]->getx() + points[2]->gety() * points[2]->gety()) * (points[0]->gety() - points[1]->gety())) / circumcircle;
	double y = ((points[0]->getx() * points[0]->getx() + points[0]->gety() * points[0]->gety()) * (points[2]->getx() - points[1]->getx()) +
		(points[1]->getx() * points[1]->getx() + points[1]->gety() * points[1]->gety()) * (points[0]->getx() - points[2]->getx()) +
		(points[2]->getx() * points[2]->getx() + points[2]->gety() * points[2]->gety()) * (points[1]->getx() - points[0]->getx()));
	point->setx(x);
	point->sety(y);


	Circumcircle circle;
	circle.center = point;
	circle.diameter = circumcircle;
	return circle;
}

E meshAlgorithmbase::findCommonedge(T& triangle1, T& triangle2)
{
	if(triangle1 == nullptr || triangle2 == nullptr)
	{
		std::string err = __LINE__ + "Triangle is not found.";
		meshError(err);
	}

	auto edges = triangle2->getEdges();
	for(auto& edge: triangle1->getEdges())
	{
		if(std::find(edges.begin(), edges.end(), edge) != edges.end())
		{
			return edge;
		}
	}

	return nullptr;
}

bool meshAlgorithmbase::inCircle(P& point, Circumcircle& cir) 
{
	auto p = point - cir.center;
	if(p->abs() < cir.diameter / 2.0)
	{
		return true;
	}

	return false;
}