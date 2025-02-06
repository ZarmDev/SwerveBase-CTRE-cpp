// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

// (from 1155) and https://github.com/Team334/SwerveBase-CTRE

#include "FaultsTable.h"
#include <networktables/NetworkTableInstance.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <networktables/StringArrayTopic.h>

using namespace std;

/** An individual fault, containing necessary information. */
class Fault
{
public:
  // Fault expects a description, type and it automatically sets the description and type to what was passed in
  Fault(const std::string &description, FaultType type)
      : description(description), type(type) {}

  const bool equals(Fault other)
  {
    return description == other.description && type == other.type;
  }

  string toString()
  {
    // TODO Maybe don't use a switch statement and just make FaultType a map?
    string tToString;
    switch (type)
    {
    case FaultType::WARNING:
      tToString = "Warning";
      break;
    case FaultType::ERROR:
      tToString = "Error";
      break;
    case FaultType::INFO:
      tToString = "Info";
      break;
    }
    return tToString;
  }

  string info()
  {
    // TODO Maybe don't use a switch statement and just make FaultType a map?
    string tToString = toString();
    return "Fault - " + description + ", Type - " + tToString;
  }

  // This means you can not modify the return value nor the instance that is
  // called on it
  const FaultType getType() const { return type; }

  const string getDescription() const { return description; }

private:
  string description;
  FaultType type;
};

/** A table on Network Tables that contains non-persistent faults. */
class FaultsTable
{
private:
  //  These allow you to push errors, warning, info, etc to your dashboard
  nt::StringArrayPublisher errors;
  nt::StringArrayPublisher warnings;
  nt::StringArrayPublisher infos;
  // Returns an array of descriptions of all faults that match the specified
  // type.
  vector<string> filteredStrings(unordered_set<Fault> faults, FaultType type)
  {
    std::vector<std::string> descriptions;

    // Use std::for_each to filter and transform in one pass
    for_each(faults.begin(), faults.end(), [&](const Fault &fault)
             {
      if (fault.getType() == type) {
        descriptions.push_back(fault.getDescription());
      } });

    return descriptions;
    // return faults.stream()
    //     .filter(a->a.type() == type)
    //     .map(Fault::description)
    //     .toArray(String[] ::new);
  }

public:
  FaultsTable(nt::NetworkTable &base, std::string &name)
  {
    nt::NetworkTableInstance inst = nt::NetworkTableInstance::GetDefault();
    std::shared_ptr<nt::NetworkTable> table = inst.GetTable(name);

    nt::StringArrayPublisher strPub =
        inst.GetStringArrayTopic(".type").Publish();
    // Thanks AI
    std::string alertStr = "Alert";
    std::span<const std::string> alertSpan(&alertStr, 1);
    strPub.Set(alertSpan);

    inst.GetStringArrayTopic("errors").Publish();
    inst.GetStringArrayTopic("warnings").Publish();
    inst.GetStringArrayTopic("infos").Publish();
  }

  void set(unordered_set<Fault> faults)
  {
    errors.Set(filteredStrings(faults, FaultType::ERROR));
    warnings.Set(filteredStrings(faults, FaultType::WARNING));
    infos.Set(filteredStrings(faults, FaultType::INFO));
  }

  // TODO: Does this work? Lol
  // void clear() {
  //   vector<string> empty;
  //   errors.Set(empty);
  //   warnings.Set(empty);
  //   infos.Set(empty);
  // }
};