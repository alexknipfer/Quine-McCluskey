#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Simplifier{
  public:
    void getExpression(ifstream &);
    void groupExpression(vector<string>);

  private:
    vector<string> myExpression;
    vector<string> group0;
    vector<string> group1;
    vector<string> group2;
    vector<string> group3;
    vector<string> group4;
    vector<string> group5;
};
