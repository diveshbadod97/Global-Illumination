#pragma once
#ifndef RAY_H
#define RAY_H
#include "Vec3.h"

class ray {
public:
	ray() {}
	ray(const point3& origin, const Vec3& direction)
		: orig(origin), dir(direction)
	{}
	point3 origin() const { return orig; }
	Vec3 direction() const { return dir; }
	point3 at(double t)const {
		//return orig + t * dir;
		return dir;
	}
public:
	point3 orig;
	Vec3 dir;
};
#endif // !RAY_H
