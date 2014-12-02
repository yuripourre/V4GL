#ifndef FILTRO_HPP
#define FILTRO_HPP

#include "../util/Color.hpp"
#include "../util/Point.hpp"



#include <iostream>
#include <queue>

using namespace std;

class Filtro {

protected:

	int w;
	int h;
	int channels; //Normally RGB
	
	int colorR;    //State-Machine Color
	int colorG;    //State-Machine Color
	int colorB;    //State-Machine Color
	
	
	unsigned char** r;
	unsigned char** g;
	unsigned char** b;
	
	unsigned char* pixels;
	float* dst;
	
	
	
private:

	unsigned char* invert(unsigned char* dst){
		
		int tam = w*h*3;
  
		int i=0;
  
		for(i=0;i<tam;i+=3) {
			//pega o pixel invertido e em RBG
			pixels[i+0] = dst[tam-(i+0)];			
			pixels[i+1] = dst[tam-(i+1)];
			pixels[i+2] = dst[tam-(i+2)];
		}
		
		return pixels;
		
	}
	
public:
	
	Filtro(int w, int h){
		this->w = w;
		this->h = h;
		this->channels = 3;
		
		this->pixels = new unsigned char[w*h*channels];
		this->dst = new float[w*h*channels];
		
		r = new unsigned char*[w];
		g = new unsigned char*[w];
		b = new unsigned char*[w];
		
		int i;
		for(i=0;i<w;i++){
			r[i] = new unsigned char[h];
			g[i] = new unsigned char[h];
			b[i] = new unsigned char[h];
		}
		
	}	
	
	~Filtro(){
		
		delete[] pixels;
		delete[] dst;
		delete[] r;
		delete[] g;
		delete[] b;
		
	}
	
	virtual void filtra(void){};
	
	void setImage(unsigned char* dst){
		
		int i,j;
		
		unsigned char* img = invert(dst);
		
		for(j=0;j<h;j++){
			for(i=0;i<w;i++){
				r[i][h-j] = img[i*3+0+w*j*3];
				g[i][h-j] = img[i*3+2+w*j*3];
				b[i][h-j] = img[i*3+1+w*j*3];
			}
		}
		
	}
	
	void setColor(Color color){
		
		colorR = color.getRed();
		colorG = color.getGreen();
		colorB = color.getBlue();
		
	}
	
	void setColor(int r, int g, int b){
		
		colorR = r;
		colorG = g;
		colorB = b;
		
	}
	
	float* getPixels(){

		int i,j;
		
		for(j=0;j<h;j++){
			for(i=0;i<w;i++){
				dst[i*3+0+w*j*3] = (float)r[i][h-j]/255;
				dst[i*3+1+w*j*3] = (float)g[i][h-j]/255;
				dst[i*3+2+w*j*3] = (float)b[i][h-j]/255;
			}
		}
		
		
		return dst;
	}
	
	bool compare(int cor, int verify, int tolerance){
		
		if((cor+tolerance>=verify)&&(cor-tolerance<=verify)){
			return true;
		}
		
		return false;
		
	}
	
	int diferenceMod(int cor, int verify){
		int dif = cor-verify;
		if(dif<0){
			dif*=-1;
		}
		return dif;
	}
	
	bool isSkin(int r, int g, int b){
		
		//Falso positivo
		//2E111C
		//34131D
		
		//Cores extremas
		if((r<160)
		&&(r>35)
		
		&&(r>g)&&(r>b)
		
		//Evitar Rosa
		//&&(r-b<30)&&(r-b>0)//Ruim
		//&&(r-g<30)&&(r-g>0)//Ruim
		
		//Cuidado com peles escuras
		//&&(r-b<40)&&(r-b>10)
		//&&(r-g<40)&&(r-g>10)
		
		
		&&(diferenceMod(g,b)<21)){
			return true;
		}
		
		return false;
	}
	
	bool isInside(int i, int j, int size){
		
		if((i+size<=w)
		&&(j+size<=h)
		&&(i-size>=0)
		&&(j-size>=0))
		{
			return true;
		}
		return false;
		
	}
	bool isInside(int i, int j){
		
		return isInside(i,j,0);
	}
	
	void setPixel(int x, int y){
		r[x][y] = colorR;
		g[x][y] = colorG;
		b[x][y] = colorB;
	}
	
	void setPixel(Point p){
		int x = p.getX();
		int y = p.getY();
		
		r[x][y] = colorR;
		g[x][y] = colorG;
		b[x][y] = colorB;
	}
	
	int getRed(int x, int y){
		return r[x][y];
	}
	int getGreen(int x, int y){
		return g[x][y];
	}
	int getBlue(int x, int y){
		return b[x][y];
	}
	
	Color getColor(int x, int y){
		return Color(getRed(x,y),getGreen(x,y),getBlue(x,y));
	}
	
	Color getColor(Point point){
		int x = point.getX();
		int y = point.getY();
		
		return Color(getRed(x,y),getGreen(x,y),getBlue(x,y));
	}
	
	void drawLine(int x1, int y1, int x2, int y2){
		
		int dx = x2 - x1;
		int dy = y2 - y1;
		
		int x,y;
		
		if(x1!=x2){
		
			for(x=x1;x<x2;x++){
				y = y1 + (dy) * (x - x1)/(dx);
				setPixel(x, y);
			}
		}
		else{
			for(y=y1;y<y2;y++){
				setPixel(x1,y);
			}
		}
		
	}
	
	void drawCross(int i, int j, int size){
		int c;
		
		if(isInside(i,j,size))
		{
			setPixel(i,j);
		
			for(c=0;c<size;c++){
				
				setPixel(i+c,j);
				setPixel(i-c,j);
				setPixel(i,j-c);
				setPixel(i,j+c);
					
			}
			
		}
		
	}
	
	void drawCross(int i, int j){
		drawCross(i,j,2);
	}
	
};

#endif
