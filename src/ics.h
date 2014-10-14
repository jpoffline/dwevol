/*

	ics.h

	Contains initial conditions

*/

double initialconditions(int realn){
	double x, y,val,rho;
	double dumtoret=1;
	srand(time(NULL));
	
	for(int i=0;i<imax;i++){
		x=(i-0.5*imax)*h;
		for(int j=0;j<jmax;j++){
			y=(j-0.5*jmax)*h;
			rho = sqrt(x*x+y*y);
			if(inittype == 0){
				for(int tt=0;tt<2;tt++){
					val=1.0;
					if(x<0)
						val=-1.0;
					fld[tt][0][i][j]=val;
				}
			}	
		}
	}
	
	return dumtoret;
	
} // END initialconditions()