#include "point.hpp"

class Circle {
private:
  Point c;
  const double r;
public:
  Circle(Point c, const double r);
  void move (double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
