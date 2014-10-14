/*

	Routine to read in inifile & set values of parameters

*/


double setuparams(IniReader &init){
	
	h = init.getiniDouble("h", 0.25, "Main");
	ht = init.getiniDouble("ht", 0.1, "Main");	
	ttot = init.getiniInt("ttot", 1000, "Main");		
	imax = init.getiniInt("imax", 512, "Main");		
	jmax = init.getiniInt("jmax", 512, "Main");			
	
	nreals = init.getiniInt("nreals", 1, "Main");		
	killatlx = init.getiniBool("killatlx", true, "Main");		
	ntimespastlx = init.getiniInt("ntimespastlx", 1, "Main");		
	
	eomtype = init.getiniInt("eomtype", 1, "Main");		
	tdamp = init.getiniInt("tdamp", 200, "Main");		
	damp = init.getiniDouble("damp", 5.0, "Main");
	bctype = init.getiniInt("bctype", 1, "Main");		
	pottype = init.getiniInt("pottype", 1, "Main");	
	inittype = init.getiniInt("inittype", 0, "Main");	
	
	outDIR = init.getiniString("outDIR", "data/", "Dump");		
	filePREFIX = init.getiniString("filePREFIX", "file", "Dump");	
	timehistoryproto = init.getiniString("timehistoryproto", "timehistory", "Dump");	
	screendumpfreq = init.getiniInt("screendumpfreq", 20, "Dump");	
	dumptofile = init.getiniBool("dumptofile", true, "Dump");		
	filedumpfreq = init.getiniInt("filedumpfreq", 1000, "Dump");	
	return 1.0;
	
} // END setuparams()