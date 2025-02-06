#ifndef FAULTSTABLE_H
#define FAULTSTABLE_H

#include <networktables/NetworkTableInstance.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <networktables/StringArrayTopic.h>

using namespace std;

enum class FaultType
{
    INFO,
    WARNING,
    ERROR
};

class Fault
{
public:
    Fault(const std::string &description, FaultType type)
    {
        string toString();
        string info();
        const FaultType getType();
        const string getDescription();
    }

private:
    string description;
    FaultType type;
};

class FaultsTable
{
public:
    FaultsTable(std::shared_ptr<nt::NetworkTable> base, const std::string &name);
    void set(unordered_set<Fault> faults);
    // void clear();

private:
    nt::StringArrayPublisher errors;
    nt::StringArrayPublisher warnings;
    nt::StringArrayPublisher infos;
};

#endif // FAULTSTABLE_H