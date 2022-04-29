#ifndef TRIANGLES_3_H
#define TRIANGLES_3_H

#include <cmath>

#include "../include/Point_3.h"
#include "../include/Ray_3.h"
#include "../include/Vector_3.h"
#include "../include/Object.h"
#include "../include/euclidean_constructions_3.h"
#include "../include/number_utils.h"
#include "../include/Color.h"

class Triangles_3 : public Object
{
public:
  // Constructors
  Triangles_3();
  Triangles_3(const Point_3& p, const Point_3& q, const Point_3& r);

  const Point_3& v1() const;
  const Point_3& v2() const;
  const Point_3& v3() const;

  Hit_pair hit(const Ray_3& r, double tmin = 0.0, double tmax = INF) const;
  Vector_3 normal(const Point_3& p) const;
  Vector_3 unit_normal(const Point_3& p) const;

private:
  Point_3 _v1;
  Point_3 _v2;
  Point_3 _v3;
};

#endif // TRIANGLES_3_H

