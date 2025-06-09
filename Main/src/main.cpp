#include <chrono>
#include "Tool.h"
#include "Delaunay.h"
#include "Meshtovtu.h"
#include<random>

using namespace meshAlorithm;

int main()
{


	auto start = std::chrono::high_resolution_clock::now();

	std::shared_ptr<Delaunay> test = Smart<Delaunay>();
	auto& point = test->generate2dPoints(0, 10, 0, 10, 10000);

	test->setPoints(point);
	auto& mesh = test->pointsMesh(DELAUNAY::Bowyer_Watson);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Program Execution Time: " << duration.count() << " milliseconds." << std::endl;


	FileIOVtu t;
	//t.meshTovtu(mesh->getNode(), "D:\\Delaunay.vtu");
	t.meshTovtu(mesh, "D:\\Delaunay.vtu");

	
}
