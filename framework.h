#ifndef MCMC_FRAMEWORK_H_
#define MCMC_FRAMEWORK_H_

#include <vector>
#include <memory>

#include "mcmc/logger.h"

namespace mcmc {

class Sample {
public:
  double operator[](const int i) const { return dims_[i]; }
  double &operator[](const int i) { return dims_[i]; }
  int GetNumDims() const { return dims_.size(); }
  void Swap(Sample* other);
  std::string ToString() const;
  const std::vector<double>& GetVector() const;
  Sample& operator-=(const Sample& other);

  static Sample Zeros(int ndims);
  static Sample FromVector(const std::vector<double>& vec);

private:
  Sample(const std::vector<double> &dims) : dims_(dims) {}
  std::vector<double> dims_;
};

class Distribution {
public:
  virtual void Draw(const Sample &here, Sample *sample) = 0;
  virtual double Likelihood(const Sample &here, const Sample &there) = 0;
};

class ConditionalDistribution : public Distribution {
public:
  virtual void Draw(const Sample &here, Sample *sample) = 0;
  virtual double Likelihood(const Sample &here, const Sample &there) = 0;
};

class Density {
public:
  virtual double operator()(const Sample &sample) = 0;
};

class Sampler {
public:
  virtual void Next(int iteration, const Sample &here, Sample *there) const = 0;
};

class MetroSampler : public Sampler, public Logger {
public:
  MetroSampler(Distribution *proposal, Density *target);
  void Next(int iteration, const Sample &here, Sample *there) const override;

private:
  void Gen(const Sample &here, Sample *there) const;
  bool Accept(int iteration, const Sample &here, const Sample &there) const;

private:
  std::unique_ptr<Distribution> proposal_;
  std::unique_ptr<Density> target_;
};

class GibbsSampler : public Sampler {
public:
  GibbsSampler(const std::vector<int>& observable_indices,
               const std::vector<int>& hidden_indices);
  void Next(int iteration, const Sample &here, Sample *there) const override;

private:
  std::vector<int> observable_indices_;
  std::vector<int> hidden_indices_;
  std::vector<int> evidence_indices_;;
  std::vector<std::unique_ptr<ConditionalDistribution>> cpds_;
};

class Worker {
public:
  virtual void operator()(const Sample &sample) = 0;
};

void Simulate(const Sample& start, const Sampler &sampler, int num_iterations, Worker *worker);

} // namespace mcmc

#endif // MCMC_FRAMEWORK_H_
