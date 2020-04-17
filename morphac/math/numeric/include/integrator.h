#ifndef INTEGRATOR_H
#define INTEGRATOR_H

namespace morphac {
namespace math {
namespace numeric {

class Integrator {
 public:
  Integrator();

  virtual morphac::constructs::State Step(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input, const double dt) = 0;

 private:
  std::function<morphac::constructs::State(const morphac::constructs::State&,
                                           const morphac::constructs::Input&)>
      derivative_function_;
};

}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
