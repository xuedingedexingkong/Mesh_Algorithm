#include"MeshAlgorithm.h"


void meshAlorithm::meshAlgorithmbase::findBox(const std::vector<P>& points) 
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

std::vector<double>meshAlorithm::meshAlgorithmbase::getBox() {
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