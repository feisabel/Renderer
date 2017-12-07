#include "../include/dielectric.h"

bool Dielectric::scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
	vec3 reflected = unit_vector(ray.get_direction()) - 2 * dot(unit_vector(ray.get_direction()), rec.normal) * rec.normal;
	attenuation = vec3(1.0,1.0,1.0);
	double n1, n2;
	vec3 normal;
	double reflect_prob;
	double cosine = dot(unit_vector(ray.get_direction()), rec.normal);
	if(dot(unit_vector(ray.get_direction()), rec.normal) > 0) {
		n1 = refractive_index;
		n2 = 1;
		normal = -rec.normal;
        cosine = sqrt(1 - refractive_index * refractive_index * (1 - cosine * cosine));
	}
	else {
		n1 = 1.0;
		n2 = refractive_index;
		normal = rec.normal;
		cosine = -cosine;
	}
	vec3 refracted;
	if(refract(normal, unit_vector(ray.get_direction()), n1/n2, refracted)) {
		reflect_prob = schlick(normal, unit_vector(ray.get_direction()), n1, n2);
	}
	else {
		reflect_prob = 1;
	}
	std::random_device rd;
    std::mt19937 gen(rd());
    double random_prob = std::generate_canonical<double,10>(gen);
	if(random_prob < reflect_prob) {
		scattered = Ray(rec.p, reflected);
	}
	else {
		scattered = Ray(rec.p, refracted);
	}
	return true;
}

bool Dielectric::refract(vec3 normal, vec3 dir, double n, vec3& refracted) const {
	double dt = dot(dir, normal);
	double discriminant = 1.0 - n * n * (1.0 - dt * dt);
	if(discriminant > 0){
		refracted = n * (dir - normal * dt) - normal * sqrt(discriminant);
		return true;
	}
	return false;
}

double Dielectric::schlick(vec3 normal, vec3 dir, double n1, double n2) const {
	double r0 = (n1 - n2)/(n1 + n2);
	r0 *= r0;
	double cosX = -dot(normal, dir);
	if(n1 > n2) {
		double n = n1/n2;
		double sinT2 = n * n * (1 - cosX * cosX);
		if(sinT2 > 1) {
			return 1;
		}
		cosX = sqrt(1 - sinT2);
	}
	double x = 1 - cosX;
	return r0 + (1 - r0) * x * x * x * x * x;
}

double Dielectric::schlick(double cosine, double n1, double n2) const {
	double r0 = (n1 - n2)/(n1 + n2);
	r0 *= r0;
	return r0 + (1 - r0) * pow((1-cosine),5);
}