/*
    The author: Quan Nguyen
    The Assignment Name: A1-An Ecological Simulation
    Description: This program is used to generate a chart which simulate the predator-prey relationship by using the Lotka-Volterra equation
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

// Pre-Set constant variables //
#define SCALE_FACTOR 0.1
#define rabbitGrowth 0.2
#define predictionRate 0.0022
#define foxPreyConversion 0.6
#define foxMortalityRate 0.2
#define carryCapacity 1000.0

// Functions Prototypes
void plotPopulations(double rabbitNum, double foxNum, double scaleFactor);
void plotCharacter(int number, char character);
void updatePopulations(double g, double p, double c, double m, double K,
                       double& rabbitNum, double& foxNum);
void runSimulation(int iter, double rabbitNum, double foxNum);
void incrementCounter(int* iter);
/////////////////////////////////////////////////////////////////////////


int main(){
    double foxNum, rabbitNum;
   

    std::cout << "Welcome to the ecological simulation" << std::endl;

    std::cout << "Enter the amount of foxes: ";
    std::cin >> foxNum;

    // if the input not a double, give warning and terminate program
    if(std::cin.fail()){
        std::cout << "This is not double. Terminating the program." << std::endl;
        return 0;
    }
    std::cout << std::endl;

    std:: cout << "Enter the amount of rabbits: ";
    std::cin >> rabbitNum;

    // if the input not a double, give warning and terminate program
    if(std::cin.fail()){
        std::cout << "This is not double. Terminating the program." << std::endl;
        return 0;
    }
    std::cout << std::endl;
    
    static const double predatorPop = foxNum;
    static const double preyPop = rabbitNum;

    runSimulation(500, preyPop, predatorPop);

    return 0;
}

/* 
    This function is used for checking the population between foxes and rabbits before
    computing the necessary space for each character then call the plotCharacter function
*/
void plotPopulations(double rabbitNum, double foxNum, double scaleFactor){
    
    int rabbitSpace = floor(rabbitNum * scaleFactor);
    int foxSpace    = floor(foxNum    * scaleFactor);

    if(rabbitSpace == foxSpace){
        plotCharacter(rabbitSpace, '*');
    }

    else if(rabbitSpace > foxSpace){
        plotCharacter(foxSpace, 'F');

        rabbitSpace = rabbitSpace - foxSpace;
        plotCharacter(rabbitSpace - 1, 'r');
    }

    else{
        plotCharacter(rabbitSpace, 'r');
        foxSpace = foxSpace - rabbitSpace;

        plotCharacter(foxSpace - 1, 'F');
    }

 
}

// This function is used for running the simulation with an the passing number of iteration
void runSimulation(int iter, double rabbitNum, double foxNum){

    int iteration = 0;

    // Initial population line
    plotPopulations(rabbitNum, foxNum, SCALE_FACTOR);
    std::cout << std::endl;

    while(iteration < iter){
        if(rabbitNum < 1 || foxNum < 1) return;

        else
        {
            updatePopulations(rabbitGrowth, predictionRate, foxPreyConversion, foxMortalityRate, carryCapacity,
                rabbitNum, foxNum);

             // After calculating the change in populations, start plotting for the graphs.
            plotPopulations(rabbitNum, foxNum, SCALE_FACTOR);

            // Add an newline whenever called
            std::cout << std::endl;
        }

        incrementCounter(&iteration);


    }

}

// This function is used for printing out the space and the character on to the terminal
void plotCharacter(int number, char character){
    if(number < 1 )
    {
        std::cout << character;
    }

    else
    {
        for(int i = 0; i < number; i++){
            std::cout << " ";
        }
        std::cout << character;
    }
}



/* 
    This function is used to compute and update the number of foxes and 
    rabbits through each iteration and call the plotPopulation function. 
*/

void updatePopulations(double g, double p, double c, double m, double K,
                       double& rabbitNum, double& foxNum)
{
    // Change in rabbits population formula
    double deltaRabbit = g * rabbitNum * (1-rabbitNum/K) - p * rabbitNum * foxNum;

    // Change in foxes population formula 
    double deltaFox = c * p * rabbitNum * foxNum - m * foxNum;

    rabbitNum += deltaRabbit;
    foxNum += deltaFox;

   
}


// This function is used for incrementing the iteration in the runSimulation function
void incrementCounter(int* iter){
    int increment = *iter + 1;

    *iter = increment;
}

