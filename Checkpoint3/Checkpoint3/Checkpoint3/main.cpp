#include <iostream>
#include "color.h"
#include "hittable_list.h"
#include "mathconst.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "aarect.h"
#include "bvh.h"

color ray_color(const ray& r, const color& background, const hittable& world, int depth) {
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	// If the ray hits nothing, return the background color.
	if (!world.hit(r, 0.001, infinity, rec))
		return background;

	ray scattered;
	color attenuation;
	color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

	if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		return emitted;

	return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}
int main() {
	const auto aspect_ratio = 16.0/9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;
	hittable_list world;
	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material1 = make_shared<phong>(color(0.2, 0.3, 0.8));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_right = make_shared<lambertian>(color(0.8, 0.6, 0.2));
	auto difflight = make_shared<diffuse_light>(color(1500, 1500, 1500));
	world.add(make_shared<xz_rect>(-1, 0.5, 0.3, 2, -0.25, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.05, 0.7), 0.25, material1));
	world.add(make_shared<sphere>(point3(-0.3, -0.05, 0.97), 0.2, material_right));
	//world.add(make_shared<sphere>(point3(0.0, 5, -2), 0.02, difflight));
	point3 lookfrom(-0.15, 0, 0);
	point3 lookat(-0.15, 0, 1);
	Vec3 vup(0, 2.15, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.00;
	color background(.7, .7, .7);
	camera cam(lookfrom, lookat, vup, 100, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines Remaining:" << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, background, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}