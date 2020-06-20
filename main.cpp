#include "application_interface.hpp"
#include "runs_needed_profiling_application.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[]) {
  std::string const options_text = "Valid options:\n"
    "  runs_needed - Rolls and evaluates a large number of boards and outputs the scores (shortcut: rn)\n";
  if (argc != 2) {
    std::cout << "Please specify exactly one argument.\n" << options_text;
    return 1;
  }

  std::unique_ptr<boggle::ApplicationInterface> app;
  if (strcmp("rn", argv[1]) == 0 || strcmp("runs_needed", argv[1]) == 0) {
    app = std::make_unique<boggle::RunsNeededProfilingApplication>();
  } else {
    std::cout << "Invalid application.\n" << options_text;
    return 1;
  }

  auto start_time = std::chrono::steady_clock::now();
  std::cout << "Beginning application " << argv[1] << '\n';

  app->Run();

  auto end_time = std::chrono::steady_clock::now();
  auto duration_in_ms
      = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "Application complete!";
  std::cout << "Time elapsed: " << static_cast<double>(duration_in_ms.count()) / 1000.0
            << " seconds.\n";
  return 0;
}
