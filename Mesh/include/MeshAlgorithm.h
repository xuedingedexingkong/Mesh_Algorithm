#pragma once
#include"Physicalmesh.h"


namespace meshAlorithm {
	class meshAlgorithmbase {
	public:
		meshAlgorithmbase() = default;
		meshAlgorithmbase(std::size_t dim) :dimention(dim) {};
		void findBox(const std::vector<P>& points);

		std::vector<double> getBox();
		std::size_t inline getDimension() { return dimention; };
	private:
		inline void setDimension(const std::size_t dim) 
		{
			dimention = dim;
		};
		std::size_t dimention = 2;
		double xmin, xmax, ymin, ymax, zmin, zmax;
	};
}