#ifndef _MAT4_H_
#define _MAT4_H_

#include <cmath>
#include <iostream>
#include <cassert>
#include <random>

class vec3;

class mat4 {
	private:
		double m[4][4];
	public: 
		mat4() {
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

		class vec4 {
    		public:
        		vec4(mat4& p_, int r_) : parent(p_), row(r_) { }

        		double operator[](int col) const { return parent.m[row][col]; }
        		double& operator[](int col) { return parent.m[row][col]; }
    		private:
        		mat4& parent;
        		int row;
    	};

        vec4 operator[](int row) { return vec4(*this, row); }

        mat4& operator=(const mat4& m_) {
            for(int i = 0; i < 4; i++) {
            	for(int j = 0; j < 4; j++) {
            		m[i][j] = m_.m[i][j];
            	}
            }
            return *this;
        }

        mat4& operator*=(const mat4& m_) {
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

		void translate(vec3& v);
};

#endif