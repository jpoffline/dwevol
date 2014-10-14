/*

	evolver.h

	Contains evolution routines for a given realization

*/


double evreal(int n, int ttot){
	
	double energy,energydensity,pot,gradientenergy,nwalls,oldenergy;
	double phi,phi_ip,phi_im,phi_jp,phi_jm;
    double x,y,a1,a2;
	int    ip,im,jp,jm,tt,tp;
    double h2=h*h, ht2=ht*ht;
	bool   dump=false;
    int    filenum=0;
	int    trail=10000;
	double eom, laptemp;
	vector<double> dpot,lap,fx,fy;
	string filename,realizationID;
	ofstream timehist,filedump;  

	
	// file name prefix for this realization  
	realizationID=to_string(trail+n);
	
	// Setup various vectors to be the correct length (i.e. number of components)
	for(int c=0;c<nflds;c++){
		// dV/dphi_c
		dpot.push_back(0.0);
		// nabla^2phi_c
		lap.push_back(0.0);
		// dphi_c/dx
		fx.push_back(0.0);
		// dphi_c/dy
		fy.push_back(0.0);
	}
	
	 
	// Set the initial conditions
	initialconditions(n);

	
	// Get file name of timehistory
	filename=outDIR+filePREFIX+"_"+realizationID+"_"+timehistoryproto+".dat";
	// Open up timehistory file
	timehist.open(filename);
	
	if(eomtype==3){
		// For full dynamics, use logarithmic outputting steps	
		filedumpfreq=1;
		// Setup the damping coefficient terms
		a1=1.0+0.5*damp*ht;
		a2=1.0-0.5*damp*ht;
	}
	// zero integrated energy
	energy=0.0;
	
    // Begin evolution
    for(int t=0;t<ttot;t++){
	
        // Set the time-step counters for arrays
		tt=t%2;tp=tt+1;
		if(tt==1)tp=0;
	
		// If outputting to file, setup that file
		if((t%filedumpfreq==0 || t==ttot-1) && dumptofile){
			dump=true;
			filename=outDIR+filePREFIX+"_"+realizationID+"_"+to_string(trail+filenum)+".dat";
			filedump.open(filename);
		} 
	
		// Do some setup for damped dynamics, eomtype==3
		if(eomtype==3){
			// Setup the damping coefficient terms for damped evolution
			if (t<tdamp){
			}
			else{
				a1=1.0;
				a2=1.0;
			}
			// double the filedumpfreq
			if(dump)
				filedumpfreq=2*filedumpfreq;
		}
		
		// dump current energy into the old energy 
		oldenergy=energy;
		// zero the integrated energy
		energy=0.0;
		// zero the number of walls
		nwalls=0.0;

		
		// Begin run over space
        for(int i=0;i<imax;i++){
            
			x=(i-0.5*imax)*h;
			ip=i+1;im=i-1;
			if(bctype==1){
            	// Boundary condition: periodic in x
            	if(im==-1)im=imax-1;
            	if(ip==imax)ip=0;
			}
			if(bctype==2){
				// Boundary condition: fix in x-direction
				if(im==-1)im=1;
				if(ip==imax)ip=imax-1;
			}
			
            for(int j=0;j<jmax;j++){
            	
			    y=(j-0.5*jmax)*h;
                jp=j+1;jm=j-1;                
				if(bctype==1 || bctype==2){
                	// Boundary condition: periodic in y
               	 	if(jm==-1)jm=jmax-1;  
					if(jp==jmax)jp=0;
				}
			
				// Now for the main evolution and analysis rountines
			
				// Get phi at this location for easier reading
                phi=fld[tt][0][i][j];
				phi_ip=fld[tt][0][ip][j];
				phi_im=fld[tt][0][im][j];
				phi_jp=fld[tt][0][i][jp];
				phi_jm=fld[tt][0][i][jm];			
			 
				
                // Compute finite difference derivatives
				// Second order accuracy
                for(int c=0;c<nflds;c++){
                    laptemp=0.0;
                    laptemp=laptemp+(phi_ip+phi_im-2.0*fld[tt][c][i][j])/h2;
                    laptemp=laptemp+(phi_jp+phi_jm-2.0*fld[tt][c][i][j])/h2;
					lap[c] = laptemp;
                    fx[c]=(phi_ip-phi_im)/(2.0*h);
                    fy[c]=(phi_jp-phi_jm)/(2.0*h);
                }
                
				// dV/dphi
                dpot=getdpot(phi);
				
				// Compute EoM, then update field according to required prescription
                for(int c=0;c<nflds;c++){
					// Get EoM = \nabla^2\phi - V'
                    eom=lap[c]-dpot[c];
					// 1 = full dynamics
					if(eomtype==1) 
						fld[tp][c][i][j]=ht2*eom+2.0*phi-fld[tp][c][i][j];
					// 2 = gradient flow
					if(eomtype==2) 
						fld[tp][c][i][j]=ht*eom+phi;		
					// 3 = damped dynamics
					if(eomtype==3) 
						fld[tp][c][i][j]=(ht2*eom+2.0*phi-a2*fld[tp][c][i][j])/a1;
                }
			
              	// Do some analysis
				// - currently, computes the energy density & adds onto the 
				// integrated energy

				// Calculate energy density
				
                // Get potential energy V(phi)
                pot=getpot(phi);
				gradientenergy=0.0;
				for(int c=0;c<nflds;c++)
					gradientenergy+=pow(fx[c],2.0)+pow(fy[c],2.0);
				
                energydensity=gradientenergy+pot;
                energy=energy+energydensity*h2;
			
				
			
				// Dump to file
				if(dump)
					filedump << x << " " << y << " " << phi << " " << energydensity << endl;
            
            } // end j-loop
		
			// Print a newline to file
			// Dump to file
			if(dump)
				filedump << endl;	
		
        } // end i-loop
	
		// Close the output file
        if(dump){
        	filedump.close();
			dump=false;
			filenum++;
        }
	
		// Dump timehistory
		timehist << t*ht << " " << energy << endl;
		// Dump to screen
		if(t%screendumpfreq==0){
			if(nreals>1)
				cout << "(r:" << n << "/" << nreals << ") ";
			cout << t << "/"  << ttot << " " << energy << " " << (oldenergy-energy)/ht << endl;
		}
	
	
    }// end t-loop

	// Close timehistory file
	timehist.close();

	return nwalls;
	
} // END evreal()
