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
	auto point = Smart<Point>();
	auto points = triangle->getNodes();
	double x1 = points[0]->getx();
	double y1 = points[0]->gety();
	double x2 = points[1]->getx();
	double y2 = points[1]->gety();
	double x3 = points[2]->getx();
	double y3 = points[2]->gety();

	double x0 = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) - (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
		(2 * (x3 - x1) * (y2 - y1) - 2 * (x2 - x1) * (y3 - y1));
	double y0 = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) - (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
		(2 * (y3 - y1) * (x2 - x1) - 2 * (y2 - y1) * (x3 - x1));

	point->setx(x0);
	point->sety(y0);

	double dis1 = point->distance(triangle->getNodes()[0]);

	Circumcircle circle;
	circle.center = point;
	circle.radius = dis1;
	return circle;
}

E meshAlgorithmbase::findCommonedge(T& triangle1, T& triangle2)
{
	if(triangle1 == nullptr || triangle2 == nullptr)
	{
		std::string err = "[Mesh] Triangle is not found.";
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
	if(p->abs() < cir.radius)
	{
		return true;
	}

	return false;
}

std::vector<P>& meshAlgorithmbase::generate2dPoints(double xmin, double xmax, double ymin, double ymax, size_t pointnum)
{
	//std::random_device seed;
	size_t seed = 10;
	std::mt19937 gen(seed);

	std::uniform_real_distribution<> dis(0.0, 1.0);

	double dx = xmax - xmin;
	double dy = ymax - ymin;
	for(size_t i = 0; i < pointnum; i++)
	{
		double x = dis(gen) * dx + xmin;
		double y = dis(gen) * dy + ymin;
		P point = Smart<Point>(x, y);
		generate_Points.emplace_back(point);
	}

	return generate_Points;
}