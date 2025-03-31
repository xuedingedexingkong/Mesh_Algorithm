#pragma once
#include<iostream>
#include<unordered_map>
#include"Physicalmesh.h"
#include"MeshAlgorithm.h"

namespace meshAlorithm {
	class Delaunay: public meshAlgorithmbase
	{
	public:
		Delaunay() = default;
		Delaunay(const std::vector<P>& p, std::shared_ptr<Mesh>& m) : points(p), mesh(m) {};
		inline void setPoints(const std::vector<P>& p) 
		{
			points = p;
		};

		std::shared_ptr<Mesh> pointsMesh();
	private:
		std::shared_ptr<Mesh> solver();

		T findSupertranigle();

		std::vector<P>points;
		std::shared_ptr<Mesh>mesh = nullptr;
	};
}