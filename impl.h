#ifndef MCMC_IMPL_H_
#define MCMC_IMPL_H_

#include <random>

#include "FreeSample/framework.h"
#include "FreeSample/logger.h"

namespace mcmc {

double Gaussian(double x, double half_inv_sigma2);

class GaussianDensity : public Density {
public:
  GaussianDensity(double mean, double sigma2);
  double operator()(const Sample &sample) override;

private:
  double mean_;
  double half_inv_sigma2_;
};

class GaussianDistribution : public Distribution {
public:
  GaussianDistribution(double sigma2);

  void Draw(const Sample &here, Sample *sample) override;
  double Likelihood(const Sample &here, const Sample &there) override;

private:
  double half_inv_sigma2_;
  std::normal_distribution<double> distribution_;
  std::default_random_engine generator_;
};

class TableConditionalDistribution : public ConditionalDistribution {
public:
  void Draw(const Sample &here, Sample *sample) override;
  double Likelihood(const Sample &here, const Sample &there) override;

private:
};



} // namespace mcmc

#endif // MCMC_IMPL_H_
