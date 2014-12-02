#ifndef FILTROFLOODFILL_HPP
#define FILTROFLOODFILL_HPP

#include "Filtro.hpp"

class FiltroFloodFill: public Filtro {
	
public:

	FiltroFloodFill(int w, int h):  Filtro(w,h){}

	/*

	Picked from 	
	http://stackoverflow.com/questions/1257117/does-anyone-have-a-working-non-recursive-floodfill-algorithm-written-in-c
	answered Aug 10 '09 at 21:06 by rlbond

	*/
	
	void connectedRegion(const Point& source/*, RegionType& region, const Color target*/)
	{
		
		setColor(0,0,0xff);
		//region = r[][],g[][],b[][];
		//Color src_color = getColor(source);
		Color src_color = Color(0xff,0,0);
		
		queue<Point> analyze_queue;
		analyze_queue.push(source);

		while (!analyze_queue.empty())
		{
			//Point p = analyze_queue.front();
			if (getColor(analyze_queue.front()) != src_color)
			{
				analyze_queue.pop();
				continue;
			}
			Point leftmost_pt = analyze_queue.front();
				leftmost_pt.setOffsetX(-1);//leftmost_pt.col -= 1;
				
			analyze_queue.pop();
			
			Point rightmost_pt = leftmost_pt;
				//rightmost_pt.col += 2;
				rightmost_pt.setOffsetX(2);
			while (getColor(leftmost_pt) == src_color){
				leftmost_pt.setOffsetX(-1);//--leftmost_pt.col;
			}
	
			while (getColor(rightmost_pt) == src_color){
				if(rightmost_pt.getX()<w-1){
					rightmost_pt.setOffsetX(+1);//++rightmost_pt.col;
				}
				else{
					break;
				}
			}

			bool check_above = true;
			bool check_below = true;
				Point pt = leftmost_pt;
				pt.setOffsetX(1);//++pt.col;
				
			while(pt.getX() < rightmost_pt.getX())
			{
				pt.setOffsetX(1);
				
				setColor(0,0,0xff);
				setPixel(pt.getX(),pt.getY());//set_color(pt, region, target);
				

				Point pt_above = pt;
					pt.setOffsetY(-1);//--pt_above.row;
						
				if (check_above)
				{
					if (getColor(pt_above) == src_color)
					{
						analyze_queue.push(pt_above);
						check_above = false;
					}
				}
				else // !check_above
				{
					check_above = (getColor(pt_above) != src_color);
				}

				Point pt_below = pt;
						pt.setOffsetY(+1);//++pt_below.row;
						
				if (check_below)
				{
					if (getColor(pt_below) == src_color)
					{
						analyze_queue.push(pt_below);
						check_below = false;
					}
				}
				else // !check_below
				{
					check_below = (getColor(pt_below) != src_color);
				}
			} // for 
		} // while queue not empty

	}
	
	
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
		
		//cout<<rx<<" "<<ry<<endl;
		const Point p(rx,ry);
		connectedRegion(p);
		
		setColor(0,0,0);
		drawCross(rx-1,ry-1,5);
		drawCross(rx+1,ry-1,5);
		drawCross(rx+1,ry+1,5);
		drawCross(rx-1,ry+1,5);
		
		setColor(0xff,0xff,0);
		drawCross(rx,ry,5);
		
	}
	
	
};

#endif
