#ifndef YK_37039987_RECTANGLE_H
#define YK_37039987_RECTANGLE_H
#include <iostream>

/*
* Rectangle class template - T is assumed to be either float or integer.
* Minimal checking for errors - values are not checked for negativity for the sake of simplicity
*/
template <typename T>
/*
* Rectangle class - provides a constructor and accessors and printing functions
*/
class Rectangle {
public:
	Rectangle(const T& l, const T& w) : length{ l }, width{ w } {}
	const T& getLength() const { return length; }
	const T& getWidth() const { return width; }
	T getArea() const { return length * width; }
	T getPerimeter() const { return length + length + width + width; }
	void printStats(std::ostream& os) const {
		os << "length: " << length << " width: " << width << " area: " << getArea() << " perimeter: " << getPerimeter();
	}
private:
	T length;
	T width;
};


template <typename T>
std::ostream& operator << (std::ostream& os, const Rectangle<T>& r) {
	r.printStats(os);
	return os;
}

/*
* Compare two rectangles by their areas
*/
template <typename T>
class AreaCompare {
public:
	bool operator() (const Rectangle<T>& left, const Rectangle<T>& right) const {
		bool result = left.getArea() < right.getArea();
		return result;
	}
};

/*
* Compare two rectangles by their perimeters
*/
template <typename T>
class PerimeterCompare {
public:
	bool operator() (const Rectangle<T>& left, const Rectangle<T>& right) const {
		bool result = left.getPerimeter() < right.getPerimeter();
		return result;
	}
};


#endif
