#include "Meshtovtu.h"

#include "MeshAlgorithm.h"
#include "Physicalmesh.h"

void FileIOVtu::meshTovtu(const std::shared_ptr<Mesh>& mesh, std::string cwd)
{
	auto& triangles = mesh->getTriangle();

	meshTovtu(triangles, cwd);
}

void FileIOVtu::meshTovtu(const std::vector<T>& triangles, std::string cwd)
{
	std::cout << "[FileIO] Begin to print mesh.\n";

	std::ofstream file(cwd);
	if (!file.is_open())
	{
		meshError("[FileIO] Not found file: " + cwd);
	}

	file << "<?xml version=\"1.0\"?>" << std::endl;
	file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;
	file << "  <UnstructuredGrid>" << std::endl;
	file << "    <Piece NumberOfPoints=\"" << 3 * triangles.size() << "\" NumberOfCells=\"" << triangles.size() << "\">" << std::endl;
	file << "      <Points>" << std::endl << "        <DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;

	for (auto& triangle : triangles)
	{
		for (auto& node : triangle->getNodes())
		{
			file << "          " << node->getx() << " " << node->gety() << " " << node->getz() << "\n";
		}
	}
	file << "        </DataArray>" << std::endl << "      </Points>" << std::endl << "      <Cells>" << std::endl;
	file << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;

	for (size_t i = 0; i < triangles.size(); i++)
	{
		file << "          " << i * 3 << " " << i * 3 + 1 << " " << i * 3 + 2 << "\n";
	}
	file << "        </DataArray>" << std::endl << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << "\n";

	for (size_t i = 0; i < triangles.size(); i++)
	{
		file << "          " << i * 3 + 3 << std::endl;
	}
	file << "        </DataArray>" << std::endl << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;
	for (size_t i = 0; i < triangles.size(); i++)
	{
		file << "          " << 5 << std::endl;
	}
	file << "        </DataArray>" << std::endl << "      </Cells>" << std::endl << "    </Piece>" << std::endl << "  </UnstructuredGrid>" << std::endl << "</VTKFile>";

	std::cout << "[FileIO] Success to print mesh.\n";
}

void FileIOVtu::meshTovtu(const std::unordered_map<T, meshAlorithm::Circumcircle>& triangles, std::string cwd)
{
	std::vector<T> t;
	for(auto& [triangle, circle]: triangles)
	{
		t.emplace_back(triangle);
	}

	meshTovtu(t, cwd);
}

void FileIOVtu::nodeTovtu(const std::vector<P>& nodes, std::string cwd)
{
	std::cout << "[FileIO] Begin to print nodes.\n";

	std::ofstream file(cwd);
	if (!file.is_open())
	{
		meshError("[FileIO] Not found file: " + cwd);
	}

	file << "<?xml version=\"1.0\"?>" << std::endl;
	file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;
	file << "  <UnstructuredGrid>" << std::endl;
	file << "    <Piece NumberOfPoints=\"" << nodes.size() << "\" NumberOfCells=\"" << nodes.size() << "\">" << std::endl;
	file << "      <Points>" << std::endl << "        <DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;

	for (auto& node : nodes) {

		file << "          " << node->getx() << " " << node->gety() << " " << node->getz() << "\n";
	}

	file << "        </DataArray>" << std::endl << "      </Points>" << std::endl << "      <Cells>" << std::endl;
	file << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;

	for (size_t i = 0; i < nodes.size(); i++)
	{
		file << "          " << i << std::endl;
	}
	file << "        </DataArray>" << std::endl << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << std::endl;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		file << "          " << i + 1 << std::endl;
	}
	file << "        </DataArray>" << std::endl << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		file << "          " << 1 << std::endl;
	}
	file << "        </DataArray>" << std::endl << "      </Cells>" << std::endl << "    </Piece>" << std::endl << "  </UnstructuredGrid>" << std::endl << "</VTKFile>";
}
