#ifndef TUNERCONSTANTS_H
#define TUNERCONSTANTS_H

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/Pigeon2.hpp>
#include <ctre/phoenix6/swerve/SwerveModuleConstants.hpp>
#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Pose2d.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "ctre/phoenix6/swerve/SwerveDrivetrain.hpp"

using namespace ctre::phoenix6;

namespace TunerConstants
{
    static const swerve::SwerveDrivetrainConstants DrivetrainConstants = swerve::SwerveDrivetrainConstants{}
                                                                             .WithCANBusName(kCANBusName)
                                                                             .WithPigeon2Id(kPigeonId)
                                                                             .WithPigeon2Configs(pigeonConfigs);

    static const swerve::SwerveModuleConstantsFactory ConstantCreator =
        swerve::SwerveModuleConstantsFactory<configs::TalonFXConfiguration, configs::TalonFXConfiguration, configs::CANcoderConfiguration>{}
            .WithDriveMotorGearRatio(kDriveGearRatio)
            .WithSteerMotorGearRatio(kSteerGearRatio)
            .WithCouplingGearRatio(kCoupleRatio)
            .WithWheelRadius(kWheelRadius)
            .WithSteerMotorGains(steerGains)
            .WithDriveMotorGains(driveGains)
            .WithSteerMotorClosedLoopOutput(kSteerClosedLoopOutput)
            .WithDriveMotorClosedLoopOutput(kDriveClosedLoopOutput)
            .WithSlipCurrent(kSlipCurrent)
            .WithSpeedAt12Volts(kSpeedAt12Volts)
            .WithDriveMotorType(kDriveMotorType)
            .WithSteerMotorType(kSteerMotorType)
            .WithFeedbackSource(kSteerFeedbackType)
            .WithDriveMotorInitialConfigs(driveInitialConfigs)
            .WithSteerMotorInitialConfigs(steerInitialConfigs)
            .WithEncoderInitialConfigs(encoderInitialConfigs)
            .WithSteerInertia(kSteerInertia)
            .WithDriveInertia(kDriveInertia)
            .WithSteerFrictionVoltage(kSteerFrictionVoltage)
            .WithDriveFrictionVoltage(kDriveFrictionVoltage);
    // Both sets of gains need to be tuned to your individual robot.
    static constexpr double kSteerKP = 100;
    static constexpr double kSteerKI = 0;
    static constexpr double kSteerKD = 0.5;
    static constexpr double kSteerKS = 0.1;
    static constexpr double kSteerKV = 1.91;
    static constexpr double kSteerKA = 0;

    static constexpr double kDriveKP = 0.1;
    static constexpr double kDriveKI = 0;
    static constexpr double kDriveKD = 0;
    static constexpr double kDriveKS = 0;
    static constexpr double kDriveKV = 0.124;

    static constexpr swerve::ClosedLoopOutputType kSteerClosedLoopOutput = swerve::ClosedLoopOutputType::Voltage;
    static constexpr swerve::ClosedLoopOutputType kDriveClosedLoopOutput = swerve::ClosedLoopOutputType::Voltage;

    static constexpr swerve::DriveMotorArrangement kDriveMotorType = swerve::DriveMotorArrangement::TalonFX_Integrated;
    static constexpr swerve::SteerMotorArrangement kSteerMotorType = swerve::SteerMotorArrangement::TalonFX_Integrated;

    static constexpr swerve::SteerFeedbackType kSteerFeedbackType = swerve::SteerFeedbackType::FusedCANcoder;

    static constexpr units::ampere_t kSlipCurrent = 120_A;

    configs::TalonFXConfiguration driveInitialConfigs;
    configs::TalonFXConfiguration steerInitialConfigs;
    configs::CANcoderConfiguration encoderInitialConfigs;
    configs::Pigeon2Configuration pigeonConfigs;

    CANBus kCANBus{"canivore", "./logs/example.hoot"};

    static constexpr units::meters_per_second_t kSpeedAt12Volts = 4.69_mps;

    static constexpr double kCoupleRatio = 3.8181818181818183;
    static constexpr double kDriveGearRatio = 7.363636363636365;
    static constexpr double kSteerGearRatio = 15.42857142857143;
    static constexpr units::inch_t kWheelRadius = 2.167_in;

    static constexpr bool kInvertLeftSide = false;
    static constexpr bool kInvertRightSide = true;

    static constexpr int kPigeonId = 1;

    static constexpr units::kilogram_square_meter_t kSteerInertia = 0.01_kg_sq_m;
    static constexpr units::kilogram_square_meter_t kDriveInertia = 0.01_kg_sq_m;
    static constexpr units::volt_t kSteerFrictionVoltage = 0.2_V;
    static constexpr units::volt_t kDriveFrictionVoltage = 0.2_V;

