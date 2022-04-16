#include <cmath>
#include "../include/euclidean_constructions_3.h"

Vector_3
cross_product(const Vector_3& u, const Vector_3& v)
{
  return Vector_3(u.y() * v.z() - u.z() * v.y(),
      u.z() * v.x() - u.x() * v.z(),
      u.x() * v.y() - u.y() * v.x());
}

double
dot_product(const Vector_3& u, const Vector_3& v)
{
  return ((u.x() * v.x()) + (u.y() * v.y()) + (u.z() * v.z()));
}

double
squared_distance(const Point_3& p, const Point_3& q)
{
  return ( (p.x() - q.x()) * (p.x() - q.x()) +
      (p.y() - q.y()) * (p.y() - q.y()) +
      (p.z() - q.z()) * (p.z() - q.z()) );
}

Vector_3
normal(const Point_3& p, const Point_3& q, const Point_3& r)
{
  Vector_3 n = cross_product(q-p, r-p);
  return n;
}

Vector_3
unit_normal(const Point_3& p, const Point_3& q, const Point_3& r)
{
  Vector_3 n = cross_product(q-p, r-p);
  n = n/std::sqrt(n.squared_length());
  return n;
}
