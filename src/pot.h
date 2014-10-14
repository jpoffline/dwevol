/*

	pot.h

	Contains scalar potential V(phi), and V'(phi)

*/


double getpot(double phi){
	
	
	if(pottype==1)
		return 0.25*(phi*phi-1.0)*(phi*phi-1.0);
	else
		return 0.0;
	
}

vector<double> getdpot(double phi){
	
	vector<double> dpot;
	
	if(pottype==1){
		for(int c=0;c<nflds;c++)
			dpot.push_back(phi*(phi*phi-1.0));	
	}
	
	return dpot;
	
}