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

float remap(float a, float b, float t) {
	return (t - a) / (b - a);
}

float hitSphere(const vec3& center, float radius, const ray& r) {
//	vec3 oc = r.origin - center;
//	float a = dot(r.direction, r.direction);
//	float b = 2.0 * dot(oc, r.direction);
//	float c = dot(oc, oc) - radius * radius;
//	float discriminant = b * b - 4 * a*c;
//	if (discriminant < 0) {
//		return -1.0;
//	}
//	else {
//		return (-b - sqrt(discriminant)) / (2.0*a);
//	}
	vec3 rd = unit_vector(r.direction);
	vec3 ro = r.origin;

	float t = dot((center - ro), rd);
	vec3 p = ro + rd * t;
	vec3 l = center - p;
	float y = l.length();
	if (y < radius) {
		float x = sqrt((radius*radius) - (y * y));
		return t - x;
	}
	return 0;
}

vec3 randomInUnitSphere() {
	vec3 p;
	do {
		float r1 = rand() / (RAND_MAX + 1.0);
		float r2 = rand() / (RAND_MAX + 1.0);
		float r3 = rand() / (RAND_MAX + 1.0);
		p = 2.0*vec3(r1, r2, r3) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;

}

vec3 color(const ray& r, Hitable *world) {
	hitRecord rec;

	if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
		vec3 target = rec.p + rec.normal + randomInUnitSphere();
		return 0.5*color(ray(rec.p, target - rec.p), world);
	}
	else {
		vec3 unitDirection = unit_vector(r.direction);
		float t = 0.5*(unitDirection.y() + 1.0);
		return ((1.0 - t)*vec3(1.0, 1.0, 1.0)) + (t*vec3(0.5, 0.7, 1.0));
	}
}

int main() {
	srand(time(NULL));
	std::ofstream out("test.ppm");
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to file

	int nx = 400;
	int ny = 200;
	int ns = 20;

	vec3 lowerLeftCorner{ -2.0, -1.0, -1.0 };
	vec3 horizontal{ 4.0, 0.0, 0.0 };
	vec3 vertical{ 0.0, 2.0, 0.0 };
	vec3 origin{ 0.0, 0.0, 0.0 };

	Hitable *list[2];
	list[0] = new Sphere(vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(vec3(0, -100.5, -1), 100);
	Hitable *world = new HitableList(list, 2);
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Camera cam;
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
				col += color(r, world);
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