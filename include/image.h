#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>

class Image {
	private:
		int width; // lower left corner of the view plane.
    	int height; // Horizontal dimension of the view plane.
    	std::string name;
    	std::string codification;
        std::string mode;

    public:
    	Image(int w_=0, int h_=0) 
			: width(w_), height(h_) {}
			
    	int get_width() { return width; }
    	int get_height() { return height; }
    	std::string get_name() { return name; }
        std::string get_mode() { return mode; }
    	std::string get_codification() { return codification; }

    	void set_codification(std::string c_) { codification = c_; }
    	void set_name(std::string n_) { name = n_; }
        void set_mode(std::string m_) { mode = m_; }
    	void set_dimensions(int w_, int h_) { width = w_; height = h_; }
};

#endif