#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "Simplifier.h"

using namespace std;

int main(){
  Simplifier mySimplifier;

  ifstream inputFile("data1.txt");

  mySimplifier.getExpression(inputFile);
}

//******************************************************************************

void Simplifier::getExpression(ifstream &inputFile){
    //Receives - input file
    //Task - read input from data file
    //Returns - nothing

  string expression;

    //read in parts of expression from input file
  inputFile >> expression;

    //continue reading in data until sentinel is reached
  while(expression != "S"){

      //expression is complete once x is read in
    if(expression == "X"){
      analyzeExpression(myExpression);
    }

      //add parts of expression to vector
    myExpression.push_back(expression);
    inputFile >> expression;
  }
}

//******************************************************************************

void Simplifier::analyzeExpression(vector<string> myExpression){
  for(int x = 0; x < myExpression.size(); x++){
    cout << myExpression[x] << endl;
  }
}

//******************************************************************************
