#ifndef PRINTSTATS
#define PRINTSTATS

#include "Timeline.hpp"
#include "writeToFile.hpp"
#include <algorithm>
#include <iostream>

void printStats(Timeline stats)
{
  std::string content;
  float activityTime = 0;

  int index = 0;

  for (auto i : stats.state)
  {

    std::sort(i.begin(), i.end(), [](Process a, Process b) {
      return a.processID < b.processID;
    });

    content += std::to_string(index);
    content += " ";
    for (auto process : i)
    {
      content += std::to_string(process.processID) + ": " + process.state + " ";
      if (process.state == "running")
        activityTime++;
    }
    content += "\n";
    index++;
  }

  content += "\nFinishing Time: " + std::to_string(stats.state.size() - 1) + "\n";
  content += "CPU utilization: " + std::to_string((activityTime / stats.state.size())) + "\n";

  std::sort(stats.processes.begin(), stats.processes.end(), [](Process a, Process b) {
    return a.processID < b.processID;
  });

  for (auto i : stats.processes)
  {
    content += "Turnaround time of process " + std::to_string(i.processID) + ": ";
    content += std::to_string(i.turnaroundTime) + "\n";
  }

  writeToFile("outputFCFS.txt", content);
}

#endif