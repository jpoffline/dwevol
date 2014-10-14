// options.h
// All parameters here get set from params.ini

//// -------------------------------- ////
///// GRID PROPERTIES
//// -------------------------------- ////
// Note: these are used to construct the array "fld"... a user can specify smaller grid
// in params.ini... but, larger will require these to be modified to encompass the larger
// number of grid-points
const int   itot=512;				// Number of grid-points in i-direction
const int   jtot=512;				// Number of grid-points in j-direction
int 		imax, jmax;
const int   nflds=1;        		// Number of scalar fields in total
double  	h;         				// space step-size
double  	ht;         			// time step-size (take note of Courant stability conditions)
int     	ttot;       			// total number of time-steps (gets over-written if killatlx=true)
//// -------------------------------- ////
//// -------------------------------- ////



//// -------------------------------- ////
///// DUMP PARAMETERS/OPTIONS
//// -------------------------------- ////
bool		dumptofile;				// Should we *ever* dump fields to file?
int 		filedumpfreq;			// Frequency (in t-steps) to dump to file
									// (gets reset if making a video)
int			screendumpfreq;			// Frequency (in t-steps) to dump info to screen
string 		outDIR;					// Output directory
string 		filePREFIX;				// Prefix of field/energy-files
string		timehistoryproto; 		// Prefix of time-history file
//// -------------------------------- ////
//// -------------------------------- ////




//// -------------------------------- ////
///// EVOLUTION SETTINGS
//// -------------------------------- ////
int   		nreals;				// Number of realizations (set to 20 for useful averages)
bool 		killatlx;			// Should we kill at light-crossing-time?
int 		ntimespastlx;		// number of times to run past lx (=1 for "physical" random ICs, =4 for percolation)
int 		eomtype; 				

int			tdamp;				// Time to stop damping			
double		damp;				// Damping magnitude


//// -------------------------------- ////
/////	Type settings
//// -------------------------------- ////
int			bctype;				
int			pottype;
int			inittype;			
//// -------------------------------- ////
//// -------------------------------- ////






/// EOF