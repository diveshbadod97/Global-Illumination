#pragma once
#ifndef HITTABLE_H
#define HHITTABLE_H
#include "ray.h"
#include "aabb.h"
#include "mathconst.h"
class material;
struct hit_record{
	point3 p;
	Vec3 normal;
	bool front_face;
	shared_ptr<material> mat_ptr;
	double t;
	double u;
	double v;

	inline void set_face_normal(const ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};
class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;

};
#endif // !HITTABLE_H

