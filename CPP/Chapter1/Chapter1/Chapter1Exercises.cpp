/* Exercise 15 in Chapter1
*
* Generates random Rectangles and then finds the maximal one by area and by perimeter using the
* generic findMax routine from the book
*/
#include "Chapter1Exercises.h"
#include "Chapter1Routines.h"
#include "Matrix.h"

// generates a vector of rectangles and finds the one with the maximal area
// and the one with the maximal perimeter
void chapter1::exercise15() {
	constexpr int numberOfRectangles = 10;
	constexpr int maximalSideSize = 10;

	std::vector<Rectangle<int> > rectangles;

	std::default_random_engine generator(time(NULL));
	std::uniform_int_distribution<int> distribution{ 1, maximalSideSize + 1 };

	for (int i = 0; i < numberOfRectangles; ++i) {
		int length = distribution(generator);
		int width = distribution(generator);
		rectangles.push_back(Rectangle<int>{length, width});
	}

	auto maxPerimeterRect = findMax(rectangles, PerimeterCompare<int>{});
	auto maxAreaRect = findMax(rectangles, AreaCompare<int>{});
	std::cout << "Rectanlgles:\n";
	for (auto r : rectangles) {
		std::cout << r << "\n";
	}

	std::cout << "Rectangle with maximal area: " << maxAreaRect
		<< "\nRectangle with maximal perimeter: " << maxPerimeterRect << "\n";

	std::cin.get();
}

void chapter1::exercise16() {
	Matrix<int> intMatrix{ 2,3 };

	std::cout << "Contents of an integer matrix:\n";

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			intMatrix[i][j] = (i + 1) * (j + 1);
			std::cout << intMatrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Resizing the matirx\n";
	intMatrix.resize(3, 4);

	std::cout << "The new contents of the matrix\n";
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << intMatrix[i][j] << " ";
		}

		std::cout << "\n";
	}


	std::cin.get();
}