    static const swerve::SwerveDrivetrainConstants DrivetrainConstants = swerve::SwerveDrivetrainConstants{}
                                                                             .WithCANBusName(kCANBusName)
                                                                             .WithPigeon2Id(kPigeonId)
                                                                             .WithPigeon2Configs(pigeonConfigs);
    // swerve::SwerveModuleConstantsFactory<
    //     configs::TalonFXConfiguration, configs::TalonFXConfiguration, configs::CANcoderConfiguration>
    //     ConstantCreator{

    static const swerve::SwerveModuleConstantsFactory<configs::TalonFXConfiguration, configs::TalonFXConfiguration, configs::CANcoderConfiguration> ConstantCreator =
        swerve::SwerveModuleConstantsFactory<configs::TalonFXConfiguration, configs::TalonFXConfiguration, configs::CANcoderConfiguration>{}
            .WithDriveMotorGearRatio(kDriveGearRatio)
            .WithSteerMotorGearRatio(kSteerGearRatio)
            .WithCouplingGearRatio(kCoupleRatio)
            .WithWheelRadius(kWheelRadius)
            .WithSteerMotorGains(steerGains)
            .WithDriveMotorGains(driveGains)
            .WithSteerMotorClosedLoopOutput(kSteerClosedLoopOutput)
            .WithDriveMotorClosedLoopOutput(kDriveClosedLoopOutput)
            .WithSlipCurrent(kSlipCurrent)
            .WithSpeedAt12Volts(kSpeedAt12Volts)
            .WithDriveMotorType(kDriveMotorType)
            .WithSteerMotorType(kSteerMotorType)
            .WithFeedbackSource(kSteerFeedbackType)
            .WithDriveMotorInitialConfigs(driveInitialConfigs)
            .WithSteerMotorInitialConfigs(steerInitialConfigs)
            .WithEncoderInitialConfigs(encoderInitialConfigs)
            .WithSteerInertia(kSteerInertia)
            .WithDriveInertia(kDriveInertia)
            .WithSteerFrictionVoltage(kSteerFrictionVoltage)
            .WithDriveFrictionVoltage(kDriveFrictionVoltage);

    // Front Left
    static constexpr int kFrontLeftDriveMotorId = 3;
    static constexpr int kFrontLeftSteerMotorId = 2;
    static constexpr int kFrontLeftEncoderId = 1;
    static constexpr units::radian_t kFrontLeftEncoderOffset = 0.15234375_rad;
    static constexpr bool kFrontLeftSteerMotorInverted = true;
    static constexpr bool kFrontLeftEncoderInverted = false;

    static constexpr units::inch_t kFrontLeftXPos = 10_in;
    static constexpr units::inch_t kFrontLeftYPos = 10_in;

    // Front Right
    static constexpr int kFrontRightDriveMotorId = 1;
    static constexpr int kFrontRightSteerMotorId = 0;
    static constexpr int kFrontRightEncoderId = 0;
    static constexpr units::radian_t kFrontRightEncoderOffset = -0.4873046875_rad;
    static constexpr bool kFrontRightSteerMotorInverted = true;
    static constexpr bool kFrontRightEncoderInverted = false;

    static constexpr units::inch_t kFrontRightXPos = 10_in;
    static constexpr units::inch_t kFrontRightYPos = -10_in;

    // Back Left
    static constexpr int kBackLeftDriveMotorId = 7;
    static constexpr int kBackLeftSteerMotorId = 6;
    static constexpr int kBackLeftEncoderId = 3;
    static constexpr units::radian_t kBackLeftEncoderOffset = -0.219482421875_rad;
    static constexpr bool kBackLeftSteerMotorInverted = true;
    static constexpr bool kBackLeftEncoderInverted = false;

    static constexpr units::inch_t kBackLeftXPos = -10_in;
    static constexpr units::inch_t kBackLeftYPos = 10_in;

    // Back Right
    static constexpr int kBackRightDriveMotorId = 5;
    static constexpr int kBackRightSteerMotorId = 4;
    static constexpr int kBackRightEncoderId = 2;
    static constexpr units::radian_t kBackRightEncoderOffset = 0.17236328125_rad;
    static constexpr bool kBackRightSteerMotorInverted = true;
    static constexpr bool kBackRightEncoderInverted = false;

    static constexpr units::inch_t kBackRightXPos = -10_in;
    static constexpr units::inch_t kBackRightYPos = -10_in;

    static const swerve::SwerveModuleConstants FrontLeft = ConstantCreator.CreateModuleConstants(
        kFrontLeftSteerMotorId, kFrontLeftDriveMotorId, kFrontLeftEncoderId, kFrontLeftEncoderOffset,
        kFrontLeftXPos, kFrontLeftYPos, kInvertLeftSide, kFrontLeftSteerMotorInverted, kFrontLeftEncoderInverted);

