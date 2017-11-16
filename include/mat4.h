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
		mat4();
		
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
        mat4& operator=(const mat4& m_);
        mat4& operator*=(const mat4& m_);

		void translate(vec3& v);
		void scale(vec3& v);
		void rotate(double t, char c);
};

#endif