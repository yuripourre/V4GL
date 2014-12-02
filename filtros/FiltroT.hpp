#ifndef FILTROT_HPP
#define FILTROT_HPP

#include "Filtro.hpp"

class FiltroT: public Filtro {
	
public:

	FiltroT(int w, int h):  Filtro(w,h){}
	
	void filtra(void){
		
		int i,j,k;
	
		//setColor(0x00,0x00,0xff);
		
		int borda = 5;
		
		unsigned int rx = 0,ry = 0;
		unsigned int rline = 10;
		unsigned int linew = 0;
		unsigned int lineh = 0;
		unsigned int line;
		unsigned int x;
		
		
		
		for(j=borda;j<h-borda;j++){	
		//for(j=borda;j<h-borda;j+=3){	
			
			for(i=borda;i<w-borda;i++){
			//for(i=borda;i<w-borda;i+=2){
				
					if(isSkin(r[i][j],g[i][j],b[i][j]))	{
						
						setPixel(i,j);
						
						for(k=i+1;k<w-borda;k++){	
							if(isSkin(r[k][j],g[k][j],b[k][j]))	{		
								linew++;
								setColor(0xff,0,0);
								setPixel(k,j);
							}
							else{
								break;
							}
						}
						
						if(linew>5){
							
							for(k=j;k<h-borda;k++){	
								
								x = i+linew/2;
								
								if(isSkin(r[x][k],g[x][k],b[x][k]))	{		
									lineh++;
								}
								else{
									break;
								}
							}
							
							line = linew+lineh;
							if(line>rline){
								rline = line;
								rx = i;
								ry = j;
							}
							
						}

					}
					else{
						linew = 0;
					}
					
			}
			
		}	
		
		
		
		setColor(0,0,0);
		drawCross(rx-1,ry-1,5);
		drawCross(rx+1,ry-1,5);
		drawCross(rx+1,ry+1,5);
		drawCross(rx-1,ry+1,5);
		
		setColor(0xff,0xff,0);
		drawCross(rx,ry,5);
		
		//cout<<rx<<" "<<ry<<endl;
		
	}
	
	
	
	
	
};

#endif
