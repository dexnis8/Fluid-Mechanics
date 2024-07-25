

//TME 314 asssignment
// Matric Number: 231604
// Department: Mechanical Engineering
// Question: Create a program that helps with Iteration finding the correct value of the friction factor(f) starting with the users assumed value.

/* 

 This program calculates the relative roughness and Reynolds number from the users assumed value of f.
 This then prompts the user to check their moody diagram using the calculated Reynolds number and relative roughness.
 If the user's calculated Reynolds number is within the given range for the given friction factor, the program will output the calculated Reynolds number and the corresponding Moody chart number.
 If the user's calculated Reynolds number is outside the given range, the program will output a message indicating that the given friction factor is not suitable for the given conditions.
 This then prompts the user again with a new calculated Reynolds Number from the new value of friction factor(f) obtained from the moody diagram.
 The program continues this process until it finds a suitable friction factor(f) which satisfies the given conditions.

 */
// NOTE: This program is written in C++

// Beginning of the program
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


// Constants
const double kineticViscosity = 1.13 * pow(10, -6);
const double g = 9.81; // acceleration due to gravity

// Function to calculate the velocity which is needed to get the Reynolds number
double calculateVelocity(double headLoss, double diameter, double length, double fValue) {
    return sqrt((headLoss * diameter * 2 * g) / (fValue * length));
}

// Function to calculate the relative roughness
double calculateRelativeRoughness(double absoluteRoughness, double diameter) {
    return absoluteRoughness / diameter;
}

// Function to calculate the Reynolds number
double calculateReynoldsNumber(double velocity, double diameter) {
    return (velocity * diameter) / kineticViscosity;
}

// Function to round a value to significant figures
double roundToSignificantFigures(double value, int sigFigs) {
    if (value == 0.0) return 0.0;
    double scale = pow(10, sigFigs - 1 - floor(log10(abs(value))));
    return round(value * scale) / scale;
}

int main() {
    cout << "This program assumes the following values are given  (head loss, diameter of the pipe, length of the pipe, absolute roughness)" << endl;

    // Accepting the necessary parameters from the user
    double headLoss, diameter, length, absoluteRoughness, assumedValueOfF;
    cout << "Enter the head loss (in meters): ";
    cin >> headLoss;
    cout << "Enter the diameter of the pipe (in meters): ";
    cin >> diameter;
    cout << "Enter the length of the pipe (in meters): ";
    cin >> length;
    cout << "Enter the absolute roughness (in meters): ";
    cin >> absoluteRoughness;
    cout << "Enter the value of the assumed f: ";
    cin >> assumedValueOfF;

    // Calculated value of the velocity
    double velocity = calculateVelocity(headLoss, diameter, length, assumedValueOfF);

    // Calculated value of the relative roughness
    double relativeRoughness = calculateRelativeRoughness(absoluteRoughness, diameter);

    // Calculated value of the Reynolds number
    double reynoldsNumber = calculateReynoldsNumber(velocity, diameter);

    cout << fixed << setprecision(6);
    cout << "This is the calculated velocity: " << velocity << endl;
    cout << "This is the calculated relative roughness: " << relativeRoughness << endl;
    cout << "This is the calculated Reynolds number: " << reynoldsNumber << endl;

    // Prompts the user to enter the new value for f as read in the moody diagram
    double newValueOfF;
    cout << "Using the calculated Reynolds number and relative roughness, enter the new value of f obtained from the moody diagram: ";
    cin >> newValueOfF;

    // The condition to stop the loop is if there's no change in the first 2 significant figures of the friction factor (f)
    while (roundToSignificantFigures(assumedValueOfF, 2) != roundToSignificantFigures(newValueOfF, 2)) {
        velocity = calculateVelocity(headLoss, diameter, length, newValueOfF);
        reynoldsNumber = calculateReynoldsNumber(velocity, diameter);
        cout << "This is the new calculated velocity: " << velocity << endl;
        cout << "This is the relative roughness: " << relativeRoughness << endl;
        cout << "This is the new calculated Reynolds number: " << reynoldsNumber << endl;
        cout << "Using the newly calculated Reynolds number and relative roughness, enter the new value of f obtained from the moody diagram: ";
        cin >> newValueOfF;
    }

    if (roundToSignificantFigures(assumedValueOfF, 2) == roundToSignificantFigures(newValueOfF, 2)) {
        cout << "The new value of f matches the assumed value. No further calculations needed. All conditions/equations are satisfied." << endl;
    }

    return 0;
}
