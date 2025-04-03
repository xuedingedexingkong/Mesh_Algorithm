#include <chrono>
#include "Delaunay.h"
#include "Meshtovtu.h"

using namespace meshAlorithm;

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::shared_ptr<Delaunay> test = Smart<Delaunay>();
	test->uniform2dPoints(0, 10, 50, 0, 10, 50);
	test->uniform2dPoints(0, 5, 60, -5, -0.2, 20);
	auto& point = test->uniform2dPoints(5.2, 10, 100, -5, -0.2, 20);
	test->setPoints(point);
	auto& mesh = test->pointsMesh(DELAUNAY::Bowyer_Watson);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Program Execution Time: " << duration.count() << " milliseconds." << std::endl;


	FileIOVtu t;
	//t.meshTovtu(mesh->getNode(), "D:\\work\\TCAD\\My_Soft\\build\\test\\Delaunay.vtu");
	t.meshTovtu(mesh, "D:\\work\\TCAD\\My_Soft\\build\\test\\Delaunay.vtu");


}