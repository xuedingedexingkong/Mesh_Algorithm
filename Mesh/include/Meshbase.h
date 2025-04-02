#pragma once
#include<memory>


class Point;
class Edge;
class Triangle;


template <typename T, typename... Args>
std::shared_ptr<T> Smart(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}



//class Halfedge
//{
//public:
//	using P = std::shared_ptr<Point>;
//	using E = std::shared_ptr<Edge>;
//	using H = std::shared_ptr<Halfedge>;
//private:
//	P origin = nullptr;
//	P end = nullptr;
//	E oppsite = nullptr;
//	H next = nullptr;
//	H prev = nullptr;
//};