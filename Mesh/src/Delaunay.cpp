#include"Delaunay.h"

std::shared_ptr<Mesh> meshAlorithm::Delaunay::pointsMesh() {
	return this->Bowyer_Watsonsolver();
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
std::shared_ptr<Mesh> meshAlorithm::Delaunay::Bowyer_Watsonsolver() {
	//step1: structure super tranigle
	if (points.size() < 3) {
		std::cout << "Points number is too small.";
		return nullptr;
	}
	T superTriangle = findSupertranigle();
	auto initpoints = superTriangle->getNodes();

	//step2:insert point
	std::unordered_map<T, Circumcircle>triangleCircle;
	this->mesh = std::make_shared<Mesh>();
	auto supercir = calCircumcircle(superTriangle);
	triangleCircle[superTriangle] = supercir;
	for(auto& point: this->points)
	{
		std::vector<T>commonTriangle;
		for(auto& [triangle, circle]: triangleCircle)
		{
			if(inCircle(point, circle))
			{
				commonTriangle.emplace_back(triangle);
			}
		}

		//first insert
		if(commonTriangle.size() == 1)
		{
			if (triangleCircle.size() == 1)
			{
				T tr1 = std::make_shared<Triangle>(initpoints[0], initpoints[1], point);
				T tr2 = std::make_shared<Triangle>(initpoints[0], initpoints[2], point);
				T tr3 = std::make_shared<Triangle>(initpoints[1], initpoints[2], point);
				auto cir1 = calCircumcircle(tr1);
				auto cir2 = calCircumcircle(tr2);
				auto cir3 = calCircumcircle(tr3);

				triangleCircle[tr1] = cir1;
				triangleCircle[tr2] = cir2;
				triangleCircle[tr3] = cir3;

				triangleCircle.erase(superTriangle);
			}
			else
			{
				meshError(__LINE__ + "Not found triangle.");
			}
		}
		//other insert
		else 
		{
			if(commonTriangle.size()!=2)
			{
				meshError(__LINE__ + "Too much triangle.");
			}

			auto common = findCommonedge(commonTriangle[0], commonTriangle[1]);
			triangleCircle.erase(commonTriangle[0]);
			triangleCircle.erase(commonTriangle[1]);


			triangleCircle[] = 
		}
	}

	return nullptr;
}