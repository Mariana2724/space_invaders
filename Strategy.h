#pragma once
#include "Shapes.h"
#include <list>
using namespace std;

class Strategy {
	list <Shapes*> shapes;
public:
	void refresh() {
		for (Shapes* s : shapes) {
			s->draw();
			s->movement();
		}
	}
	void add(Shapes* shape) {
		shapes.emplace_back(shape);
	}
};