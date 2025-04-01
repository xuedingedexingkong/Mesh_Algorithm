
#include "Delaunay.h"
#include "Meshtovtu.h"

using namespace meshAlorithm;

int main()
{
	std::shared_ptr<Delaunay> test = Smart<Delaunay>();
	auto& point = test->generate2dPoints(0, 10, 0, 10, 10);
	test->setPoints(point);
	auto& mesh = test->pointsMesh(DELAUNAY::Bowyer_Watson);

	FileIOVtu t;
	t.meshTovtu(mesh, "D:\\work\\TCAD\\My_Soft\\build\\test\\Delaunay.vtu");
}