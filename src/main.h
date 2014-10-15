

#include <stdio.h>
#include <string.h>
#include <cmath>  
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer/timer.hpp>
#include <sstream>

using namespace boost::property_tree;
using namespace std;
//#include "inireader.h"

using namespace std;
const double PI=4.0*atan(1.0);

#include "options.h"
#include "inireader.h"
#include "typesinfo.h"
////////////////////////////////////////////////
// The field definition
double      fld[2][nflds][itot][jtot];
////////////////////////////////////////////////

// Some useful auxiliary functions


// Function to check if a directory exists; if not it'll get created
void checkdirexists(string dir){
    
    using namespace boost::filesystem;
    
    if (!exists(dir)) {
        cout << endl;
        cout << " --> Creating output directory" << endl;
        cout << endl;
        
        create_directory(dir);
    }
    
} // END checkdirexists()


// Function to return uniform random number on unit interval
double unitrand(){
	
	return rand()/(double)RAND_MAX;
	
} // END unitrand()

// Print a welcome message
void printwelcome(){
	
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "Simple code to evolve domain wall networks" << endl;
	cout << "J. Pearson (Durham/Nottingham 2014)" << endl;
	cout << "------------------------------------------" << endl;
	cout << endl;
	
} // END printwelcome()


// Print top matter -- mainly info about current run
void printtopmatter(){
	
	cout << endl;
	cout << "Simulation conditions/parameters:" << endl;
	cout << "output dir: " << outDIR << endl;	
	cout << "(imax, jmax) = (" << imax << ", " << jmax << ")" << endl;
	cout << "(h, ht) = (" << h << ", " << ht << ")" << endl;
	printinfo("Potential",pottype);	
	printinfo("BoundaryConditions",bctype);
	printinfo("InitialConditions",inittype);
	printinfo("EoM",eomtype);	
	
		
	
	
	// Compute light-crossing time
	double lx=int(imax*h/2/ht);
	cout << "Light crossing time = " << imax*h/2 << " (lx_time-step = " << lx << ")" << endl;
	
	// If we are stopping at light-crossing (or some fixed multiple thereof), then 
	// code modifies the total number of time-steps here
	if(killatlx){
		ttot=ntimespastlx*lx;
		cout << "Will kill at " << ntimespastlx << " times light-crossing time." << endl;
	}

	cout << "Begin evolution" << endl;
	cout << endl;
		
} // END printtopmatter()

// Print final message
void printfinalmessage(double te){
	
	string tu="ms";
	if(te>1e3){
		te=te/1e3;
		tu="sec";
	}
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "Evolution complete in " << te << tu << endl;
	cout << "------------------------------------------" << endl;
	cout << endl;
	
} // END printfinalmessage()