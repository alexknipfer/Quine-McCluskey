#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Simplifier{
  public:
    Simplifier();
    void getExpression(ifstream &);
    void groupExpression(vector<string>);
    void minimizeExpression();

  private:
    int expressionSize;
    vector<string> myExpression;
    vector<string> group0;
    vector<string> group0New;
    vector<string> group1;
    vector<string> group1New;
    vector<string> group2;
    vector<string> group2New;
    vector<string> group3;
    vector<string> group3New;
    vector<string> group4;
    vector<string> group4New;
    vector<string> group5;
    vector<string> group5New;
    vector<string> group0Check;
    vector<string> group1Check;
    vector<string> group2Check;
    vector<string> group3Check;
    vector<string> group4Check;
    vector<string> group5Check;
    vector<string> group0NewCheck;
    vector<string> group1NewCheck;
    vector<string> group2NewCheck;
    vector<string> group3NewCheck;
    vector<string> group4NewCheck;
    vector<string> group5NewCheck;
    vector<string> finalExpressions;
};
