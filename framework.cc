#include <cstdlib>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "FreeSample/framework.h"

namespace mcmc {

using namespace std;

MetroSampler::MetroSampler(Distribution* proposal, Density* target)
    : proposal_(proposal), target_(target) {}

void MetroSampler::Next(int iteration, const Sample &here, Sample *there) const {
  Gen(here, there);
  if (!Accept(iteration, here, *there)) {
    *there = here;
  }
  //Log({float(iteration), (*there)[0]});
}

void MetroSampler::Gen(const Sample &here, Sample* there) const {
  proposal_->Draw(here, there);
}

bool MetroSampler::Accept(int iteration, const Sample &here, const Sample &there) const {
  //double accept_odds = (*target_)(there)*proposal_->Likelihood(there, here);
  //double reject_odds = (*target_)(here)*proposal_->Likelihood(here, there);
  double density_ratio = (*target_)(there)/(*target_)(here);
  double likelihood_ratio = proposal_->Likelihood(there, here)/proposal_->Likelihood(here, there);
  double prob = density_ratio * likelihood_ratio;
  if (prob >= 1.0) {
    return true;
  }
  return (float(rand()) / RAND_MAX) < prob;
}

void GibbsSampler::Next(int iteration, const Sample &here, Sample *there) const {
  int var_idx;
  do {
    var_idx = rand() % here.GetNumDims();
  } while (evidence_indices_[var_idx]);
  cpds_[var_idx]->Draw(here, there);
}

void ConditionalDistribution::Draw(const Sample &here, Sample *sample) {
}

void Simulate(const Sample& start, const Sampler &sampler, int num_iterations, Worker *worker) {
  Sample here(start);
  (*worker)(here);

  Sample there(start);
  for (int i = 0; i < num_iterations; ++i) {
    sampler.Next(i, here, &there);
    (*worker)(there);
    here.Swap(&there);
  }
}

void Sample::Swap(Sample* other) {
  dims_.swap(other->dims_);
}

string Sample::ToString() const {
  std::ostringstream oss;
  if (dims_.empty()) return "";

  std::copy(dims_.begin(), dims_.end(), std::ostream_iterator<double>(oss, " "));
  return oss.str();
}

Sample& Sample::operator-=(const Sample& other) {
  for (int i = 0; i < dims_.size(); ++i) {
    dims_[i] -= other.dims_[i];
  }
  return *this;
} 

const vector<double>& Sample::GetVector() const {
  return dims_;
}

// static
Sample Sample::Zeros(int ndims) {
  return FromVector(std::vector<double>(0.0, ndims));
}

// static
Sample Sample::FromVector(const std::vector<double>& vec) {
  return Sample(vec);
}

} // namespace mcmc
