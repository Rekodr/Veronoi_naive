#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "voronoi.h"
#include "time.h"
#include "createBMP.h"
#include <sys/time.h>

using namespace std;



#define COL 400
#define ROW 400

int main(int argc, char* argv[])
{
	srand(time(NULL));
	timeval start, end; 

	if (argc < 4) {
		cerr << "use: program_name  Xdim  Ydim  numSeeds" << endl;
		exit(1);
	}


	int col = atoi(argv[1]); 
	int row = atoi(argv[2]);
	int numSeeds = atoi(argv[3]);

	int** matrix = new int*[row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new int[col];
	}
	vector<pair<int, int>> P = genSeeds(numSeeds, col, row);  //{ {7,7}, {22,7}, {7,22}, {22,22} };

	cout << "computing veronoi... " << endl;
	gettimeofday(&start, NULL);
	voronoi(matrix, P, col, row);
	gettimeofday(&end, NULL); 
	cout << "done... " << endl; 

	int t = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000; 
	cout << "computation time(ms): " << t << endl;

	/*for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}*/
   
	createBMP(matrix, P, col, row, P.size());
	delete matrix;

    return 0;
}