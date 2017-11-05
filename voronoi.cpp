#include "voronoi.h"
#include <cmath>
#include <utility>
#include <cstdlib>

using namespace std;


// d = sqrt( Ax - Bx)^2 + (Ay - By)^2)
double eucludianDist(pair<int, int> a, pair<int, int> b) {

	double d = sqrt(pow((a.first - b.first), 2) +
		pow((a.second - b.second), 2)
	);
	return d;
}



void voronoi(int** vec, vector<pair<int, int>> &P, int xDim, int yDim) {
	for (int y = 0; y < yDim; y++) {
		for (int x = 0; x < xDim; x++) {

			auto d = eucludianDist(make_pair(x, y), P.at(0));
			int pos = 0;
			vec[y][x] = pos;
			for (auto &p : P) {
				auto temp = eucludianDist(make_pair(x, y), p);
				if (temp < d) {
					d = temp;
					vec[y][x] = pos;
				}
				pos++;
			}
		}
	}
}

vector<pair<int, int>> genSeeds(int n, int maxX, int maxY) {

	vector<pair<int, int>> v;

	for (int i = 0; i < n; ) {
		bool exist = false;
		int x = rand() % maxX;
		int y = rand() % maxY;

		for (auto e : v) {
			if (x == e.first && y == e.second) {
				exist = true;
				break;
			}
		}

		if (exist == false) {
			v.push_back(make_pair(x, y));
			i++;
		}
	}

	return v;
}