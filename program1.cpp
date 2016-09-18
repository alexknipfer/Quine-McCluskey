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
      groupExpression(myExpression);
      myExpression.clear();
      group0.clear();
      group1.clear();
      group2.clear();
      group3.clear();
      group4.clear();
      group5.clear();
    }
    else{
      myExpression.push_back(expression);
    }

    inputFile >> expression;
  }
}

//******************************************************************************

void Simplifier::groupExpression(vector<string> myExpression){
  int complimentCount = 0;
  for(int x = 0; x < myExpression.size(); x++){
    for(int y = 0; y < myExpression[x].length(); y++){
      if(islower(myExpression[x][y])){
        complimentCount++;
      }
    }
    switch(complimentCount){
      case 0: group0.push_back(myExpression[x]);
        break;
      case 1: group1.push_back(myExpression[x]);
        break;
      case 2: group2.push_back(myExpression[x]);
        break;
      case 3: group3.push_back(myExpression[x]);
        break;
      case 4: group4.push_back(myExpression[x]);
        break;
      case 5: group5.push_back(myExpression[x]);
        break;
    }
    complimentCount = 0;
  }
  for(int x = 0; x < group0.size(); x++){
    cout << group0[x] << " ";
  }
  cout << endl;
  for(int x = 0; x < group1.size(); x++){
    cout << group1[x] << " ";
  }
  cout << endl;
  for(int x = 0; x < group2.size(); x++){
    cout << group2[x] << " ";
  }
  cout << endl;
  for(int x = 0; x < group3.size(); x++){
    cout << group3[x] << " ";
  }
  cout << endl;
  for(int x = 0; x < group4.size(); x++){
    cout << group4[x] << " ";
  }
  cout << endl;
  for(int x = 0; x < group5.size(); x++){
    cout << group5[x] << " ";
  }
}

//******************************************************************************
