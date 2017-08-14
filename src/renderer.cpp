#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
std::vector<int> getColor( std::string line ) {
	std::vector<int> color;
	int start, end;
   	start = line.find_first_of( "=" ) + 2;
    end = line.find_first_of( " ", start );
    color.push_back( std::stoi( line.substr( start, end-start ), nullptr ) );
    start = end+1;
    end = line.find_first_of( " ", start );
    color.push_back( std::stoi( line.substr( start, end-start ), nullptr ) );
    start = end+1;
    if( line.find_first_of( " ", start ) == std::string::npos )
    	end = line.size();
   	else
   		end = line.find_first_of( " ", start );
   	color.push_back( std::stoi( line.substr( start, end-start ), nullptr ) );
   	return color;
}


int main( int argc, char *argv[] ) {
	std::string name, type, codification;
	int width, height;
	std::vector<int> upper_left, lower_left, upper_right, lower_right;

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
		upper_left = getColor( line );
		getline( scene_file, line );
		lower_left = getColor( line );
		getline( scene_file, line );
		upper_right = getColor( line );
		getline( scene_file, line );
		lower_right = getColor( line );

    	scene_file.close();
    }

    char *buffer = new char[width*height*3];
    int k = 0;

    //calculating each pixel's rgb with bilinear interpolation
    for( int row = height-1; row >= 0; row-- ) {
    	std::vector<int> a, b;
    	for( int i = 0; i < 3; i++ ) {
    		a.push_back( float(row)/( height-1 ) * ( upper_left[i] - lower_left[i] ) + lower_left[i] );
    		b.push_back( float(row)/( height-1 ) * ( upper_right[i] - lower_right[i] ) + lower_right[i] );
    	}
    	for( int col = 0; col < width; col++ ) {
    		for( int i = 0; i < 3; i++ ) {
    			int c = float(col)/( width-1 ) * ( b[i] - a[i] ) + a[i];
    			buffer[k] = char(c);
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