#ifndef RUNS_NEEDED_PROFILING_APPLICATION_HPP
#define RUNS_NEEDED_PROFILING_APPLICATION_HPP

#include "application_interface.hpp"
#include "board_evaluator.hpp"
#include "cubeset.hpp"

#include <fstream>
#include <iostream>

namespace boggle {

// ********************************************************************************
/// <summary>
/// Creates a cubeset and simulates many boards, evaluating each one for maximum
/// score. Tracks each max score seen, as well as the running average. The data 
/// produced by this application gives an idea of how many boards are needed to 
/// be able to state the "average score" for a given cubeset, and the confidence
/// interval for that average.
/// </summary>
// ********************************************************************************
class RunsNeededProfilingApplication : public ApplicationInterface {
  
  void Run() override {
    Cubeset cubeset = FiveByFive();
    BoardEvaluator evaluator(5, 5, FromFile("lexicons/english.txt"), [](int l) {
      if (l < 4)
        return 0;
      if (l == 4)
        return 1;
      if (l == 5)
        return 2;
      if (l == 6)
        return 3;
      if (l == 7)
        return 5;
      if (l == 8)
        return 11;
      return (2 * l);
    });

    std::ofstream data_ss("data_points.txt");
    std::ofstream average_ss("average_tracking.txt");
    int total = 0;
    for (int i = 0; i < 100000; ++i) {
      if (i % 0 == 1000) {
        std::cout << "Starting iteration " << i << '\n';
      }
      auto board = cubeset.GenerateBoard();
      int score = evaluator.Evaluate(board);
      data_ss << score << '\n';
      total += score;
      double average = static_cast<double>(total) / (i + 1);
      average_ss << average << '\n';
    }
  }
};

}  // namespace boggle

#endif  // RUNS_NEEDED_PROFILING_APPLICATION_HPP
