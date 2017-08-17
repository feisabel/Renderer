#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

class Ray {

	private:
		point3 origin;
		vec3 direction;

	public:
		typedef float real_type;

		Ray( point3 o_=point3(), vec3 d_=vec3() ) 
			: origin( o_ ), direction( d_ ) {}

		inline vec3 get_direction( void ) const { return direction; }
		inline point3 get_origin( void ) const { return origin; }
		point3 point_at( real_type t_ ) const { return origin + t_ * direction; }

};

#endif