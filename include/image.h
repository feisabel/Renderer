#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>

class Image {
	private:
		int width; // lower left corner of the view plane.
    	int height; // Horizontal dimension of the view plane.
    	std::string name;
    	std::string codification;
        int samples;

    public:
    	Image() {}
			
    	int get_width() { return width; }
    	int get_height() { return height; }
    	std::string get_name() { return name; }
    	std::string get_codification() { return codification; }
        int get_samples() { return samples; }

    	void set_codification(std::string c_) { codification = c_; }
    	void set_name(std::string n_) { name = n_; }
    	void set_dimensions(int w_, int h_) { width = w_; height = h_; }
        void set_width(int w_) { width = w_; }
        void set_height(int h_) { height = h_; }
        void set_samples(int s_) { samples = s_; }
};

#endif