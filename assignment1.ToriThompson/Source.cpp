#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//Name:Tori Thompson

//Assignment 1 - Program to get meat type, cost and output to a file to create a receipt

double getValidCost();
void printBill(char, double, double, double, double);
double determineMeatCost(char);
char getValidMeat();
double validateWeight(double);

int main()
{
	double cost;
	char meatType;
	double meatCost, meatWeight, dairyCost, miscCost;
	int custAmount = 0;
	string answer;

	do
	{
		meatType = getValidMeat();
		meatCost = determineMeatCost(meatType);
		cout << "Enter the weight of the meat: " << endl;
		cin >> meatWeight;
		meatWeight = validateWeight(meatWeight);
		cout << "Getting dairy cost" << endl;
		dairyCost = getValidCost();
		cout << "Getting miscellaneous cost" << endl;
		miscCost = getValidCost();
		printBill(meatType, meatCost, dairyCost, miscCost, meatWeight);
		custAmount++;
		cin.ignore(80, '\n');
		cout << "Press enter to handle next customer or ctrl Z to close cash." << endl;
		getline(cin, answer);
	} while (!cin.eof());
	
	cout << "The number of customers you entered was: " << custAmount << endl;

	system("pause");
}//end of main
//Function to ensure user is only entering B, C or F for valid meat types
char getValidMeat()
{
	char meatType;
	cout << "Enter B for beef, C for chicken or F for fish: " << endl;
	cin >> meatType;
	meatType = toupper(meatType);
	while (meatType != 'B' && meatType != 'C' && meatType != 'F' || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Sorry you must enter B, F or C, try again:" << endl;
		cin >> meatType;
		meatType = toupper(meatType);
	}
	return meatType;
}
//Function to validate the weight of the meat and ensure no input failure
double validateWeight(double passedWeight)
{
	while (passedWeight < 0.0 || passedWeight > 50.0 || cin.fail())
	{
		cout << "Sorry you must enter a weight between 0.1-50.0kg, enter again:" << endl;
		cin >> passedWeight;
	}
	return passedWeight;
}
//Function to determine cost of meat based on user input
double determineMeatCost(char passedMeatType)
{
	double returnMeatCost;
	switch (passedMeatType)
	{
	case 'B':
		returnMeatCost = 8.80;
		break;
	case 'C':
		returnMeatCost = 5.49;
		break;
	default:
		returnMeatCost = 6.59;
		break;
	}
	return returnMeatCost;
}
// Function to validate dairy and misc cost input 
double getValidCost()
{
	double costEntered;
	cout << "Please enter the cost:" << endl;
	cin >> costEntered;
	while (costEntered < 1.0 || costEntered > 150.0 || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Sorry your cost must be between 1.0 and 150.0, enter again:" << endl;
		cin >> costEntered;
	}
	return costEntered;
}
//Funtion to open file, using passed parameters to print bill information
void printBill(char passedMeatType, double passedMeatCost, double passedDairyCost, double passedMiscCost, double passedMeatWeight)
{
	string fullMeatType;
	ofstream fout("receipt.txt");
	if (!fout.is_open())
	{
		cout << "Unable to open file receipt.txt";
		exit(-1);
	}
	fout << fixed << setprecision(2);
	switch (passedMeatType)
	{
	case 'B':
		fullMeatType = "Beef";
		break;
	case 'C':
		fullMeatType = "Chicken";
		break;
	case 'F':
		fullMeatType = "Fish";
		break;
	}
	fout << "---------------------------------------------" << endl;
	fout << "ABC Grocery Store" << endl << endl;
	fout << "Items bought:" << endl << endl;
	fout << left << setw(5) << "Meat " << setw(7) << fullMeatType << setw(4) << " @ $" << setw(4) << passedMeatCost 
		 << setw(3) << "/kg" << right << setw(21) << passedMeatCost * passedMeatWeight << endl;
	fout << left << setw(20) << "Dairy Products" << right << setw(24) << passedDairyCost << endl;
	fout << left << setw(20) << "Miscellaneous" << right << setw(24) << passedMiscCost << endl << endl;
	fout << right << setw(44) << (passedMeatCost*passedMeatWeight) + passedDairyCost + passedMiscCost << endl << endl;
	fout << right << setw(18) << "THANK YOU!" << endl << endl;
	fout << "---------------------------------------------" << endl;
	system("type receipt.txt");
}

/*
Enter B for beef, C for chicken or F for fish:
b
Enter the weight of the meat:
4
Getting dairy cost
Please enter the cost:
12
Getting miscellaneous cost
Please enter the cost:
17
---------------------------------------------
ABC Grocery Store

Items bought:

Meat Beef    @ $8.80/kg                35.20
Dairy Products                         12.00
Miscellaneous                          17.00

									   64.20

		THANK YOU!

---------------------------------------------
Press enter to handle next customer or ctrl Z to close cash.
*/
