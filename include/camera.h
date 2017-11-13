#ifndef _CAMERA_H_
#define _CAMERA_H_

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
    public:
    	Camera() {}
			
    	point3 get_lower_left_corner() { return lower_left_corner; }
    	vec3 get_horizontal() { return horizontal; }
    	vec3 get_vertical() { return vertical; }
    	point3 get_viewpoint() { return viewpoint; }

        void set_camera(point3 look_from, point3 look_at, vec3 up_vec, std::string proj) { 
            viewpoint = look_from;
            w = unit_vector(look_from - look_at);
            u = unit_vector(cross(up_vec, w));
            v = cross(w, u);
            projection = proj;
        }

        void set_perspective(double fov, double ratio, double d) {
            double height = tan(fov/2) * 2 * d;
            double width = height * ratio;
            horizontal = width * u;
            vertical = height * v;
            lower_left_corner = viewpoint - (d * w) - (horizontal/2) - (vertical/2);
        }

        Ray get_ray(double s, double t) {
            if(projection.compare("perspective") == 0) {
                point3 p = lower_left_corner + s * horizontal + t * vertical;
                return Ray(viewpoint, p - viewpoint);
            }
            else {
                return Ray();
            }
        }
};

#endif