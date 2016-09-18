#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Simplifier{
  public:
    void getExpression(ifstream &);
    void analyzeExpression(vector<string>);

  private:
    vector<string> myExpression;
};
