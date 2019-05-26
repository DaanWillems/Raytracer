#include <iostream>
#include <fstream>
#include <string>
#include "../include/vec3.h"
#include <limits>
#include <random>
#include <stdlib.h>
#include <ctime>
#include "../include/HitableList.h"
#include "../include/Sphere.h"
#include "../include/ray.h"
#include "../include/Camera.h"
#include "../include/material.h"
#include "../include/lambertian.h"
#include "../include/metal.h"
#include "../include/dielectric.h"

float remap(float a, float b, float t) {
	return (t - a) / (b - a);
}

vec3 color(const ray& r, Hitable *world, int depth) {
	hitRecord rec;

	if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
		ray scattered;
		vec3 attenuation;

		if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}

		return vec3(0, 0, 0);
	}
	vec3 unitDirection = unit_vector(r.direction);
	float t = 0.5*(unitDirection.y() + 1.0);
	return ((1.0 - t)*vec3(1.0, 1.0, 1.0)) + (t*vec3(0.5, 0.7, 1.0));
}

int main() {
	srand(time(NULL));
	std::ofstream out("test.ppm");
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to file

	int nx = 3200;
	int ny = 1600;
	int ns = 200;

	Hitable *list[5];
	list[0] = new Sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new Sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new Sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
	list[3] = new Sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new Sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));

	float R = cos(M_PI / 4);

	Hitable *world = new HitableList(list, 5);
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Camera cam{{-2,2,1}, {0,0,-1}, {0,1,0}, 90, float(nx) / float(ny) };

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col{ 0,0,0 };
			for (int s = 0; s < ns; s++) {
				float r1 = rand() / (RAND_MAX + 1.0);
				float r2 = rand() / (RAND_MAX + 1.0);

				float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);

				ray r = cam.getRay(u, v);
				vec3 p = r.pointAtParameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));
			int ir = int(255.99*col.r());
			int ig = int(255.99*col.g());
			int ib = int(255.99*col.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
} 