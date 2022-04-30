#include <cmath>
#include "../include/euclidean_constructions_3.h"
#include "../include/number_utils.h"

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

Point_3
find_point (const Vector_3& v, const Point_3& q, double t){
    Vector_3 n = Vector_3(v.x()*t,
                          v.y()*t,
                          v.z()*t);
    Point_3 p = Point_3(q.x() + n.x(),
                        q.y() + n.y(),
                        q.z() + n.z());
    return p;
}

double
cos0 (const Vector_3& u, const Vector_3& v){
    double Mu, Mv, c = dot_product(u, v);
    Mu = sqrt(u.squared_length());
    Mv = sqrt(v.squared_length());
    return c/(Mu*Mv);
}

Point_3
rotacaox (const Point_3& p, double ang){
    double m[3][3];
    double coseno = std::cos(ang*PI/180);
    double seno = std::sin(ang*PI/180);
    if (coseno < 1.0e-3)
        coseno = 0.0;
    for (int l = 0; l < 3; l++){
        for (int c = 0; c < 3; c++){
            if ((l == 0 && c == 0) || (l == 2  && c == 2))
                m[l][c] = coseno;
            else if (l == c && l == 1)
                m[l][c] = 1.0;
            else if (l == 0 && c == 2)
                m[l][c] = seno;
            else if (l == 2 && c == 0)
                m[l][c] = -seno;
            else
                m[l][c] = 0.0;
        }
    }
    return Point_3(p.x()*m[0][0] + p.y()*m[0][1] + p.z()*m[0][2],
                   p.x()*m[1][0] + p.y()*m[1][1] + p.z()*m[1][2],
                   p.x()*m[2][0] + p.y()*m[2][1] + p.z()*m[2][2]);
}

Point_3
rotacaoy (const Point_3& p, double ang){
    double m[3][3];
    double coseno = std::cos(ang*PI/180);
    double seno = std::sin(ang*PI/180);
    if (coseno < 1.0e-3)
        coseno = 0.0;
    for (int l = 0; l < 3; l++){
        for (int c = 0; c < 3; c++){
            if ((l == 1 && c == 1) || (l == 2  && c == 2))
                m[l][c] = coseno;
            else if (l == c && l == 0)
                m[l][c] = 1.0;
            else if (l == 2 && c == 1)
                m[l][c] = seno;
            else if (l == 1 && c == 2)
                m[l][c] = -seno;
            else
                m[l][c] = 0.0;
        }
    }
    return Point_3(p.x()*m[0][0] + p.y()*m[0][1] + p.z()*m[0][2],
                   p.x()*m[1][0] + p.y()*m[1][1] + p.z()*m[1][2],
                   p.x()*m[2][0] + p.y()*m[2][1] + p.z()*m[2][2]);
}

Point_3
rotacaoz (const Point_3& p, double ang){
    double m[3][3];
    double coseno = std::cos(ang*PI/180);
    double seno = std::sin(ang*PI/180);
    if (0 < coseno && coseno < 1.0e-6)
        coseno = 0.0;
    for (int l = 0; l < 3; l++){
        for (int c = 0; c < 3; c++){
            if ((l == 0 && c == 0) || (l == 1  && c == 1))
                m[l][c] = coseno;
            else if (l == c && l == 2)
                m[l][c] = 1.0;
            else if (l == 1 && c == 0)
                m[l][c] = seno;
            else if (l == 0 && c == 1)
                m[l][c] = -seno;
            else
                m[l][c] = 0.0;
        }
    }
    return Point_3(p.x()*m[0][0] + p.y()*m[0][1] + p.z()*m[0][2],
                   p.x()*m[1][0] + p.y()*m[1][1] + p.z()*m[1][2],
                   p.x()*m[2][0] + p.y()*m[2][1] + p.z()*m[2][2]);
}

Point_3
moverx (const Point_3& p, double dist){
    return Point_3(p.x(), p.y() + dist, p.z());
}

Point_3
movery (const Point_3& p, double dist){
    return Point_3(p.x() + dist, p.y(), p.z());
}

Point_3
moverz (const Point_3& p, double dist){
    return Point_3(p.x(), p.y(), p.z() + dist);
}

Point_3
transladar (const Point_3& p, double x, double y){
    return Point_3(movery(moverx(p, x), y));
}
