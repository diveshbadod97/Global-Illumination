#pragma once
#ifndef HITTABLE_H
#define HHITTABLE_H
#include "ray.h"
struct hit_record{
	point3 p;
	Vec3 normal;
	bool front_face;
	double t;

	inline void set_face_normal(const ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};
class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

};
#endif // !HITTABLE_H

