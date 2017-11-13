#ifndef _CAMERA_H_
#define _CAMERA_H_

#include  "ray.h"

class Camera {
	private:
        point3 viewpoint; //camera viewpoint
        vec3 u; //camera X axis basis
        vec3 v; //camera Y axis basis
        vec3 w; //camera Z axis basis
        std::string projection; //projection type
		point3 lower_left_corner; // lower left corner of the view plane.
    	vec3 horizontal; // Horizontal dimension of the view plane.
    	vec3 vertical; // Vertical dimension of the view plane.
        vec3 viewplane_normal;
        double lens_radius;
    public:
    	Camera() {}

        void set_camera(point3 look_from, point3 look_at, vec3 up_vec, std::string proj);

        void set_perspective(double fov, double ratio, double d, double aperture);
        void set_perspective(double fov, double ratio, double d, double aperture, vec3 vpn);

        void set_parallel(double l, double r, double t, double b);
        void set_parallel(double l, double r, double t, double b, vec3 vpn);

        Ray get_ray(double s, double t);
};

#endif