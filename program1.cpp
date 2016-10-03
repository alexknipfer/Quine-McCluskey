#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
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
  int totalPairs = 0;
  int doneCount = 0;
  char tempVariable;
  char tempVariable2;
  string tempExpression;
  bool doneSorting = false;

  while(doneSorting == false){
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
                totalPairs++;
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
                doneCount++;
                group0New.push_back(tempExpression);  //add new expression to vector
                group0NewCheck.push_back("X");

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
                totalPairs++;

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
                doneCount++;
                group1New.push_back(tempExpression);  //expression is complete
                group1NewCheck.push_back("X");

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

      }

      if(group2.size() != 0 && group3.size() != 0){
        for(int x = 0; x < group2.size(); x++){

          for(int y = 0; y < group3.size(); y++){

            if(group3Check[y] != "done"){

                //go through expression to compare variables
              for(int x1 = 0; x1 < group2[x].length(); x1++){

                  //if variables in expression are not equal, then it's possible
                  //it can be minimalized, store possible variables in tempVariable
                  //just in case they can be minimalized
                if(group2[x][x1] != group3[y][x1]){
                  tempVariable = group2[x][x1];
                  tempVariable2 = group3[y][x1];
                  foundPairs++;
                }
              } //end x1 loop

                //expressions differ in one variable therefore can be minimalized
              if(foundPairs == 1){
                totalPairs++;

                  //go through and replace with '_' to know variable has been removed
                for(int replace = 0; replace < group2[x].length(); replace++){
                  if(group2[x][replace] == tempVariable || group2[x][replace] == tempVariable2){
                    tempExpression += '_';
                  }

                    //create a temporary expression with variable gone for adding
                    //to vector with new expression
                  else{
                    tempExpression += group2[x][replace];
                  }
                }
                group2Check[x] = "done";  //expression is complete
                group3Check[y] = "done";  //expression is complete
                doneCount++;
                group2New.push_back(tempExpression);  //expression is complete
                group2NewCheck.push_back("X");

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

      }

      if(doneCount == 0){
        doneSorting = true;
      }
      else{
        doneCount = 0;
      }
      /*for(int x = 0; x < group0.size(); x++){
        cout << group0[x] << " " << group0Check[x] << endl;
      }*/
      /*
      for(int x = 0; x < group1.size(); x++){
        cout << group1[x] << " " << group1Check[x] << endl;
      }
      for(int x = 0; x < group2.size(); x++){
        cout << group2[x] << " " << group2Check[x] << endl;
      }
      for(int x = 0; x < group3.size(); x++){
        cout << group3[x] << " " << group3Check[x] << endl;
      }
      for(int x = 0; x < group4.size(); x++){
        cout << group4[x] << " " << group4Check[x] << endl;
      }
      for(int x = 0; x < group5.size(); x++){
        cout << group5[x] << " " << group5Check[x] << endl;
      }
      cout << endl;*/
      for(int x = 0; x < group0Check.size(); x++){
        if(group0Check[x] != "done"){
          finalExpressions.push_back(group0[x]);
        }
      }
      for(int x = 0; x < group1Check.size(); x++){
        if(group1Check[x] != "done"){
          finalExpressions.push_back(group1[x]);
        }
      }
      for(int x = 0; x < group2Check.size(); x++){
        if(group2Check[x] != "done"){
          finalExpressions.push_back(group2[x]);
        }
      }
      for(int x = 0; x < group3Check.size(); x++){
        if(group3Check[x] != "done"){
          finalExpressions.push_back(group3[x]);
        }
      }
      for(int x = 0; x < group4Check.size(); x++){
        if(group4Check[x] != "done"){
          finalExpressions.push_back(group4[x]);
        }
      }
      for(int x = 0; x < group5Check.size(); x++){
        if(group5Check[x] != "done"){
          finalExpressions.push_back(group5[x]);
        }
      }

      group0.clear();
      group1.clear();
      group2.clear();
      group3.clear();
      group4.clear();
      group5.clear();
      group0Check.clear();
      group1Check.clear();
      group2Check.clear();
      group3Check.clear();
      group4Check.clear();
      group5Check.clear();

        //see if expressions exists in group0 and group1
      if(group0New.size() != 0 && group1New.size() != 0){

          //go through expressions with 0 compliments
        for(int x = 0; x < group0New.size(); x++){

            //go through expressions with 1 compliment
          for(int y = 0; y < group1New.size(); y++){

              //make sure the expression hasn't already been completed
            if(group1NewCheck[y] != "done"){

                //go through expression to compare variables
              for(int x1 = 0; x1 < group0New[x].length(); x1++){

                  //if variables in expression are not equal, then it's possible
                  //it can be minimalized, store possible variables in tempVariable
                  //just in case they can be minimalized
                if(group0New[x][x1] != group1New[y][x1]){
                  tempVariable = group0New[x][x1];
                  tempVariable2 = group1New[y][x1];
                  foundPairs++;
                }
              } //end x1 loop

                //expressions differ in one variable therefore can be minimalized
              if(foundPairs == 1){
                totalPairs++;
                  //go through and replace with '_' to know variable has been removed
                for(int replace = 0; replace < group0New[x].length(); replace++){
                  if(group0New[x][replace] == tempVariable || group0New[x][replace] == tempVariable2){
                    tempExpression += '_';
                  }
                    //create a temporary expression with variable gone for adding
                    //to vector with new expression
                  else{
                    tempExpression += group0New[x][replace];
                  }
                }
                group0NewCheck[x] = "done";  //expression is complete
                group1NewCheck[y] = "done";  //expression is complete
                doneCount++;
                group0.push_back(tempExpression);  //add new expression to vector
                group0Check.push_back("X");

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

        } //end x loop

      } //end if statement

        //see if expressions exists in group0 and group1
      if(group1New.size() != 0 && group2New.size() != 0){

          //go through expressions with 0 compliments
        for(int x = 0; x < group1New.size(); x++){

            //go through expressions with 1 compliment
          for(int y = 0; y < group2New.size(); y++){

              //make sure the expression hasn't already been completed
            if(group2NewCheck[y] != "done"){

                //go through expression to compare variables
              for(int x1 = 0; x1 < group1New[x].length(); x1++){

                  //if variables in expression are not equal, then it's possible
                  //it can be minimalized, store possible variables in tempVariable
                  //just in case they can be minimalized
                if(group1New[x][x1] != group2New[y][x1]){
                  tempVariable = group1New[x][x1];
                  tempVariable2 = group2New[y][x1];
                  foundPairs++;
                }
              } //end x1 loop

                //expressions differ in one variable therefore can be minimalized
              if(foundPairs == 1){
                totalPairs++;
                  //go through and replace with '_' to know variable has been removed
                for(int replace = 0; replace < group1New[x].length(); replace++){
                  if(group1New[x][replace] == tempVariable || group1New[x][replace] == tempVariable2){
                    tempExpression += '_';
                  }
                    //create a temporary expression with variable gone for adding
                    //to vector with new expression
                  else{
                    tempExpression += group1New[x][replace];
                  }
                }
                group1NewCheck[x] = "done";  //expression is complete
                group2NewCheck[y] = "done";  //expression is complete
                doneCount++;
                group1.push_back(tempExpression);  //add new expression to vector
                group1Check.push_back("X");

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

        } //end x loop

      } //end if statement

        //see if expressions exists in group0 and group1
      if(group2New.size() != 0 && group3New.size() != 0){

          //go through expressions with 0 compliments
        for(int x = 0; x < group2New.size(); x++){

            //go through expressions with 1 compliment
          for(int y = 0; y < group3New.size(); y++){

              //make sure the expression hasn't already been completed
            if(group3NewCheck[y] != "done"){

                //go through expression to compare variables
              for(int x1 = 0; x1 < group2New[x].length(); x1++){

                  //if variables in expression are not equal, then it's possible
                  //it can be minimalized, store possible variables in tempVariable
                  //just in case they can be minimalized
                if(group2New[x][x1] != group3New[y][x1]){
                  tempVariable = group2New[x][x1];
                  tempVariable2 = group3New[y][x1];
                  foundPairs++;
                }
              } //end x1 loop

                //expressions differ in one variable therefore can be minimalized
              if(foundPairs == 1){
                totalPairs++;
                  //go through and replace with '_' to know variable has been removed
                for(int replace = 0; replace < group2New[x].length(); replace++){
                  if(group2New[x][replace] == tempVariable || group2New[x][replace] == tempVariable2){
                    tempExpression += '_';
                  }
                    //create a temporary expression with variable gone for adding
                    //to vector with new expression
                  else{
                    tempExpression += group2New[x][replace];
                  }
                }
                group2NewCheck[x] = "done";  //expression is complete
                group3NewCheck[y] = "done";  //expression is complete
                doneCount++;
                group2.push_back(tempExpression);  //add new expression to vector
                group2Check.push_back("X");

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

        } //end x loop

      } //end if statement

      if(doneCount == 0){
        doneSorting = true;
      }
      else{
        doneCount = 0;
      }

      for(int x = 0; x < group0NewCheck.size(); x++){
        if(group0NewCheck[x] != "done"){
          finalExpressions.push_back(group0New[x]);
        }
      }
      for(int x = 0; x < group1NewCheck.size(); x++){
        if(group1NewCheck[x] != "done"){
          finalExpressions.push_back(group1New[x]);
        }
      }
      for(int x = 0; x < group2NewCheck.size(); x++){
        if(group2NewCheck[x] != "done"){
          finalExpressions.push_back(group2New[x]);
        }
      }
      for(int x = 0; x < group3NewCheck.size(); x++){
        if(group3NewCheck[x] != "done"){
          finalExpressions.push_back(group3New[x]);
        }
      }
      for(int x = 0; x < group4NewCheck.size(); x++){
        if(group4NewCheck[x] != "done"){
          finalExpressions.push_back(group4New[x]);
        }
      }
      for(int x = 0; x < group5NewCheck.size(); x++){
        if(group5NewCheck[x] != "done"){
          finalExpressions.push_back(group5New[x]);
        }
      }

      group0New.clear();
      group1New.clear();
      group2New.clear();
      group3New.clear();
      group4New.clear();
      group5New.clear();
      group0NewCheck.clear();
      group1NewCheck.clear();
      group2NewCheck.clear();
      group3NewCheck.clear();
      group4NewCheck.clear();
      group5NewCheck.clear();
  }

  for(int x = 0; x < finalExpressions.size(); x++){
    cout << finalExpressions[x] << endl;
  }

  /*for(int z = 0; z < group0New.size(); z++){
    cout << group0New[z] << " " << group0NewCheck[z] << endl;
  }
  cout << endl;

  for(int z = 0; z < group1New.size(); z++){
    cout << group1New[z] << " " << group1NewCheck[z] << endl;
  }
  cout << endl;

  for(int z = 0; z < group2New.size(); z++){
    cout << group2New[z] << " " << group2NewCheck[z] << endl;
  }

  for(int z = 0; z < group0.size(); z++){
    cout << group0[z] << group0Check[z] << endl;
  }
  cout << endl;


  */

}

//******************************************************************************
