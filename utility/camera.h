#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera {
	private:
		point3 lower_left_corner; // lower left corner of the view plane.
    	vec3 horizontal; // Horizontal dimension of the view plane.
    	vec3 vertical; // Vertical dimension of the view plane.
    	point3 origin; // the camera's origin.
    public:
    	Camera(point3 l_=point3(), vec3 h_=vec3(), vec3 v_=vec3(), point3 o_=point3()) 
			: lower_left_corner(l_), horizontal(h_), vertical(v_), origin(o_) {}
			
    	point3 get_lower_left_corner() { return lower_left_corner; }
    	vec3 get_horizontal() { return horizontal; }
    	vec3 get_vertical() { return vertical; }
    	point3 get_origin() { return origin; }
};

#endif