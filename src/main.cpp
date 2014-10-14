/*
	Simple code to evolve domain wall networks
		J. Pearson (Durham/Nottingham 2014)
		j.pearson@nottingham.ac.uk
*/

// NOTES
// Not the cleverest code (i.e., many arrays & variables are globally defined
// ... and most definitely not object oriented) but the code is pretty quick!
// 

#include "main.h"
#include "setup.h"
#include "ics.h"
#include "pot.h"
#include "evolver.h"

int main(int argc, char* argv[]) {

	// Read the input parameters file, named "params.ini" by default.
	// If there is a command line argument, assume that it is the filename for the parameters file.
	IniReader inifile;
	if (argc > 1)
		inifile.read(argv[1]);
	else
		inifile.read("params.ini");

	// Start timing!
    boost::timer::cpu_timer myTimer;
	
	// Setup parameters
	setuparams(inifile);
	
	// Print welcome message to screen
	printwelcome();
		
	// Check that the output directory exists; if not, code will create it
    checkdirexists(outDIR);
	
	// Print top-matter (run info)
	printtopmatter();
	
	// If we are doing a number of realizations, then this 
	// kicks them all off...
	for(int n=0; n<nreals; n++){

		if(nreals>1)
  		    // report realization number to screen
			cout << n << "/" << nreals << endl;
		
		// Call the main evolution routine
		evreal(n,ttot);	
	}
	
	
	cout << "Completed" << endl;
	
	// Stop timing
    myTimer.stop();
	// Send final time to be printed, along with a polite message	
	printfinalmessage(myTimer.elapsed().wall / 1e6);
	
	
} // END main




/// EOF

