// ## How to access constants? ##
// #include <Constants.cpp>
// To get any value from constants -> Constants::variablename
// constexpr is used to evalulate at compile time rather than at runtime to improve performance

#include "units/frequency.h"
#include "units/velocity.h"
#include "units/length.h"
#include "units/angular_velocity.h"
#include "units/acceleration.h"
#include <frc/apriltag/AprilTag.h>
#include <frc/apriltag/AprilTagFieldLayout.h>
#include <wpi/SymbolExports.h>
#include <frc/apriltag/AprilTagFields.h>
#include <string>
#include <vector>
#include <cmath>
#include <numbers>

using namespace std;

namespace Constants
{
    constexpr units::hertz_t simUpdateFrequency = 200_Hz;

    namespace Ports
    {
        constexpr int driverController = 0;
    }

    namespace FieldConstants
    {
        // Load the 2025 Reefscape
        const frc::AprilTagFieldLayout fieldLayout = frc::LoadAprilTagLayoutField(frc::AprilTagField::k2025Reefscape);
    }

    namespace VisionConstants
    {
        const string blueArducamName = "blue-arducam";

        const vector<double> singleTagBaseStdDevs = {5.0, 5.0, 5.0};
        const vector<double> multiTagBaseStdDevs = {1.0, 1.0, 1.0};

        constexpr double xBoundMargin = 0.01;
        constexpr double yBoundMargin = 0.01;
        constexpr double zBoundMargin = 0.01;

        // TODO: Implement VisionPoseEstimator
        // constexpr VisionPoseEstimatorConstants blueArducam =
        //     new VisionPoseEstimatorConstants(
        //         blueArducamName,
        //         new Transform3d(new Translation3d(0, 0, 1), new Rotation3d()),
        //         0.2,
        //         0.0001,
        //         3,
        //         7);
    }

    namespace SwerveConstants
    {
        constexpr units::hertz_t odometryFrequency = 250_Hz;
        
        // Calculates the "Euclidean" distance (just the distance formula) from LocationX on the FrontLeft to LocationY on the FrontLeft
        // We use meter_t because it's just for type safety. It allows you to do calculations and get an error if you didn't convert correctly
        const units::meter_t driveRadius = sqrt(
                    pow(TunerConstants::FrontLeft::LocationX, 2) +
                    pow(TunerConstants::FrontLeft::LocationY, 2));

        // constexpr Distance driveRadius =
        //     Meters.of(
        //         Math.sqrt(
        //             Math.pow(
        //                 TunerConstants.FrontLeft.LocationX, 2) + Math.pow(TunerConstants.FrontLeft.LocationY, 2)));
        
        // Multiply by radians per second in order to convert it (otherwise you will get an error)
        const units::meters_per_second_t maxTranslationalSpeed = 3.632 * units::meters_per_second_t(1);
        // Multiply by radians per second in order to convert it (otherwise you will get an error)
        const units::radians_per_second_t maxAngularSpeed = numbers::pi * units::radians_per_second_t(1);

        // respecting wheel COF and max motor torque (this can be obtained from choreo probably)
        constexpr units::meters_per_second_squared_t maxTranslationalAcceleration =
            14.715 * units::meters_per_second_squared_t(1);
        // TODO: Careful here since there is no units::radians_per_second_squared_t
        constexpr double maxAngularAcceleration =
            numbers::pi * 3;

        const units::meters_per_second_t translationalDeadband = maxTranslationalSpeed * (0.1);
        const units::radians_per_second_t rotationalDeadband = maxAngularSpeed * (0.1);
    }
}