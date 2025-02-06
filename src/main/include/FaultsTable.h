#ifndef FAULTSTABLE_H
#define FAULTSTABLE_H

#include <string>
#include <memory>
#include <unordered_set>

/**
 * The type of fault, used for detecting whether the fallible is in a failure
 * state and displaying to NetworkTables.
 */
enum class FaultType { INFO, WARNING, ERROR };

class Fault {
 public:
 Fault(const std::string& description, FaultType type)
  string toString();
  string info();
  const FaultType getType() const { return type; }
  const string getDescription() const { return description; }

 private:
  string description;
  FaultType type;
};

class FaultsTable {
 public:
  FaultsTable(std::shared_ptr<nt::NetworkTable> base, const std::string& name);
  void set(unordered_set<Fault> faults);
  // void clear();

 private:
  nt::StringArrayPublisher errors;
  nt::StringArrayPublisher warnings;
  nt::StringArrayPublisher infos;
};

#endif  // FAULTSTABLE_H