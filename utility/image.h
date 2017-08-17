#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image {
	private:
		int width; // lower left corner of the view plane.
    	int height; // Horizontal dimension of the view plane.

    public:
    	Image(int w_=0, int h_=0) 
			: width(w_), height(h_) {}
			
    	int get_width() { return width; }
    	int get_height() { return height; }
};

#endif