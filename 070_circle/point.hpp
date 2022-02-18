#ifndef __CODE_H__
#define __CODE_H__

class Point {
private:
  double x;
  double y;
public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

#endif
