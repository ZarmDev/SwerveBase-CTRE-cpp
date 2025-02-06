// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


// import static edu.wpi.first.wpilibj2.command.Commands.*;

// import edu.wpi.first.wpilibj2.command.Command;
#include <stdexcept>
#include <frc2/command/Command.h>

class Autos final {
  private:
   Autos() {
    throw new std::invalid_argument("This is a utility class!");
  }

  /** An auto that doesn't do anything for 15 sec. */
  public:
    // frc2::Command none() {
    //     return
    // }
}