    static const swerve::SwerveModuleConstants FrontRight = ConstantCreator.CreateModuleConstants(
        kFrontRightSteerMotorId, kFrontRightDriveMotorId, kFrontRightEncoderId, kFrontRightEncoderOffset,
        kFrontRightXPos, kFrontRightYPos, kInvertRightSide, kFrontRightSteerMotorInverted, kFrontRightEncoderInverted);

    static const swerve::SwerveModuleConstants BackLeft = ConstantCreator.CreateModuleConstants(
        kBackLeftSteerMotorId, kBackLeftDriveMotorId, kBackLeftEncoderId, kBackLeftEncoderOffset,
        kBackLeftXPos, kBackLeftYPos, kInvertLeftSide, kBackLeftSteerMotorInverted, kBackLeftEncoderInverted);

    static const swerve::SwerveModuleConstants BackRight = ConstantCreator.CreateModuleConstants(
        kBackRightSteerMotorId, kBackRightDriveMotorId, kBackRightEncoderId, kBackRightEncoderOffset,
        kBackRightXPos, kBackRightYPos, kInvertRightSide, kBackRightSteerMotorInverted, kBackRightEncoderInverted);

    /**
     * Creates a CommandSwerveDrivetrain instance. This should only be called once in your robot
     * program,.
     */
    static Swerve createDrivetrain()
    {
        return new Swerve(DrivetrainConstants, FrontLeft, FrontRight, BackLeft, BackRight);
    }

    /** Swerve Drive class utilizing CTR Electronics' Phoenix 6 API with the selected device types. */
    static class TunerSwerveDrivetrain : SwerveDrivetrain<TalonFX, TalonFX, CANcoder>
    {
        /**
         * Constructs a CTRE SwerveDrivetrain using the specified constants.
         *
         * <p>This constructs the underlying hardware devices, so users should not construct the devices
         * themselves. If they need the devices, they can access them through getters in the classes.
         *
         * @param drivetrainConstants Drivetrain-wide constants for the swerve drive
         * @param modules Constants for each specific module
         */
    public TunerSwerveDrivetrain(
        SwerveDrivetrainConstants drivetrainConstants, SwerveModuleConstants<?, ?, ?>... modules)
        {
            super(TalonFX::new, TalonFX::new, CANcoder::new, drivetrainConstants, modules);
        }

        /**
         * Constructs a CTRE SwerveDrivetrain using the specified constants.
         *
         * <p>This constructs the underlying hardware devices, so users should not construct the devices
         * themselves. If they need the devices, they can access them through getters in the classes.
         *
         * @param drivetrainConstants Drivetrain-wide constants for the swerve drive
         * @param odometryUpdateFrequency The frequency to run the odometry loop. If unspecified or set
         *     to 0 Hz, this is 250 Hz on CAN FD, and 100 Hz on CAN 2.0.
         * @param modules Constants for each specific module
         */
    public TunerSwerveDrivetrain(
        SwerveDrivetrainConstants drivetrainConstants,
        double odometryUpdateFrequency,
        SwerveModuleConstants<?, ?, ?>... modules)
        {
            super(
                TalonFX::new,
                TalonFX::new,
                CANcoder::new,
                drivetrainConstants,
                odometryUpdateFrequency,
                modules);
        }

        /**
         * Constructs a CTRE SwerveDrivetrain using the specified constants.
         *
         * <p>This constructs the underlying hardware devices, so users should not construct the devices
         * themselves. If they need the devices, they can access them through getters in the classes.
         *
         * @param drivetrainConstants Drivetrain-wide constants for the swerve drive
         * @param odometryUpdateFrequency The frequency to run the odometry loop. If unspecified or set
         *     to 0 Hz, this is 250 Hz on CAN FD, and 100 Hz on CAN 2.0.
         * @param odometryStandardDeviation The standard deviation for odometry calculation in the form
         *     [x, y, theta]ᵀ, with units in meters and radians
         * @param visionStandardDeviation The standard deviation for vision calculation in the form [x,
         *     y, theta]ᵀ, with units in meters and radians
         * @param modules Constants for each specific module
         */
    public TunerSwerveDrivetrain(
        SwerveDrivetrainConstants drivetrainConstants,
        double odometryUpdateFrequency,
        Matrix<N3, N1> odometryStandardDeviation,
        Matrix<N3, N1> visionStandardDeviation,
        SwerveModuleConstants<?, ?, ?>... modules)
        {
            super(
                TalonFX::new,
                TalonFX::new,
                CANcoder::new,
                drivetrainConstants,
                odometryUpdateFrequency,
                odometryStandardDeviation,
                visionStandardDeviation,
                modules);
        }
    }
}

#endif // TUNERCONSTANTS_H