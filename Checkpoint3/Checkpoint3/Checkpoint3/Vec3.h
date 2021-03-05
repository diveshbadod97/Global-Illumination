#ifndef Vec3_H
#define Vec3_H
#include <cmath>
#include <iostream>
using std::sqrt;
using std::fabs;

class Vec3 {
public:
    Vec3() : e{ 0,0,0 } {}
    Vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vec3& operator+=(const Vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const {
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }
    inline static Vec3 random() {
        double a = rand() / (RAND_MAX + 1.0);
        double b = rand() / (RAND_MAX + 1.0);
        double c = rand() / (RAND_MAX + 1.0);
        return Vec3(a, b, c);
    }
    inline static Vec3 random(double min, double max) {
        double a = min + (max - min) * (rand() / (RAND_MAX + 1.0));
        double b = min + (max - min) * (rand() / (RAND_MAX + 1.0));
        double c = min + (max - min) * (rand() / (RAND_MAX + 1.0));
        return Vec3(a, b, c);
    }
    public:
        double e[3];
};

using point3 = Vec3;
using color = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}
inline Vec3 operator/(Vec3 v, double t) {
	return (1 / t) * v;
}
inline double dot(const Vec3& u, const Vec3& v) {
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
inline Vec3 cross(const Vec3& u, const Vec3  v) {
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline Vec3 unit_vector(Vec3 v) {
	return v / v.length_squared();
}

inline Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}
Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
Vec3 random_in_unit_disk() {
    while (true) {
        double a = (rand() / (RAND_MAX + 1.0));
        double b = (rand() / (RAND_MAX + 1.0));
        auto p = Vec3(a, b, 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

#endif



