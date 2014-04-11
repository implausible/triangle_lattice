// yup - implausible
// also run time executes within 10-15 seconds for largest matrix 200, 200
// though if they run several large numbers it will take a bit :-\
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef unsigned long long ullong;

// thank you knuth
ullong choose(ullong n, ullong k) {
    if (k > n) {
        return 0;
    }
    ullong r = 1;
    for (ullong d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

int vertsDiag(int m, int n, int x, int y, int run, int fall) {
	int points = 0;
	while (x < m && y < n) {
		points++;
		x += run;
		y += fall;
	}
	return points;
}

int main(int argc, char **argv) {
	string input;
	if (argc < 2) {
		input = "input.txt";
	} else {
		input = argv[1];
	}

	fstream fin, fout;
	fin.open(input, ios::in);
	fout.open("output.txt", ios::out);
	if (!fin.is_open() || !fout.is_open()) {
		cout << "There was an error opening a file for input or output, check your permissions." << endl;
		cin.get();
		return -1;
	}

	int m, n;
	ullong combinations, rows, cols, diagonals, quarterCount;

	while (fin >> m >> n) {
		combinations = choose((++m)*(++n), 3);
		rows = n*choose(m, 3);
		cols = m*choose(n, 3);
		diagonals = 0;


		for (int x = 0; x < n - 2; ++x) {
			for (int y = 0; y < m - 2; ++y) {
				// get the center line
				diagonals += 2 * choose( vertsDiag(m, n, x, y, 1, 1), 3);
				//cout << "(" << x << ", " << y << ") [1,1]: " << vertsDiag(m, n, x, y, 1, 1) << endl;
				quarterCount = 0;
				for (int run = 1; run < n/2; ++run) {
					for (int fall = (run + 1); fall < m/2; ++fall) {
						//cout << "(" << x << ", " << y << ") [" << run << "," << fall << "]: " << vertsDiag(m, n, x, y, run, fall) << endl;
						quarterCount += choose( vertsDiag(m, n, x, y, run, fall), 3);
					}
				}
				diagonals += 4*quarterCount;
			}
		}
		fout << combinations - rows - cols - diagonals << endl;
	}

	fin.close();
	fout.close();
	return 0;
}