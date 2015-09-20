#include <cstdlib>
#include <cmath>
#include <random>
#include <memory>

#include "FreeSample/impl.h"

namespace mcmc {

double Gaussian(double x, double half_inv_sigma2) {
  return exp(-x * x * half_inv_sigma2);
}

GaussianDensity::GaussianDensity(double mean, double sigma2)
    : mean_(mean), half_inv_sigma2_(0.5 / sigma2) {}

double GaussianDensity::operator()(const Sample &sample) {
  double rho = Gaussian(mean_ - sample[0], half_inv_sigma2_);
  return rho;
}

GaussianDistribution::GaussianDistribution(double sigma2)
    : half_inv_sigma2_(0.5 / sigma2), distribution_(0.0, sigma2), generator_() {}

void GaussianDistribution::Draw(const Sample &here, Sample *sample) {
  double x = distribution_(generator_);
  (*sample)[0] = x + here[0];
}

double GaussianDistribution::Likelihood(const Sample &here,
                                       const Sample &there) {
  Sample diff(here);
  diff -= there;
  double likelihood = Gaussian(diff[0], half_inv_sigma2_);
  return likelihood;
}

}  // namespace mcmc
