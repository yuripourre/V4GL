#ifndef FILTROAUMENTADO_HPP
#define FILTROAUMENTADO_HPP

#include "Filtro.hpp"

class FiltroAumentado: public Filtro {
	
public:

	FiltroAumentado(int w, int h):  Filtro(w,h){}
	
	void filtra(void){
		
		int i,j;
	
		setColor(0x00,0x00,0xff);
		
		for(j=0;j<h;j++){	
			
			for(i=0;i<w;i++){
				
					//4E4D70
					if(
					(b[i][j]>r[i][j])&&(b[i][j]>g[i][j])					
					&&(r[i][j]>10)
					&&(r[i][j]<55)
					&&(g[i][j]>10)
					&&(g[i][j]<55)
					)					
					{
						
						setPixel(i,j);						

					}
					
			}
			
		}
		
		redutorRuido();
		
	}
	
	void redutorRuido(void){
		
		int i,j;
		
		for(j=1;j<h;j++){	
			
			for(i=1;i<w;i++){
				
					//4E4D70
					if((b[i-1][j]==0xff)					
					&&(b[i][j-1]==0xff))
					{
						
						setPixel(i,j);						

					}
					
			}
			
		}
	}
	
};

#endif
