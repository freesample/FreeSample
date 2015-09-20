#include <iostream>

#include "FreeSample/logger.h"
#include "FreeSample/framework.h"

namespace mcmc {

using namespace std;

bool Logger::LogInit(const string& file_name) {
  log_file_.reset(new ofstream);
  log_file_->open(file_name);
  return log_file_->is_open();
}

void Logger::Log(const vector<double>& data) const {
  if (log_file_) {
    std::copy(data.begin(), data.end(), std::ostream_iterator<double>(*log_file_, " "));
    *log_file_ << endl;
  } else {
    cerr << "Error in MetroSampler::Log: Did you forget to call MetroSampler::LogInit()?" << endl;
    exit(1);
  }
}

}  // namespace mcmc
