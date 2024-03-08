////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
////////////////////////////////////////////////////////////////////////////////

typedef std::complex<double> Point;
typedef std::vector<Point> Polygon;

// helper function that computes determinant based on the formula |A| = x1*y2 - y1*x2
// Where (x1, y1) is u.real() and u.imag(), and (x2, y2) is v.real() and v.imag().
// https://www.cuemath.com/algebra/determinant-of-matrix/
double inline det(const Point &u, const Point &v) {
	// TODO
	return u.real() * v.imag() - u.imag() * v.real();
};

struct Compare {
	Point p0; // Leftmost point of the poly
	bool operator ()(const Point &p1, const Point &p2) {
		// TODO: sort points in counter-clockwise order
		Point u = p1 - p0;
		Point v = p2 - p0;
		// if the determinant is positive, then the angle from u to v is counterclockwise, otherwise it is clockwise.
		// if counterclockwise, p1 should come before p2 in sorted list, so it returns true.
		// if clockwise, p2 should come before p1, so it returns false.
		double det_uv = det(u, v);
		if (det_uv != 0.0) {
			return det_uv > 0.0;
		} else {
			// if determinant is 0, then the two vectors are parallel. We compare based on the magnitude of p1 and p2. 
			// shorter magnitude goes first. 
			double dist1 = std::norm(u);
			double dist2 = std::norm(v);
			return dist1 < dist2;
		}
	}
};

// A salient angle is when an angle is greater than 180 degrees. 
// We use the determinant to see whether the vector from a to b makes a left turn (counterclockwise) to the vector from b to c.
// If determinant is positive, it makes a left turn. Otherwise it makes a right turn/is parallel.
// We use the salient angle to determine if a point turns back on previously added points, so we can take it out if true.
bool inline salientAngle(const Point &a, const Point &b, const Point &c) {
	// TODO
	return det(b-a, c-b) > 0;
}

////////////////////////////////////////////////////////////////////////////////

Polygon convex_hull(std::vector<Point> &points) {
    Compare order;
    // Find the leftmost point
    Point leftmost = points[0];
    for (const auto &p : points) {
        if (p.real() < leftmost.real() || (p.real() == leftmost.real() && p.imag() < leftmost.imag())) {
            leftmost = p;
        }
    }
    order.p0 = leftmost;
	// Step 2: sort input points counter-clockwise with respect to P0. 
    std::sort(points.begin(), points.end(), order);
    // Build the hull
    Polygon hull;
	// TODO: Step 3 - iterate through points, whenever salient angle is found pop middle-point from hull.
    for (const auto &p : points) {
		// when we have enough points to compare: check if it is a salient angle, if so remove it. 
        while (hull.size() >= 2 && !salientAngle(hull[hull.size()-2], hull[hull.size()-1], p)) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    return hull;
}

////////////////////////////////////////////////////////////////////////////////

std::vector<Point> load_xyz(const std::string &filename) {
	std::vector<Point> points;
	std::ifstream in(filename);
	// TODO
	if (!in.is_open()) {
		throw std::runtime_error("failed to open file " + filename);
	}
	// skip first line becasue it is size of points (3000)
	int skip;
	in >> skip;
	// read three numbers per line. We only need x and y. 
	double x, y, z;
	// std::cout << "loading points" << std::endl;
	while (in >> x >> y >> z) {
		Point v(x,y);
		// std::cout << v << std::endl;
		points.push_back(v);
	}
	// std::cout << points.front() << std::endl;
	in.close();
	return points;
}

void save_obj(const std::string &filename, Polygon &poly) {
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw std::runtime_error("failed to open file " + filename);
	}
	out << std::fixed;
	for (const auto &v : poly) {
		out << "v " << v.real() << ' ' << v.imag() << " 0\n";
	}
	for (size_t i = 0; i < poly.size(); ++i) {
		out << "l " << i+1 << ' ' << 1+(i+1)%poly.size() << "\n";
	}
	out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
	if (argc <= 2) {
		std::cerr << "Usage: " << argv[0] << " points.xyz output.obj" << std::endl;
	}
	std::vector<Point> points = load_xyz(argv[1]);
	Polygon hull = convex_hull(points);
	save_obj(argv[2], hull);
	return 0;
}