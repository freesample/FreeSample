#include <sstream>
#include <iostream>

#include "mcmc/histogram.h"

namespace mcmc {

using namespace std;

Histogram::Histogram(double range_start, double range_end, int num_bins) :
  range_start_(range_start), range_end_(range_end), num_bins_(num_bins),
  counts_(num_bins + 2, 0), units_per_bin_((range_end_ - range_start_)/num_bins) {}

void Histogram::Accumulate(double x) {
  int bin = -1;
  if (x < range_start_) {
    bin = 0;
  } else if (x >= range_end_) {
    bin = num_bins_ + 1;
  } else {
    bin = ((x - range_start_) / units_per_bin_)+1;
  }
  ++counts_[bin];
}

string Histogram::ToString() const {
  ostringstream oss;
  oss << "< " << range_start_ << ": " << counts_[0] << endl;
  for (int i = 1; i <= num_bins_; ++i) {
    oss << "[" << range_start_ + (i - 1) * units_per_bin_ << "," << range_start_ + i * units_per_bin_ << ") : " << counts_[i] << endl;
  }
  oss << ">= " << range_end_ << ": " << counts_[num_bins_ + 1];
  return oss.str();
}

void LoggingHistogram::Flush() {
  double sum = 0.0;
  for (int n : counts_) {
    sum += n;
  }
  for (int i = 0; i < counts_.size(); ++i) {
    Log({double(i), double(counts_[i])/sum});
  }
}

}  // namespace mcmc
