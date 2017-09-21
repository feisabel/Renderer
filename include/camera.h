#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera {
	private:
		point3 lower_left_corner; // lower left corner of the view plane.
    	vec3 horizontal; // Horizontal dimension of the view plane.
    	vec3 vertical; // Vertical dimension of the view plane.
    	point3 origin; // the camera's origin.
    public:
    	Camera() {}
			
    	point3 get_lower_left_corner() { return lower_left_corner; }
    	vec3 get_horizontal() { return horizontal; }
    	vec3 get_vertical() { return vertical; }
    	point3 get_origin() { return origin; }

        void set_position(point3 p_) { origin = p_; }
        void set_lower_left_corner(point3 p_) { lower_left_corner = p_; }
        void set_horizontal(vec3 h_) { horizontal = h_; }
        void set_vertical(vec3 v_) { vertical = v_; }
};

#endif