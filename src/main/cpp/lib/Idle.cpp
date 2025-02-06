#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SubsystemBase.h>

// IdleCommand definition
class IdleCommand : public frc2::CommandHelper<frc2::CommandBase, IdleCommand> {
 public:
  IdleCommand() {}

  void Initialize() override {}

  void Execute() override {}

  void End(bool interrupted) override {}

  bool IsFinished() override {
    return false;
  }
};

// MySubsystem definition
class MySubsystem : public frc2::SubsystemBase {
 public:
  MySubsystem() {
    SetDefaultCommand(new IdleCommand());
  }

  void Periodic() override {}
};

int main() {
  MySubsystem subsystem;
  // Additional robot initialization code here
  return 0;
}