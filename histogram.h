#ifndef MCMC_HISTOGRAM_H_
#define MCMC_HISTOGRAM_H_

#include <vector>
#include <string>

#include "mcmc/logger.h"

namespace mcmc {

class Histogram {
  public:
  Histogram(double range_start, double range_end, int num_bins);
  void Accumulate(double x);
  std::string ToString() const;

  protected:
  double range_start_;
  double range_end_;
  int num_bins_;
  std::vector<int> counts_;
  double units_per_bin_;
};

class LoggingHistogram : public Histogram, public Logger {
  public:
  LoggingHistogram(double range_start, double range_end, int num_bins) :
    Histogram(range_start, range_end, num_bins) {}
  void Flush();
};

}  // namespace mcmc

#endif  // MCMC_HISTOGRAM_H_
