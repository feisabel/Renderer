#include "../include/camera.h"

void Camera::set_camera(point3 look_from, point3 look_at, vec3 up_vec, std::string proj) { 
    viewpoint = look_from;
    viewplane_normal = look_at - look_from;
    w = unit_vector(look_from - look_at);
    u = unit_vector(cross(up_vec, w));
    v = cross(w, u);
    projection = proj;
}

void Camera::set_perspective(double fov, double ratio, double d, double aperture) {
    set_perspective(fov, ratio, d, aperture, viewplane_normal);
}

void Camera::set_perspective(double fov, double ratio, double d, double aperture, vec3 vpn) {
    fov = fov * M_PI/180;
    double height = tan(fov/2) * 2 * d;
    double width = height * ratio;
    horizontal = width * u;
    vertical = height * v;
    lower_left_corner = viewpoint - (d * w) - (horizontal/2) - (vertical/2);
    viewplane_normal = vpn;
    lens_radius = aperture/2;
}

void Camera::set_parallel(double l, double r, double t, double b) {
    set_parallel(l, r, t, b, viewplane_normal);
}

void Camera::set_parallel(double l, double r, double t, double b, vec3 vpn) {
    horizontal = vec3(r-l, 0, 0);
    vertical = vec3(0, t-b, 0);
    lower_left_corner = vec3(l, b, viewpoint[2]);
    viewplane_normal = vpn;
}

Ray Camera::get_ray(double s, double t) {
    if(projection.compare("perspective") == 0) {
        vec3 rd = lens_radius*random_unit_2d_vector();
        vec3 offset = u * rd[0] + v * rd[1];
        point3 p = lower_left_corner + s * horizontal + t * vertical;
        return Ray(viewpoint + offset, p - viewpoint - offset);
    }
    else {
        point3 p = lower_left_corner + s * horizontal + t * vertical;
        return Ray(p, viewplane_normal);
    }
}