//******************  PROGRAM IDENTIFICATION  **********************************
//*                                                                            *
//*  PROGRAM FILE NAME: program1.cpp  ASSIGNMENT #:  1    GRADE: _____         *
//*   	                                                                       *
//*  PROGRAM AUTHOR:   ____________________________________                    *
//*                             Alex Knipfer                                   *
//*                                                                            *
//*  COURSE #:   CSC 40300 21             DUE DATE: October 17, 2016           *
//*                                                                            *
//******************************************************************************


//********************* PROGRAM DESCRIPTION ************************************
//*    Process: This program uses the Quine-McKluskey method to minimalize any *
//*             read in boolean expression.                                    *
//*                                                                            *
//*    USER DEFINED                                                            *
//*     MODULES:       : printHeader - print program header                    *
//*                      printFooter - print program footer                    *
//*                      getExpression - reads in current expression from file *
//*                      groupExpression - groups expression                   *
//*                      minimizeExpression - simplifies expression using the  *
//*                                           Quine-McKluskey algorithm        *
//*                      createMatrix - adds X vector values to the y axis of  *
//*                                     matrix                                 *
//*                      printExpressions - prints the final expressions from  *
//*                                         vector                             *
//******************************************************************************

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

    //variables for input file and output file
  ifstream inputFile("data1.txt");
  ofstream outputFile("output.txt");

    //print header
  mySimplifier.printHeader(outputFile);

    //get the expression from input file
  mySimplifier.getExpression(inputFile, outputFile);

    //print footer
  mySimplifier.printFooter(outputFile);
}

//******************************************************************************

Simplifier::Simplifier(){
  //Receives - nothing
  //Task - Constructor - initialize matrix and expressions counts
  //Returns - nothing

    //initialize counts
  expressionSize = 0;
  numOfExpressions = 0;

    //intialize matrix for final expressions
  for(int x = 0; x < 15; x++){
    for(int y = 0; y < 15; y++){
      matrix[x][y] = 'y';
    }
  }
}

//******************************************************************************

