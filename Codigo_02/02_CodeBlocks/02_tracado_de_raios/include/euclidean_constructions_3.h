#ifndef EUCLIDEAN_CONSTRUCTIONS_3_H
#define EUCLIDEAN_CONSTRUCTIONS_3_H

#include "../include/Point_3.h"
#include "../include/Vector_3.h"

Vector_3
cross_product(const Vector_3& u, const Vector_3& v);

double
dot_product(const Vector_3& u, const Vector_3& v);

double
squared_distance(const Point_3& p, const Point_3& q);

Vector_3
normal(const Point_3& p, const Point_3& q, const Point_3& r);

Vector_3
unit_normal(const Point_3& p, const Point_3& q, const Point_3& r);

Point_3
find_point (const Vector_3& v, const Point_3& q, double t);

double
cos0 (const Vector_3& u, const Vector_3& v);

Point_3
rotacaox (const Point_3& p, double ang);

Point_3
rotacaoy (const Point_3& p, double ang);

Point_3
rotacaoz (const Point_3& p, double ang);

Point_3
moverx (const Point_3& p, double dist);

Point_3
movery (const Point_3& p, double dist);

Point_3
moverz (const Point_3& p, double dist);

Point_3
transladar (const Point_3& p, double x, double y);

#endif // EUCLIDEAN_CONSTRUCTIONS_3_H
