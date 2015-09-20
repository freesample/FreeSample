#include <vector>
#include <iostream>
#include "FreeSample/histogram.h"

using namespace std;

int main() {
  vector<double> data {1.0, 1.5, 2.9, 4.0, 4.3, 5.0, 5.1, 6.0};
  mcmc::Histogram histogram(3.0, 5.5, 4);

  for (double x : data) {
    histogram.Accumulate(x);
  }

  cout << histogram.ToString() << endl;

  return 0;
}
