#include"Delaunay.h"

std::shared_ptr<Mesh> meshAlorithm::Delaunay::pointsMesh() {
	return this->solver();
}

T meshAlorithm::Delaunay::findSupertranigle() 
{
	if (getDimension() == 3)
		return nullptr;

	findBox(points);
	
	auto box = getBox();
	P midPoint;
	midPoint->setx((box[0] + box[1]) / 2.0);
	midPoint->sety((box[2] + box[3]) / 2.0);

	double dmax = std::max(box[1] - box[0], box[3] - box[2]);
	P point1, point2, point3;
	point1->setx(midPoint->getx());
	point1->sety(midPoint->gety() + 20 * dmax);
	point2->setx(midPoint->getx() - 20 * dmax);
	point2->sety(midPoint->gety() - dmax);
	point3->setx(midPoint->getx() + 20 * dmax);
	point3->sety(midPoint->gety() - dmax);

	T superTriangle = std::make_shared<Triangle>(point1, point2, point3);

	return superTriangle;
}

//Bowyer-Watson
std::shared_ptr<Mesh> meshAlorithm::Delaunay::solver() {
	//step1: structure super tranigle
	if (points.size() < 3) {
		std::cout << "Points number is too small.";
	}
	findSupertranigle();

	//step2: 
}