#pragma once
#include<iostream>
#include<unordered_map>
#include"Physicalmesh.h"
#include"MeshAlgorithm.h"

namespace meshAlorithm {
	enum DELAUNAY
	{
		Bowyer_Watson
	};

	class Delaunay: public meshAlgorithmbase
	{
	public:
		Delaunay() = default;
		Delaunay(std::vector<P>& p, std::shared_ptr<Mesh>& m) : points(move(p)), mesh(m) {};

		inline void setPoints(std::vector<P>& p) 
		{
			points = std::move(p);
		};

		std::shared_ptr<Mesh>& pointsMesh(DELAUNAY method);
	private:

		std::shared_ptr<Mesh>& Bowyer_Watsonsolver();

		T findSupertranigle();

		std::vector<P>points;
		std::shared_ptr<Mesh>mesh = nullptr;
	};
}