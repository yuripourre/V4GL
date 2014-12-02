#ifndef FILTROC_HPP
#define FILTROC_HPP

#include "Filtro.hpp"

class FiltroC: public Filtro {
	
public:

	FiltroC(int w, int h):  Filtro(w,h){}
	
	void filtra(void){
		
		bool activate;
	
		int i,j;
	
		for(j=0;j<h;j++){
			
			activate = true;
			
			
			
			for(i=0;i<w;i++){
				
				if((activate)
				&&(r[i][j]>0x25)
				&&(compare(r[i][j],g[i][j],10))){
					//Pinta de Branco
					r[i][j] = 0xff;
					g[i][j] = 0xff;
					b[i][j] = 0xff;	
				}
				else if (compare(r[i][j],g[i][j],20)){
					//Pinta de Branco
					r[i][j] = 0x00;
					g[i][j] = 0xff;
					b[i][j] = 0x00;	
				}
				else{
					//stroke(i,j,1);
					r[i][j] = 0x00;
					g[i][j] = 0x00;
					b[i][j] = 0x00;
					
					
					//Calcula Quad,
					//Mais perfeito achou!
				}
					
			}
			
		}
		
	}
	
	void stroke(int i, int j, int stroke){
		
		int s;
		
		if((i>=stroke)&&(i+stroke<=w)
		&&(j>=stroke)&&(j+stroke<=h)){
			
			r[i][j] = 0x00;
			g[i][j] = 0x00;
			b[i][j] = 0x00;
			
			for(s=0;s<stroke;s++){
				r[i][j-s] = 0x00;
				g[i][j-s] = 0x00;
				b[i][j-s] = 0x00;
				
				r[i][j+s] = 0x00;
				g[i][j+s] = 0x00;
				b[i][j+s] = 0x00;
			}
			
		}
		
	}
	
	void setColor(int r, int g, int b){
		this->color = (r<<4)+(g<<2)+b;
	}
	
	bool compare(int cor, int verify, int tolerance){
		
		if((cor+tolerance>=verify)&&(cor-tolerance<=verify)){
			return true;
		}
		
		return false;
		
	}
	
};

#endif
