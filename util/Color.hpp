#ifndef COLOR_HPP
#define COLOR_HPP

class Color {

private:
	int red;
	int green;
	int blue;
	
public:

	Color(int r, int g, int b){
		this->red = r;
		this->green = g;
		this->blue = b;
	}
	
	int getRed(){
		return red;
	}
	int getGreen(){
		return green;
	}
	int getBlue(){
		return blue;
	}

};

	bool operator == (Color c1, Color c2)
	{
    return (c1.getRed() == c2.getRed() &&
            c1.getGreen() == c2.getGreen() &&
            c1.getBlue() == c2.getBlue());
	}
	
	bool operator!= (Color c1, Color c2)
	{
		return !(c1 == c2);
	}

#endif
