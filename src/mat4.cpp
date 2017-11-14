#include "../include/mat4.h"
#include "../include/vec3.h"

void mat4::translate(vec3& v) {
	m[3][0] = v[0];
	m[3][1] = v[1];
	m[3][2] = v[2];
}