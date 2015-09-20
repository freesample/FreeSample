#ifndef MCMC_LOGGER_H_
#define MCMC_LOGGER_H_

#include <memory>
#include <vector>
#include <fstream>

// Forward decls.
namespace mcmc {
class Sample;
}


namespace mcmc {

class Logger {
  public:
  bool LogInit(const std::string& file_name);
  void Log(const std::vector<double>& data) const;

  private:
  std::unique_ptr<std::ofstream> log_file_;
};

}  // namespace mcmc

#endif  // MCMC_LOGGER_H_
