// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/MathUtil.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc/Joystick.h>
#include <networktables/NetworkTableInstance.h>
#include <iostream>

#include "Drivetrain.h"
#include "Constants.cpp"
#include "TunerConstants.h"

// Robot extends TimedRobot
class Robot : public frc::TimedRobot
{
public:
  void RobotPeriodic() override
  {
    // auto nt_instance = nt::NetworkTableInstance::GetDefault();
    // auto joystick_table = nt_instance.GetTable("JoystickData");
    // joystick_table->PutNumber("X", joystick.GetX());
    // joystick_table->PutNumber("Y", joystick.GetY());
    // joystick_table->PutNumber("Z", joystick.GetZ());
    // joystick_table->PutNumber("Throttle", joystick.GetThrottle());
  }

  void AutonomousPeriodic() override
  {
    DriveWithJoystick(false);
    m_swerve.UpdateOdometry();
  }

  void TeleopPeriodic() override { DriveWithJoystick(true); }

private:
  frc::XboxController _driverController{Constants::Ports::driverController};
  const Swerve _swerve TunerConstants::createDrivetrain();

  // Slew rate limiters to make joystick inputs more gentle; 1/3 sec from 0
  // to 1.
  frc::SlewRateLimiter<units::scalar> m_xspeedLimiter{3 / 1_s};
  frc::SlewRateLimiter<units::scalar> m_yspeedLimiter{3 / 1_s};
  frc::SlewRateLimiter<units::scalar> m_rotLimiter{3 / 1_s};

  void DriveWithJoystick(bool fieldRelative)
  {
    // Get the x speed. We are inverting this because Xbox controllers return
    // negative values when we push forward.
    const auto xSpeed = -m_xspeedLimiter.Calculate(
                            frc::ApplyDeadband(m_controller.GetLeftY(), 0.02)) *
                        Drivetrain::kMaxSpeed;

    // Get the y speed or sideways/strafe speed. We are inverting this because
    // we want a positive value when we pull to the left. Xbox controllers
    // return positive values when you pull to the right by default.
    const auto ySpeed = -m_yspeedLimiter.Calculate(
                            frc::ApplyDeadband(m_controller.GetLeftX(), 0.02)) *
                        Drivetrain::kMaxSpeed;

    // Get the rate of angular rotation. We are inverting this because we want a
    // positive value when we pull to the left (remember, CCW is positive in
    // mathematics). Xbox controllers return positive values when you pull to
    // the right by default.
    const auto rot = -m_rotLimiter.Calculate(
                         frc::ApplyDeadband(m_controller.GetRightX(), 0.02)) *
                     Drivetrain::kMaxAngularSpeed;

    m_swerve.Drive(xSpeed, ySpeed, rot, fieldRelative, GetPeriod());
  }
};

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
