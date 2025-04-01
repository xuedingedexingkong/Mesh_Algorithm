#pragma once
#include <random>
#include"Physicalmesh.h"
#include"Mesherrormag.h"

namespace meshAlorithm {
	struct Circumcircle
	{
		P center;
		double radius;
	};

	class meshAlgorithmbase {
	public:
		meshAlgorithmbase() = default;
		meshAlgorithmbase(std::size_t dim) :dimention(dim) {};
		Circumcircle calCircumcircle(T& triangle);
		E findCommonedge(T& triangle1, T& triangle2);
		void findBox(const std::vector<P>& points);
		bool inCircle(P& point, Circumcircle& cir);
		std::vector<P>& generate2dPoints(double xmin, double xmax, double ymin, double ymax, size_t pointnum);

		std::vector<double> getBox();
		std::size_t inline getDimension() { return dimention; };
	private:
		inline void setDimension(const std::size_t dim) 
		{
			dimention = dim;
		};

		std::vector<P> generate_Points;
		std::size_t dimention = 2;
		double xmin, xmax, ymin, ymax, zmin, zmax;
	};
}