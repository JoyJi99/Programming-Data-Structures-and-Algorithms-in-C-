#include "circle.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

const double pi = acos(-1);

Circle::Circle(Point c, const double r) : c(c), r(r){}

void Circle::move (double dx, double dy) {
  c.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = c.distanceFrom(otherCircle.c);
  if(distance <= fabs(r - otherCircle.r)){ 
    if(r < otherCircle.r){ 
      return pi * r * r;
    }
    else{
      return pi * otherCircle.r * otherCircle.r;
    }
  }
  if(distance >= (r + otherCircle.r)){  
      return 0.0;
  }
  double ang1 = acos((r * r + distance * distance - otherCircle.r * otherCircle.r)/(2 * r * distance)); 
  double ang2= acos((otherCircle.r * otherCircle.r + distance * distance -r * r)/(2 * otherCircle.r * distance));
  double area= ang1 * r * r + ang2 * otherCircle.r * otherCircle.r - distance * r * sin(ang1);
  return area;
}
