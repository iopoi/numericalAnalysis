//Nicholas Cataldo
//AMS 326 HW1

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// --- Constants and Structs --- //

float accuracy = 0.0001;

//this struct gets used for the bisection and newton methods
typedef struct{
	float lbound;
	float ubound;
	int success;
	int iterations;
} approximation;


// --- Helper Methods --- //

// returns the result from the function f(x)
float fn(float x){
	return pow(2.016, pow((-1*x),3))-(pow(x,4)*sin(pow(x,3)))-1.949;
}

// the algebraic derivative of fn
float fn1(float x){
	return (-2.10335)*pow(2.016, pow(-x, 3))*pow(x, 2)
            - 4*pow(x, 3)*sin(pow(x, 3))
            - 3*pow(x, 6)*cos(pow(x,3));
}

// the numeric derivative of fn
float nfn1(float x){
	float delta = 0.00001525878907;

	// change in Y / change in X
	return (fn(x+delta)-fn(x-delta))/(delta+delta);
}

// finds the midpoint between two given inputs
float midpoint(float a, float b){
	return (a+b)/2;
}


// --- Calculation Methods --- //

//struct usage for newton method
//lbound: starting point (guess point)
//ubound: solution (gets filled after the function finishes)
//success: sucess status
//iteration: # of iterations
void newton(approximation* a){
	float n0;
	float n1 = a->lbound;
	int iteration = 0;
	do{
		n0 = n1;
		n1 = n0 - fn(n0)/nfn1(n0);
		iteration++;
		if(iteration>500){
			a->success = 0;
			a->iterations = iteration;
			return;
		}
	}while(n1-n0 > accuracy);

	a->ubound = n1;
	a->success = 1;
	a->iterations = iteration;

	return;
}

//struct usage for bisection method
//lbound: lower bound guess (gets set to solution after function finishes)
//ubound: upper bound guess (gets set to solution after function finishes)
//success: sucess status
//iteration: # of iterations
// this function modifies the approximation struct
// to contain the approximation
void bisection(approximation *a){
	// if the approximation is of sufficient accuracy
	// then return.
	if(accuracy>(a->ubound - a->lbound)){
		a->success=1;
		return;
	}

	//counts the iterations
	a->iterations++;

	// calculates midpoint
	float mid = midpoint(a->lbound, a->ubound);

	// if the lbound and mid straddle 0, then
	if((fn(a->lbound) < 0 && 0 < fn(mid)) 
		|| (0 < fn(a->lbound) && fn(mid) < 0)){
		//a->lbound = a->lbound;
		a->ubound = mid;
		// recursive call
		bisection(a);

	} // if the mid and ubound straddle 0, then
	else if((fn(mid) < 0 && 0 < fn(a->ubound)) 
		|| (0 < fn(mid) && fn(a->ubound) < 0)){
		a->lbound = mid;
		//a->ubound = a->ubound;
		// recursive call
		bisection(a);

	}else{ //something failed
		a->success=0;
	}
	// this will stop the function when the recursive calls finish.
	return;
}

// --- Main Method --- //

int main(int argc, char** argv){
	
	//gets the args from the command line
	float l = strtof(argv[1],NULL);
	float u = strtof(argv[2],NULL);

	//struct setup
	approximation bsct;
	bsct.lbound=l;
	bsct.ubound=u;
	bsct.iterations=0;
	bsct.success=0;

	approximation nwtn;
	nwtn.lbound=l;
	nwtn.ubound=0;
	nwtn.iterations=0;
	nwtn.success=0;

	// runs the bisection method
	bisection(&bsct);
	// print results
	printf("Bisection\n");
	printf("Approximation  [%f, %f] - %s\n",
		 bsct.lbound, bsct.ubound, bsct.success ? "success" : "fail");
	printf("Root: %f  Error+_: %f\n", 
		midpoint(bsct.lbound, bsct.ubound), (bsct.ubound - bsct.lbound)/2 );
	printf("Number of iterations %d\n", bsct.iterations);

	// runs newtons method.
	newton(&nwtn);
	// print results
	printf("\nNewton\n");
	printf("Root: %f - %s\n", 
		bsct.ubound, bsct.success ? "success" : "fail");
	printf("Error+_: %f\nIterations: %d\n", 
		accuracy/2, nwtn.iterations);
	printf("\n");
}
