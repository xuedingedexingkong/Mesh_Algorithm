#include"Delaunay.h"

#include <string>

#include "Meshtovtu.h"

std::shared_ptr<Mesh>& meshAlorithm::Delaunay::pointsMesh(meshAlorithm::DELAUNAY method) {


	if (method == DELAUNAY::Bowyer_Watson) 
	{
		std::cout << "[Mesh] [Delaunay] Mesh Algorithm: Boyer-Watson\n";
		return this->Bowyer_Watsonsolver();
	}
}

T meshAlorithm::Delaunay::findSupertranigle() 
{
	if (getDimension() == 3)
		return nullptr;

	findBox(points);
	
	auto box = getBox();
	auto midPoint = Smart<Point>();
	midPoint->setx((box[0] + box[1]) / 2.0);
	midPoint->sety((box[2] + box[3]) / 2.0);

	double dmax = std::max(box[1] - box[0], box[3] - box[2]);
	auto point1 = Smart<Point>();
	auto point2 = Smart<Point>();
	auto point3 = Smart<Point>();
	point1->setx(midPoint->getx());
	point1->sety(midPoint->gety() + 2 * dmax);
	point2->setx(midPoint->getx() - 2 * dmax);
	point2->sety(midPoint->gety() - dmax);
	point3->setx(midPoint->getx() + 2 * dmax);
	point3->sety(midPoint->gety() - dmax);

	T superTriangle = Smart<Triangle>(point1, point2, point3);

	return superTriangle;
}

//Bowyer-Watson
std::shared_ptr<Mesh>& meshAlorithm::Delaunay::Bowyer_Watsonsolver() {
	//step1: structure super tranigle
	std::cout << "[Mesh] [Delaunay] Init mesh supertriangle.\n";
	if (points.size() < 3) {
		meshError("Points number is too small.");
	}
	T superTriangle = findSupertranigle();
	auto initpoints = superTriangle->getNodes();

	//step2:insert point
	std::cout << "[Mesh] [Delaunay] Begin to insert point.\n";
	std::unordered_map<T, Circumcircle>triangleCircle;
	this->mesh = Smart<Mesh>();
	auto supercir = calCircumcircle(superTriangle);
	triangleCircle[superTriangle] = supercir;

	size_t num = 0;

	for(auto& point: this->points)
	{
		FileIOVtu test;

		test.meshTovtu(triangleCircle, "D:\\work\\TCAD\\My_Soft\\build\\test\\Delaunaymesh_" + std::to_string(num) + ".vtu");
		if(num == 0) test.nodeTovtu(this->points, "D:\\work\\TCAD\\My_Soft\\build\\test\\Delaunaynode_" + std::to_string(num) + ".vtu");
		num++;

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
			auto comtri = commonTriangle[0]->getNodes();
			T tr1 = Smart<Triangle>(comtri[0], comtri[1], point);
			T tr2 = Smart<Triangle>(comtri[0], comtri[2], point);
			T tr3 = Smart<Triangle>(comtri[1], comtri[2], point);
			auto cir1 = calCircumcircle(tr1);
			auto cir2 = calCircumcircle(tr2);
			auto cir3 = calCircumcircle(tr3);

			triangleCircle[tr1] = cir1;
			triangleCircle[tr2] = cir2;
			triangleCircle[tr3] = cir3;

			triangleCircle.erase(commonTriangle[0]);
		}
		//other insert
		else 
		{

			for(size_t i = 0; i < commonTriangle.size() - 1; i++)
			{
				for(size_t j = i + 1; j < commonTriangle.size(); j++)
				{
					auto common = findCommonedge(commonTriangle[i], commonTriangle[j]);
					if(common == nullptr)
					{
						continue;
					}
					triangleCircle.erase(commonTriangle[i]);
					triangleCircle.erase(commonTriangle[j]);

					//get noncommon edge
					auto nonCommonedge = commonTriangle[i]->getEdges();
					for (auto& nonedge : commonTriangle[j]->getEdges())
					{
						auto it = find(nonCommonedge.begin(), nonCommonedge.end(), nonedge);
						if (it == nonCommonedge.end())
						{
							nonCommonedge.emplace_back(nonedge);
						}
						else
						{
							nonCommonedge.erase(it);
						}
					}
					T tr1 = Smart<Triangle>(nonCommonedge[0]->getNode1(), nonCommonedge[0]->getNode2(), point);
					T tr2 = Smart<Triangle>(nonCommonedge[1]->getNode1(), nonCommonedge[1]->getNode2(), point);
					T tr3 = Smart<Triangle>(nonCommonedge[2]->getNode1(), nonCommonedge[2]->getNode2(), point);
					T tr4 = Smart<Triangle>(nonCommonedge[3]->getNode1(), nonCommonedge[3]->getNode2(), point);
					auto cir1 = calCircumcircle(tr1);
					auto cir2 = calCircumcircle(tr2);
					auto cir3 = calCircumcircle(tr3);
					auto cir4 = calCircumcircle(tr4);
					triangleCircle[tr1] = cir1;
					triangleCircle[tr2] = cir2;
					triangleCircle[tr3] = cir3;
					triangleCircle[tr4] = cir4;
				}
			}
			

			
		}
	}

	std::cout << "[Mesh] [Delaunay] Success to mesh structure.\n";


	return mesh;
}

