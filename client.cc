#include <vector>
#include <iostream>

#include "FreeSample/mcmc.h"
#include "FreeSample/histogram.h"

using namespace std;

class HistogramWorker : public mcmc::Worker {
public:
  HistogramWorker(double range_start, double range_end, int num_bins)
      : histogram_(range_start, range_end, num_bins) {}

  void operator()(const mcmc::Sample &sample) override {
    double x = sample[0];
    histogram_.Accumulate(x);
  }

  void Print() const {
    cout << histogram_.ToString() << endl;
  }

  void LogInit(const string& log_file_name) {
    histogram_.LogInit(log_file_name);
  }

  void Flush() {
    histogram_.Flush();
  }

  private:
  mcmc::LoggingHistogram histogram_;
};

void TestMetropolis();
void TestGibbs();

int main(int argc, char **argv) {
  //TestMetropolis();
  TestGibbs();
  return 0;
}

void TestMetropolis() {
  std::unique_ptr<mcmc::GaussianDistribution> proposal(new mcmc::GaussianDistribution(16.0));
  std::unique_ptr<mcmc::GaussianDensity> target(new mcmc::GaussianDensity(50.0, 9.0));

  mcmc::MetroSampler sampler(proposal.release(), target.release());
  sampler.LogInit("/tmp/metro_sampler_log.txt");

  const double histo_start = 40.0;
  const double histo_end = 60.0;
  const int num_bins = 20;
  HistogramWorker worker(histo_start, histo_end, num_bins);
  worker.LogInit("/tmp/histogram_worker_log.txt");

  const int num_iterations = 10000;
  mcmc::Simulate(mcmc::Sample::FromVector({20.0}), sampler, num_iterations, &worker);
  worker.Print();
  //worker.Flush();
}

void TestGibbs() {
  const int num_dims = 5;
  mcmc::GibbsSampler sampler;

  const double histo_start = 40.0;
  const double histo_end = 60.0;
  const int num_bins = 20;
  HistogramWorker worker(histo_start, histo_end, num_bins);
  worker.LogInit("/tmp/histogram_worker_log.txt");

  const int num_iterations = 10000;
  mcmc::Simulate(mcmc::Sample::Zeros(num_dims), sampler, num_iterations, &worker);
  worker.Print();
  //worker.Flush();
}
