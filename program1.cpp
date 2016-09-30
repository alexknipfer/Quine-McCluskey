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

Simplifier::Simplifier(){
  expressionSize = 0;
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
      groupExpression(myExpression);    //go group by compliments
      minimizeExpression();
      myExpression.clear();
      group0.clear();
      group1.clear();
      group2.clear();
      group3.clear();
      group4.clear();
      group5.clear();
      inputFile >> expression;
    }
    else{
      myExpression.push_back(expression);
      expressionSize = expression.size();
      inputFile >> expression;
    }
  }
}

//******************************************************************************

void Simplifier::groupExpression(vector<string> myExpression){
    //Receives - my expression vector
    //Task - group expressions by compliments
    //Returns - nothing

  int complimentCount = 0;

    //loop through expression to see how many compliments
  for(int x = 0; x < myExpression.size(); x++){
    for(int y = 0; y < myExpression[x].length(); y++){
      if(islower(myExpression[x][y])){
        complimentCount++;
      }
    }

      //add expression to correct vector based on how many compliments in the
      //expression
    switch(complimentCount){
      case 0: group0.push_back(myExpression[x]);
              group0Check.push_back("X");
        break;
      case 1: group1.push_back(myExpression[x]);
              group1Check.push_back("X");
        break;
      case 2: group2.push_back(myExpression[x]);
              group2Check.push_back("X");
        break;
      case 3: group3.push_back(myExpression[x]);
              group3Check.push_back("X");
        break;
      case 4: group4.push_back(myExpression[x]);
              group4Check.push_back("X");
        break;
      case 5: group5.push_back(myExpression[x]);
              group5Check.push_back("X");
        break;
    }
      //reset compliment count
    complimentCount = 0;
  }
}

//******************************************************************************

void Simplifier::minimizeExpression(){
  int foundPairs = 0;
  char tempVariable;
  char tempVariable2;
  string tempExpression;

    //see if expressions exists in group0 and group1
  if(group0.size() != 0 && group1.size() != 0){

      //go through expressions with 0 compliments
    for(int x = 0; x < group0.size(); x++){

        //go through expressions with 1 compliment
      for(int y = 0; y < group1.size(); y++){

          //make sure the expression hasn't already been completed
        if(group1Check[y] != "done"){

            //go through expression to compare variables
          for(int x1 = 0; x1 < group0[x].length(); x1++){

              //if variables in expression are not equal, then it's possible
              //it can be minimalized, store possible variables in tempVariable
              //just in case they can be minimalized
            if(group0[x][x1] != group1[y][x1]){
              tempVariable = group0[x][x1];
              tempVariable2 = group1[y][x1];
              foundPairs++;
            }
          } //end x1 loop

            //expressions differ in one variable therefore can be minimalized
          if(foundPairs == 1){

              //go through and replace with '_' to know variable has been removed
            for(int replace = 0; replace < group0[x].length(); replace++){
              if(group0[x][replace] == tempVariable || group0[x][replace] == tempVariable2){
                tempExpression += '_';
              }
                //create a temporary expression with variable gone for adding
                //to vector with new expression
              else{
                tempExpression += group0[x][replace];
              }
            }
            group0Check[x] = "done";  //expression is complete
            group1Check[y] = "done";  //expression is complete
            group0New.push_back(tempExpression);  //add new expression to vector

              //reset expression and found pairs
            tempExpression = "";
            foundPairs = 0;
          }

            //reset found pairs even if the expressions couldn't be minimalized
          else{
            foundPairs = 0;
          }

        } //end group1 IF STATEMENT

      } //end y loop
      for(int z = 0; z < group0New.size(); z++){
        cout << group0New[z] << endl;
      }
      cout << endl;
    } //end x loop

  } //end if statement

  if(group1.size() != 0 && group2.size() != 0){
    for(int x = 0; x < group1.size(); x++){

      for(int y = 0; y < group2.size(); y++){

        if(group2Check[y] != "done"){

            //go through expression to compare variables
          for(int x1 = 0; x1 < group1[x].length(); x1++){

              //if variables in expression are not equal, then it's possible
              //it can be minimalized, store possible variables in tempVariable
              //just in case they can be minimalized
            if(group1[x][x1] != group2[y][x1]){
              tempVariable = group1[x][x1];
              tempVariable2 = group2[y][x1];
              foundPairs++;
            }
          } //end x1 loop

            //expressions differ in one variable therefore can be minimalized
          if(foundPairs == 1){

              //go through and replace with '_' to know variable has been removed
            for(int replace = 0; replace < group1[x].length(); replace++){
              if(group1[x][replace] == tempVariable || group1[x][replace] == tempVariable2){
                tempExpression += '_';
              }

                //create a temporary expression with variable gone for adding
                //to vector with new expression
              else{
                tempExpression += group1[x][replace];
              }
            }
            group1Check[x] = "done";  //expression is complete
            group2Check[y] = "done";  //expression is complete
            group1New.push_back(tempExpression);  //expression is complete

              //reset expression and pairs found
            tempExpression = "";
            foundPairs = 0;
          }

            //reset found pairs even if the expressions couldn't be minimalized
          else{
            foundPairs = 0;
          }
        } //end group1 IF STATEMENT
      } //end y loop

    } //end x loop


    for(int z = 0; z < group1New.size(); z++){
      cout << group1New[z] << endl;
    }

  }



  /*for(int x = 0; x < group0.size(); x++){
    cout << group0[x] << " " << group0Check[x];
  }
  cout << endl;
  for(int x = 0; x < group1.size(); x++){
    cout << group1[x] << " " << group1Check[x];
  }
  cout << endl;
  for(int x = 0; x < group2.size(); x++){
    cout << group2[x] << " " << group2Check[x];
  }
  cout << endl;
  for(int x = 0; x < group3.size(); x++){
    cout << group3[x] << " " << group3Check[x];
  }
  cout << endl;
  for(int x = 0; x < group4.size(); x++){
    cout << group4[x] << " " << group4Check[x];
  }
  cout << endl;
  for(int x = 0; x < group5.size(); x++){
    cout << group5[x] << " " << group5Check[x];
  }*/

}

//******************************************************************************
