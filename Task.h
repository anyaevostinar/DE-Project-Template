#ifndef TASK_H
#define TASK_H

//#include <_types/_uint32_t.h>
#include <cmath>
#include <string>
#include <iostream>

/**
 * The interface for a task that organisms can complete.
 */
class Task {
public:
  /**
   * Given the output value the organism produced, and the last four inputs it
   * received, this function returns the points the organism should get for
   * completing this task (or 0 if the task was not completed.)
   */
  virtual double CheckOutput(uint32_t output, uint32_t inputs[4]) = 0;

  /** Returns the human-readable name of the task. */
  virtual std::string name() const = 0;
};

#endif
