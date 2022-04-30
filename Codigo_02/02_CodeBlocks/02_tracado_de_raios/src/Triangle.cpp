#include "../include/Triangle_3.h"
#include "../include/euclidean_constructions_3.h"

Triangle_3::Triangle_3(const Point_3& p, const Point_3& q, const Point_3& r)
  : _v1(p), _v2(q), _v3(r)
{ }

const Point_3&
Triangle_3::v1() const
{
  return _v1;
}

const Point_3&
Triangle_3::v2() const
{
  return _v2;
}

const Point_3&
Triangle_3::v3() const
{
  return _v3;
}

Triangle_3::Hit_pair
Triangle_3::hit(const Ray_3& r, double tmin, double tmax) const
{
    Vector_3 a1 = this->v2() - this->v1();
    Vector_3 a2 = this->v3() - this->v2();
    Vector_3 a3 = this->v1() - this->v3();
    Vector_3 N = cross_product(a1, a2);
    N = N.unit_vector();
    double D = -(N.x() * this->v1().x() +
                N.y() * this->v1().y() +
                N.z() * this->v1().z());
    double num = N.x() * r.origin().x() +
                N.y() * r.origin().y() +
                N.z() * r.origin().z() + D;
    double den = N.x() * r.direction().x() +
                N.y() * r.direction().y() +
                N.z() * r.direction().z();
    double t = -num/den;
    if (dot_product(N, r.direction()) != 0 && t > 0){
        Point_3 p = find_point(r.direction(), r.origin(), t);
        Vector_3 c1 = p - this->v1();
        Vector_3 c2 = p - this->v2();
        Vector_3 c3 = p - this->v3();
        if (dot_product(N, cross_product(a1, c1)) > 0 &&
            dot_product(N, cross_product(a2, c2)) > 0 &&
            dot_product(N, cross_product(a3, c3)) > 0){
                return Hit_pair (this, t);
            }
    }
    return Hit_pair (NULL, t);
}

Vector_3
Triangle_3::normal(const Point_3& p) const
{
    Vector_3 v1v2 = this->v2() - this->v1();
    Vector_3 v1vp = this->v3() - this->v1();
    return -cross_product(v1v2, v1vp);
}

Vector_3
Triangle_3::unit_normal(const Point_3& p) const
{
    Vector_3 v1v2 = this->v2() - this->v1();
    Vector_3 v1vp = this->v3() - this->v1();
    return -cross_product(v1v2, v1vp).unit_vector();
}

