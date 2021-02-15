#include <iostream>
#include "color.h"
#include "hittable_list.h"
#include "mathconst.h"
#include "sphere.h"
#include "camera.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
	Vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0 * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

color ray_color(const ray& r, const hittable& world) {
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);

	if (t > 0.0) {
		return color(0, 0, 0);
	}
	t = hit_sphere(point3(0.6, 0.1, -1), 0.3, r);
	if (t > 0.0) {
		return color(0, 0, 0);
	}
	t = hit_sphere(point3(0, -300.5, 0), 300, r);
	if (t > 0.0) {
		return color(1, 0, 0);
	}
	/**hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}**/
	Vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	//return color(t, t, t);
}
int main() {
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
	world.add(make_shared<sphere>(point3(0.5, 0, -1), 0.2));
	camera cam;
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines Remaining:" << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = double(i) / (image_width - 1.00);
				auto v = double(j) / (image_height - 1.00);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}