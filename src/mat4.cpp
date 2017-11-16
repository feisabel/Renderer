#include "../include/mat4.h"
#include "../include/vec3.h"

mat4::mat4() {
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					if(i == j) {
						m[i][j] = 1;
					}
					else {
						m[i][j] = 0;
					}
				}
			}
		}

void mat4::translate(vec3& v) {
	m[3][0] = v[0];
	m[3][1] = v[1];
	m[3][2] = v[2];
}

void mat4::scale(vec3& v) {
	m[0][0] = v[0];
	m[1][1] = v[1];
	m[2][2] = v[2];
}

void mat4::rotate(double t, char c) {
	t = t * M_PI/180;
	if(c == 'z') {
		m[0][0] = cos(t);
		m[0][1] = sin(t);
		m[1][0] = - sin(t);
		m[1][1] = cos(t);
	}
	else if(c == 'x') {
		m[1][1] = cos(t);
		m[1][2] = sin(t);
		m[2][1] = - sin(t);
		m[2][2] = cos(t);
	}
	else if(c == 'y') {
		m[0][0] = cos(t);
		m[0][2] = - sin(t);
		m[2][0] = sin(t);
		m[2][2] = cos(t);
	}
}

mat4& mat4::operator=(const mat4& m_) {
    for(int i = 0; i < 4; i++) {
    	for(int j = 0; j < 4; j++) {
    		m[i][j] = m_.m[i][j];
    	}
    }
    return *this;
}

mat4& mat4::operator*=(const mat4& m_) {
	mat4 result;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++) {
			result[i][j] = 0;
			for(int k = 0; k < 4; k++) {
				result[i][j] += m[i][k] * m_.m[k][j]; 
			}
		}
	}
	*this = result;
	return *this;
}