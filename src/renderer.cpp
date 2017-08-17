#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../utility/vec3.h"
#include "../utility/ray.h"
#include "../utility/sphere.h"

//parses input line for information (except colors)
std::string getInfo( std::string line ) {
	int start, end;
   	start = line.find_first_of( "=" ) + 2;
    if( line.find_first_of( " ", start ) == std::string::npos )
    	end = line.size();
   	else
   		end = line.find_first_of( " ", start );
   	return line.substr( start, end-start );
}

//parses input line for color information
vec3 getVector( std::string line ) {
    float X, Y, Z;
	int start, end;
   	start = line.find_first_of( "=" ) + 2;
    end = line.find_first_of( " ", start );
    X = std::stoi( line.substr( start, end-start ), nullptr );
    start = end+1;
    end = line.find_first_of( " ", start );
    Y = std::stoi( line.substr( start, end-start ), nullptr );
    start = end+1;
    if( line.find_first_of( " ", start ) == std::string::npos )
    	end = line.size();
   	else
   		end = line.find_first_of( " ", start );
   	Z = std::stoi( line.substr( start, end-start ), nullptr );
   	return vec3(X, Y, Z);
}

bool hit_sphere( Ray ray, Sphere sphere, float &t_) {
    vec3 direction = ray.get_direction();
    point3 center = sphere.get_center();
    float radius = sphere.get_radius();
    vec3 center_direction = ray.get_origin() - center;

    float a = dot(direction, direction);
    float b = 2 * dot(center_direction, direction);
    float c = dot(center_direction, center_direction) - radius * radius;
    float delta = b * b - 4 * a * c;
    if(delta >= 0) {
        t_ = (-b - sqrt(delta)) / (2 * a);
        if(t_ < 0) {
            t_ = (-b + sqrt(delta)) / (2 * a);
            if (t_ < 0)
                return false;
            else
                return true;
        }
        return true;
    }
    else
        return false;

}

rgb color( Ray ray ) {
    Sphere sphere( point3( 0, 0, -2 ), 1);
    float t_;

    if( hit_sphere( ray, sphere, t_ ) ) {
        point3 P = ray.point_at( t_ );
        vec3 N = P - sphere.get_center();
        vec3 unit_N = unit_vector( N );
       
        return (unit_N + vec3(1,1,1))/2 ;
    }
    else {
        rgb upper_left( 0.5, 0.7, 1 );
        rgb upper_right( 0.5, 0.7, 1 );
        rgb lower_left( 1,1,1 );
        rgb lower_right( 1,1,1 );

        vec3 unit_ray = unit_vector( ray.get_direction() );
        float x_ratio = unit_ray.x();
        x_ratio += 1;
        x_ratio /= 2;
        float y_ratio = unit_ray.y();
        y_ratio += 1;
        y_ratio /= 2;

        rgb left = y_ratio * ( upper_left - lower_left ) + lower_left;
        rgb right = y_ratio * ( upper_right - lower_right ) + lower_right;
        return x_ratio * ( right - left ) + right;
    }
}

int main( int argc, char *argv[] ) {
	std::string name, type, codification;
	int width, height;
	rgb upper_left, lower_left, upper_right, lower_right;

	//read scene file
	std::string line;
	std::ifstream scene_file ( argv[1] );
	if ( scene_file.is_open() ) {
		getline( scene_file, line );
		name = "images/" + getInfo( line );
    	getline( scene_file, line );
		type = getInfo( line );
		getline( scene_file, line );
		codification = getInfo( line );
		getline( scene_file, line );
		width = std::stoi( getInfo( line ), nullptr );
		getline( scene_file, line );
		height = std::stoi( getInfo( line ), nullptr );
		getline( scene_file, line );
		upper_left = getVector( line );
		getline( scene_file, line );
		lower_left = getVector( line );
		getline( scene_file, line );
		upper_right = getVector( line );
		getline( scene_file, line );
		lower_right = getVector( line );

    	scene_file.close();
    }
    else {
        name = "images/background2.ppm";
        width = 2000;
        height = 1000;
        codification = "binary";
    }

    char *buffer = new char[width*height*3];
    int k = 0;

    point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
    vec3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
    vec3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    point3 origin(0, 0, 0); // the camera's origin.

    //calculating each pixel's rgb with bilinear interpolation
    for( int row = height-1; row >= 0; row-- ) {
    	for( int col = 0; col < width; col++ ) {
            auto u = float(col)/( width-1 );
            auto v = float(row)/( height-1 );
            point3 end_point = lower_left_corner + u*horizontal + v*vertical;
            Ray r( origin, end_point - origin );
            rgb c = color( r );
            if(row == height/2 && col == width/2)
                std::cout << r.get_origin() << " " << r.get_direction() << std::endl;

            for( int i = 0; i < 3; i++ ) {
                buffer[k] = char( int( 255.99 * c[i] ) );
                k++;
            }
    	}
    }

    //writing image file
    std::ofstream image_file ( name );
  	if ( image_file.is_open() ) {
    	if( codification.compare( "binary" ) == 0 ) {
    		image_file << "P6\n";
    		image_file << width << " " << height << "\n";
    		image_file << "255\n";
    		image_file.write( buffer, width*height*3 );
    	}
    	else {
			image_file << "P3\n";
    		image_file << width << " " << height << "\n";
    		image_file << "255\n";
    		for( int i = 0; i < width*height*3; i+=3 ) {
    			image_file << int( ( unsigned char )buffer[i] ) << " " 
                                << int( ( unsigned char )buffer[i+1] ) << " " 
                                << int( ( unsigned char )buffer[i+2] ) << "\n";
    		}
    	}

    	image_file.close();
  	}

    delete[] buffer;

	return 0;
}