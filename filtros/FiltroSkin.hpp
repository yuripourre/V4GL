#ifndef FILTROSKIN_HPP
#define FILTROSKIN_HPP

#include "Filtro.hpp"

class FiltroSkin: public Filtro {
	
public:

	FiltroSkin(int w, int h):  Filtro(w,h){}
	
	void filtraSemRuidoVertical(void){
	//void filtra(void){
		
		int i,j;
		
		int line = 3;
		int count = 0;
		
		setColor(0x00,0x00,0xff);
			
		for(i=0;i<w;i++){
			
			for(j=0;j<h;j++){
				
					if(isSkin(r[i][j],g[i][j],b[i][j]))	{
						
						count++;
						
						//setPixel(i,j);
						
					}
					else{
						
						if(count>line){
							
							for(int k=0;k<count;k++){
								//setPixel(i-count+k,j);
								setPixel(i,j-count+k);
								
							}
							
							count = 0;	
						}	
						
					}
					
			}
			
			count = 0;
			
		}
		
		
		
	}	
	
	void filtraNormal(void){
	//void filtra(void){
		
		int i,j;
		
		unsigned int fx = 0;
		unsigned int fy = 0;
		unsigned int p = 0;
		
		setColor(0x00,0x00,0xff);
		
		for(j=0;j<h;j++){	
			
			for(i=0;i<w;i++){
				
					if(isSkin(r[i][j],g[i][j],b[i][j]))	{
						
						setPixel(i,j);
						
						fx += i;
						fy += j;
						p++;

					}
					
			}
			
		}
		
		i = fx / p;
		j = fy / p;
		
		setColor(0x00,0x00,0xff);
		drawCross(i,j,5);
		
	}
	
	void drawGrid(){
		int i,j;
		
		int size = 4;
		
		setColor(0,0,0);
		
		for(i=0;i<w;i+=size){
				
			drawLine(i,0,i,h);
				
		}
		
		for(j=0;j<h;j+=size){	
			
			drawLine(0,j,w,j);
		}
	}
	
	void filtra(void){
		
		int i,j;
		
		unsigned int fx = 0;
		unsigned int fy = 0;
		unsigned int p = 0;
		
		setColor(0x00,0x00,0xff);
		
		//unsigned int ncount = 0;
		
		unsigned int ruido = 5;
		unsigned int count = 0;
		
		int borda = 5;
		
		for(j=borda;j<h-borda;j++){	
		//for(j=borda;j<h-borda;j+=3){	
			
			for(i=borda;i<w-borda;i++){
			//for(i=borda;i<w-borda;i+=2){
				
					if(isSkin(r[i][j],g[i][j],b[i][j]))	{
						
						fx += i;
						fy += j;
						p++;
						
						//if(ncount<=line){
						//	drawLine(i-count-1,j,i,j);
						//	ncount = 0;
						//}
						
						count++;
						if(count>ruido){
							setColor(0,0,0xff);
							setPixel(i,j);
						}
						

					}
					else{
						setColor(0,0,0);
						setPixel(i,j);
						//ncount++;
					}
					
			}
			
			//ncount = 0;
			count = 0;
		}
		
		//i = fx / p;
		//j = fy / p;
		
		setColor(0x00,0x00,0xff);
		
		//drawCross(i,j,5);
		//drawGrid();
		
		
		
	}
	
	
	void findCross(void){
		
		int i,j,borda = 1;
		
		for(j=borda;j<h-borda;j++){	
			
			for(i=borda;i<w-borda;i++){
				
				
				
			}
		}
	}
	
};

#endif
