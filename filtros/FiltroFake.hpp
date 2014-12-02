#ifndef FILTROFAKE_HPP
#define FILTROFAKE_HPP

#include "Filtro.hpp"

class FiltroFake: public Filtro {
	
public:

	FiltroFake(int w, int h):  Filtro(w,h){}
	
	void filtra(void){
		
		int i,j;
	
		setColor(0x00,0x00,0xff);
		
		int offsetY = 50;
		int offsetX = 160;
		int lado = 30;
		
		int PAx = 0+offsetX,  PAy = 0+offsetY;
		int PBx = lado+offsetX, PBy = 0+offsetY;
		int PCx = 0+offsetX,  PCy = lado+offsetY;
		int PDx = lado+offsetX, PDy = lado+offsetY;
		
		//Procura pelo marcador
		/*
		drawLine(PAx,PAy,PBx,PBy);
		drawLine(PCx,PCy,PDx,PDy);
		
		//Linha Vertical
		for(j=PAy;j<PCy+espessura;j++){
			setPixel(PAx,j);
			
			setPixel(PBx,j);
		}
		*/
		
		redutorRuido();
		
		//Reutilizando os pontos
		
		int maiorX = 0;
		int menorX = w;
		
		int maiorY = 0;
		int menorY = h;
		
		
		for(j=0;j<h;j++){	
			
			for(i=0;i<w;i++){
				
				//if((b[i][j]==0xff)
				//&&(g[i][j]==0x00))
				if(g[i][j]-b[i][j]>100)
				{
					
					if(i<menorX){
						//if(PAy>j){
							menorX = i;
							PAx = i;
							PAy = j;
						//}
					}
					else if(i>=maiorX){
						maiorX = i;
						PDx = i;
						PDy = j;
					}
					
					if(j<=menorY){
						menorY = j;
						PBx = i;
						PBy = j;
					}
					else if(j>maiorY){
						maiorY = j;
						PCx = i;
						PCy = j;
					}
					
				}
				
			}
		}
		
		
		//Amarelo A
		setColor(0xff,0xff,0x00);
		drawCross(PAx,PAy,3);
		
		//Rosa B
		setColor(0xff,0x00,0xff);
		drawCross(PBx,PBy,3);
		
		//Vermelho C
		setColor(0xff,0x00,0x00);
		drawCross(PCx,PCy,3);
		
		//Verde D
		setColor(0x00,0xff,0x00);
		drawCross(PDx,PDy,3);
		
		
		
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