void Simplifier::getExpression(ifstream &inputFile, ofstream &outputFile){
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
      minimizeExpression();             //minimalize current expression
      createMatrix();                   //generate y axis for matrix
      printExpressions(outputFile);     //print the expressions

        //clear expression vectors and groups for next expression
      myExpression.clear();
      finalExpressions.clear();
      group0.clear();
      group1.clear();
      group2.clear();
      group3.clear();
      group4.clear();
      group5.clear();
      inputFile >> expression;
      numOfExpressions = 0;
    }
      //keep reading in expressions since "S" is not reached
    else{
        //add expression to vector
      myExpression.push_back(expression);
      numOfExpressions++;
        //get size of vector for amount of expressions
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
  //Receives - nothing
  //Task - minimalize current read in expression and add to finalExpressions
  //Returns - nothing

      //intialize all counts to 0
  int foundPairs = 0;
  int totalPairs = 0;
  int doneCount = 0;

    //holds values of characters in expression while iterating
  char tempVariable;
  char tempVariable2;
  string tempExpression;

    //initialize to false until complete sorting
  bool doneSorting = false;

      //continue sorting until done
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
                matrix[x][y] = 'X';
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

        //see if expressions exist in group 1 and 2
      if(group1.size() != 0 && group2.size() != 0){
        for(int x = 0; x < group1.size(); x++){

            //compare each group
          for(int y = 0; y < group2.size(); y++){

                //make sure the expression is group isn't already complete
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
                matrix[x][y] = 'X';
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

        //see if expressions exist in groups 2 and 3
      if(group2.size() != 0 && group3.size() != 0){
        for(int x = 0; x < group2.size(); x++){

            //go through and compare groups
          for(int y = 0; y < group3.size(); y++){

              //make sure expression in group isn't complete
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
                matrix[x][y] = 'X';
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

          //see if expressions exist in groups 3 and 4
      if(group3.size() != 0 && group4.size() != 0){
        for(int x = 0; x < group3.size(); x++){

            //go through and compare groups
          for(int y = 0; y < group4.size(); y++){

              //make sure group isn't complete
            if(group4Check[y] != "done"){

                //go through expression to compare variables
              for(int x1 = 0; x1 < group3[x].length(); x1++){

                  //if variables in expression are not equal, then it's possible
                  //it can be minimalized, store possible variables in tempVariable
                  //just in case they can be minimalized
                if(group3[x][x1] != group4[y][x1]){
                  tempVariable = group3[x][x1];
                  tempVariable2 = group4[y][x1];
                  foundPairs++;
                }
              } //end x1 loop

                //expressions differ in one variable therefore can be minimalized
              if(foundPairs == 1){
                totalPairs++;

                  //go through and replace with '_' to know variable has been removed
                for(int replace = 0; replace < group3[x].length(); replace++){
                  if(group3[x][replace] == tempVariable || group3[x][replace] == tempVariable2){
                    tempExpression += '_';
                  }

                    //create a temporary expression with variable gone for adding
                    //to vector with new expression
                  else{
                    tempExpression += group3[x][replace];
                  }
                }
                group3Check[x] = "done";  //expression is complete
                group4Check[y] = "done";  //expression is complete
                doneCount++;
                matrix[x][y] = 'X';
                group3New.push_back(tempExpression);  //expression is complete
                group3NewCheck.push_back("X");

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

          //see if expressions exist in groups 4 and 5
      if(group4.size() != 0 && group5.size() != 0){
        for(int x = 0; x < group4.size(); x++){

            //go through groups and compare
          for(int y = 0; y < group5.size(); y++){

              //make sure expression isn't complete
            if(group5Check[y] != "done"){

                //go through expression to compare variables
              for(int x1 = 0; x1 < group4[x].length(); x1++){

                  //if variables in expression are not equal, then it's possible
                  //it can be minimalized, store possible variables in tempVariable
                  //just in case they can be minimalized
                if(group4[x][x1] != group5[y][x1]){
                  tempVariable = group4[x][x1];
                  tempVariable2 = group5[y][x1];
                  foundPairs++;
                }
              } //end x1 loop

                //expressions differ in one variable therefore can be minimalized
              if(foundPairs == 1){
                totalPairs++;

                  //go through and replace with '_' to know variable has been removed
                for(int replace = 0; replace < group4[x].length(); replace++){
                  if(group4[x][replace] == tempVariable || group4[x][replace] == tempVariable2){
                    tempExpression += '_';
                  }

                    //create a temporary expression with variable gone for adding
                    //to vector with new expression
                  else{
                    tempExpression += group4[x][replace];
                  }
                }
                group4Check[x] = "done";  //expression is complete
                group5Check[y] = "done";  //expression is complete
                doneCount++;
                matrix[x][y] = 'X';
                group4New.push_back(tempExpression);  //expression is complete
                group4NewCheck.push_back("X");

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

        //if no expressions were possible to minimize, then break out of then
        //break out of the loop, it's finished
      if(doneCount == 0){
        doneSorting = true;
      }

        //reset the count and continue to next groups
      else{
        doneCount = 0;
      }

        //loop through all groups and push the expressions
        //into the final expression for printing later
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

        //clear all the vectors to reuse them for the next cycle of
        //minimalizing
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
                matrix[x][y] = 'X';
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
                matrix[x][y] = 'X';
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
                matrix[x][y] = 'X';
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

      //see if expressions exists in group0 and group1
    if(group3New.size() != 0 && group4New.size() != 0){

        //go through expressions with 0 compliments
      for(int x = 0; x < group3New.size(); x++){

          //go through expressions with 1 compliment
        for(int y = 0; y < group4New.size(); y++){

            //make sure the expression hasn't already been completed
          if(group4NewCheck[y] != "done"){

              //go through expression to compare variables
            for(int x1 = 0; x1 < group3New[x].length(); x1++){

                //if variables in expression are not equal, then it's possible
                //it can be minimalized, store possible variables in tempVariable
                //just in case they can be minimalized
              if(group3New[x][x1] != group4New[y][x1]){
                tempVariable = group3New[x][x1];
                tempVariable2 = group4New[y][x1];
                foundPairs++;
              }
            } //end x1 loop

              //expressions differ in one variable therefore can be minimalized
            if(foundPairs == 1){
              totalPairs++;
                //go through and replace with '_' to know variable has been removed
              for(int replace = 0; replace < group3New[x].length(); replace++){
                if(group3New[x][replace] == tempVariable || group3New[x][replace] == tempVariable2){
                  tempExpression += '_';
                }
                  //create a temporary expression with variable gone for adding
                  //to vector with new expression
                else{
                  tempExpression += group3New[x][replace];
                }
              }
              group3NewCheck[x] = "done";  //expression is complete
              group4NewCheck[y] = "done";  //expression is complete
              doneCount++;
              matrix[x][y] = 'X';
              group3.push_back(tempExpression);  //add new expression to vector
              group3Check.push_back("X");

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
  if(group4New.size() != 0 && group5New.size() != 0){

      //go through expressions with 0 compliments
    for(int x = 0; x < group4New.size(); x++){

        //go through expressions with 1 compliment
      for(int y = 0; y < group5New.size(); y++){

          //make sure the expression hasn't already been completed
        if(group5NewCheck[y] != "done"){

            //go through expression to compare variables
          for(int x1 = 0; x1 < group4New[x].length(); x1++){

              //if variables in expression are not equal, then it's possible
              //it can be minimalized, store possible variables in tempVariable
              //just in case they can be minimalized
            if(group4New[x][x1] != group5New[y][x1]){
              tempVariable = group4New[x][x1];
              tempVariable2 = group5New[y][x1];
              foundPairs++;
            }
          } //end x1 loop

            //expressions differ in one variable therefore can be minimalized
          if(foundPairs == 1){
            totalPairs++;
              //go through and replace with '_' to know variable has been removed
            for(int replace = 0; replace < group4New[x].length(); replace++){
              if(group4New[x][replace] == tempVariable || group4New[x][replace] == tempVariable2){
                tempExpression += '_';
              }
                //create a temporary expression with variable gone for adding
                //to vector with new expression
              else{
                tempExpression += group4New[x][replace];
              }
            }
            group4NewCheck[x] = "done";  //expression is complete
            group5NewCheck[y] = "done";  //expression is complete
            doneCount++;
            matrix[x][y] = 'X';
            group4.push_back(tempExpression);  //add new expression to vector
            group4Check.push_back("X");

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

        //if no expressions were possible to minimize, then break out of then
        //break out of the loop, it's finished
      if(doneCount == 0){
        doneSorting = true;
      }

        //reset the count and continue to next groups
      else{
        doneCount = 0;
      }

        //loop through all groups and push the expressions
        //into the final expression for printing later
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

        //clear all the vectors to reuse them for the next cycle of
        //minimalizing
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
}

//******************************************************************************
void Simplifier::createMatrix(){
    //Receives - nothing
    //Task - go through current matrix of expressions and add to the
    //         final expressions for printing
    //Returns - nothing

  for(int x = 0; x < numOfExpressions; x++){
      //keeps track of y axis (original expressions that they were a part of)
    matrixY.push_back(x);
  }

}
//******************************************************************************
void Simplifier::printExpressions(ofstream &outputFile){
  //Receives - nothing
  //Task - print the original and minimalized expressions
  //Returns - nothing

    //print header note for expression
  outputFile << "The Original Boolean Expression is:" << endl;

    //go through original expressions to print
  for(int x = 0; x < myExpression.size(); x++){
    outputFile << "(";
    outputFile << myExpression[x];
      //print the + if it's not the end
    if(x != myExpression.size() - 1){
      outputFile << ") + ";
    }
    else{
      outputFile << ")";
    }
  }
  outputFile << endl;
  outputFile << endl;

    //go through final expressions to print
  outputFile << "The Minimized Boolean Expression is:" << endl;
  for(int x = 0; x < finalExpressions.size(); x++){
    outputFile << "(";
    outputFile << finalExpressions[x];
      //print the + if it's not the end
    if(x != finalExpressions.size() - 1){
      outputFile << ") + ";
    }
    else{
      outputFile << ")";
    }
  }

    //separate all the expressions
  outputFile << endl;
  outputFile << endl;
  outputFile << "**************************************************************" << endl;
  outputFile << endl;
}
//******************************************************************************


void Simplifier::printHeader(ofstream &Outfile)
{
		//Receives - the output file
		//Task- Prints the output preamble
		//Returns - Nothing
	Outfile << setw(30) << "Alex Knipfer ";
	Outfile << setw(17) << "CSC 40300";
	Outfile << setw(15) << "Section 21" << endl;
	Outfile << setw(30) << "Fall 2016";
	Outfile << setw(20) << "Assignment #1" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------\n\n";
	return;
}

//****************************************************************************//

void Simplifier::printFooter(ofstream &Outfile)
{
    //Receives - the output file
    //Task - Prints the output footer
    //Returns - nothing
	Outfile << endl;
	Outfile << setw(35) << "--------------------------------" << endl;
	Outfile << setw(35) << "|    END OF PROGRAM OUTPUT     |" << endl;
	Outfile << setw(35) << "--------------------------------" << endl;

	return;
}

//*********************** END OF PROGRAM *************************************//
