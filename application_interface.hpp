#ifndef APPLICATION_INTERFACE_HPP
#define APPLICATION_INTERFACE_HPP

namespace boggle {

// ********************************************************************************
/// <summary>
/// Applications are objects that can be run, with the intention that flags
/// provided to the main executable select an application to be run. In this
/// project, little effort will be devoted to making applications configurable
/// at runtime. Instead, the intended use case is to make modifications to the
/// concrete application class and recompile.
/// </summary>
// ********************************************************************************
class ApplicationInterface {
 public:
  virtual ~ApplicationInterface() = default;
  virtual void Run() = 0;
};

}  // namespace boggle

#endif  // APPLICATION_INTERFACE_HPP