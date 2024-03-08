William Qin
3/2/23
Computer Graphics
Professor Kayar

This is my report for Assignment 1, convex hull. I implemented the helper functions det and salientAngle first, then I wrote out the code for load_xyz, compare, and convex_hull.

### Operating System
Must include the name and version of both your operating system and of the compiler that you used. I am using macOS, running Ventura 13.0.1. My IDE is Visual Studio Code, and I am compiling with cmake/make.

I run in this sequence:
* cd build
* cmake ..; make ./convex_hull ../data/points.xyz output.obj

I rendered the obj using a vsc plugin called 3D viewer.

### Det
Helper function that computes determinant based on the formula |A| = x1*y2 - y1*x2, where (x1, y1) is u.real() and u.imag(), and (x2, y2) is v.real() and v.imag(). I used this website to find the formula:  https://www.cuemath.com/algebra/determinant-of-matrix/.

### salientAngle
A salient angle is when an external angle is greater than 180 degrees. I use the determinant to see whether the vector from a to b makes a left turn (counterclockwise) to the vector from b to c. If determinant is positive, it makes a left turn. Otherwise it makes a right turn/is parallel.
The salient angle is used to determine if a point turns back on previously added points, so we can take it out if true.

### load_xyz
The function reads from ./data/points.xyz, 3 integers at a time. I make sure to skip the first integer, 3000, so that it doesn't mess up the points. Then I iterate through the file, keeping only the first 2 points. I convert the x, y into a Point object and push it into a vector (points).

### compare
The bool operator sorts points in counter-clockwise order. First I create two points u and v, which are vectors from the leftmost point of the polygon. I find the determinant of the two vectors. If the determinant is positive, then the angle from u to v is counterclockwise, otherwise it is clockwise.
If counterclockwise, p1 should come before p2 in sorted list, so it returns true. If determinant is 0, then the two vectors are parallel. We compare based on the magnitude of p1 and p2. Shorter magnitude goes first. 

### convex_hull
I implemented the convex hull function according to the instructions. First, I find leftmost point p0 by finding the point with the smallest x and y value. Next, I sort input points counter-clockwise with respect to p0. Next, after the points vector is populated with at least 2 Points, I iterate through points, whenever salient angle is found, I pop those points from hull.

### results
The points will create a 7 sided polygon like this:
![Alt text](./Screenshot%202023-03-02%20at%208.14.22%20PM.png "result")