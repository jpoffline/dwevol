/*

	function to print types info
	... boundary conditions (fixed, periodic, etc)
	... initial conditions (random, idealised, etc)
	... equation of motion (damped, gradient flow, etc)

*/



void printinfo(string type, int option){
	
	// Setup identifiers to use in switches
	int typeID;
	if(type == "BoundaryConditions")
		typeID = 0;
	if(type == "InitialConditions")
		typeID = 1;
	if(type=="EoM")
		typeID = 2;
	if(type=="Potential")
		typeID = 3;
	cout << type << " = " << option << " :: ";
	
	switch(typeID){
		case 0:
			switch(option){
				case 1: 
					cout << "periodic" << endl;
					break;
				case 2: 
					cout << "fixed in x, periodic in y" << endl;
					break;
				default:
					cout << "cant find a description for " << type << endl;
					break;
			}
			break;
			
		case 1:
			switch(option){
				case 0: 
					cout << "one wall" << endl;
					break;
				default:
					cout << "cant find a description for " << type << endl;
					break;
			}
			break;
			
		case 2:
			switch(option){
				case 1: 
					cout << "full dynamics" << endl;
					break;
				case 2: 
					cout << "gradient flow" << endl;
					break;
				case 3: 
					cout << "damped dynamics, then full :: " ;
					cout << "(tdamp, damping) = (" << tdamp << " ," << damp << ")" << endl;		
					break;
				default:
					cout << "cant find a description for " << type << endl;
					break;
			}
			break;
		case 3:
			switch(option){
				case 1: 
					cout << "simple Z2" << endl;
					break;
				default:
					cout << "cant find a description for " << type << endl;
					break;
			}
			break;
		default:
			cout << "dont know what " << type << " is" << endl;
			break;
	}
	
	
}