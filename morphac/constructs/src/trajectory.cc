#include "constructs/include/trajectory.h"

namespace morphac {
namespace constructs {

using std::vector;

using Eigen::MatrixXd;

using morphac::constructs::State;

Trajectory::Trajectory(const State& initial_state)
    : dim_(initial_state.get_size()), data_(initial_state.get_data()) {}

Trajectory::Trajectory(const MatrixXd& data) : dim_(data.cols()), data_(data) {
  MORPH_REQUIRE(data.rows() > 0 && data.cols() > 0, std::invalid_argument,
                "Trajectory data must not have zero rows or columns.");
}

}  // namespace constructs
}  // namespace morphac
