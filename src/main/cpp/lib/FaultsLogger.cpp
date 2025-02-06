// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

// import com.ctre.phoenix6.hardware.CANcoder;
// import com.ctre.phoenix6.hardware.Pigeon2;
// import com.ctre.phoenix6.hardware.TalonFX;
// import dev.doglog.DogLog;
// import edu.wpi.first.networktables.NetworkTableInstance;
// import edu.wpi.first.wpilibj.DriverStation;
// import frc.lib.FaultsTable.Fault;
// import frc.lib.FaultsTable.FaultType;
// import java.util.ArrayList;
// import java.util.HashSet;
// import java.util.List;
// import java.util.Optional;
// import java.util.Set;
// import java.util.function.BooleanSupplier;
// import java.util.function.Supplier;
// import org.photonvision.PhotonCamera;

using namespace std;

#include <unordered_set>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <FaultsTable.h>
#include <iostream>
#include <frc/DriverStation.h>
#include <frc/Errors.h>
#include <optional>

// (from team 1155 but slightly modified)

class FaultReporter {
 public:
  FaultReporter() {}
  void report() {}
};

/**
 * FaultLogger allows for faults and errors to be logged and displayed.
 */
// Final prevents inheritance
class FaultLogger final {
 private:
  //  @FunctionalInterface
  // public static interface FaultReporter {
  //   void report();
  // }
  // TODO: I'm still not sure what FaultReporter is used for...
  bool _enableConsole = true;

  // DATA
  vector<FaultReporter> faultReporters;
  unordered_set<Fault> newFaults;
  unordered_set<Fault> activeFaults;
  unordered_set<Fault> totalFaults;

  // NETWORK TABLES
  FaultsTable activeAlerts;
  FaultsTable totalAlerts;

 public:
  /** Must be called to setup the fault logger. */
  void setup(nt::NetworkTableInstance ntInst) {
    shared_ptr<nt::NetworkTable> inst = ntInst.GetDefault().GetTable("Faults");

    activeAlerts = FaultsTable(inst, "Active Faults");
    totalAlerts = FaultsTable(inst, "Total Faults");
  }

  /** Must be called to setup the fault logger. (getDefault get's the global
   * instance) */
  // void setup() { setup(NetworkTableInstance.getDefault()); }

  /** Whether or not to print new faults into the console. */
  void enableConsole(bool enable) { _enableConsole = enable; }

  /** Polls registered fallibles. This method should be called periodically. */
  void update() {
    activeFaults.clear();

    for (FaultReporter fault : faultReporters) {
      fault.report();
    }
    for (Fault fault : newFaults) {
      activeFaults.insert(fault);
    }
    newFaults.clear();

    // TODO: Replace DogLog with C++ telementary
    // for (const auto& fault : activeFaults) {
    //   DogLog.logFault(fault.toString());
    // }
    // activeFaults.forEach(f->DogLog.logFault(f.toString()));

    totalFaults.insert(activeFaults.begin(), activeFaults.end());
    // totalFaults.addAll(activeFaults);

    // don't log to NT if there is a match going on (just use doglog)
    if (!frc::DriverStation::IsFMSAttached()) {
      activeAlerts.set(activeFaults);
      totalAlerts.set(totalFaults);
    }
  }

  /** Clears total faults. */
  void clear() {
    totalFaults.clear();
    activeFaults.clear();
    newFaults.clear();
  }

  /** Clears fault suppliers. */
  void unregisterAll() { faultReporters.clear(); }

  /**
   * Returns the set of all current faults.
   *
   * @retrurn The set of all curent faults.
   */
  unordered_set<Fault> activeFaults() { return activeFaults; }

  /**
   * Returns the set of all total faults.
   *
   * @return The set of all total faults.
   */
  unordered_set<Fault> totalFaults() { return totalFaults; }

  /**
   * Reports a fault.
   *
   * @param fault The fault to report.
   */
  void report(Fault fault) {
    newFaults.insert(fault);

    if (!_enableConsole)
      return;

    switch (fault.getType()) {
      case FaultType::ERROR:
        cout << ("[Fault Logger] " + fault.info(), false);
        break;
      case FaultType::WARNING:
        // TODO: Seems like no such thing as reportWarning so using cout here
        cout << ("[Fault Logger] " + fault.info(), false);
        break;
      case FaultType::INFO:
        cout << "[Fault Logger] " + fault.info() << std::endl;
        break;
    }
  }

  /**
   * Reports a fault.
   *
   * @param description The description of the fault.
   * @param type The type of the fault.
   */
  void report(const std::string& description, FaultType type) {
    report(Fault(description, type));
  }

  /**
   * Registers a new fault supplier.
   * TODO: May be unneccessary in C++
   */
  // void register(const optional<Fault>& fault = std:nullopt) {
  //   if (fault) {
  //     faultReporters.add(FaultLogger::report);
  //   }
  // }

  /**
   * Registers a new fault supplier.
   *
   * @param condition Whether a failure is occuring.
   * @param description The failure's description.
   */
  // void register(BooleanSupplier condition, String description, FaultType type) {
  //   faultReporters.add(()->{
  //     if (condition.getAsBoolean()) {
  //       report(description, type);
  //     }
  //   });
  // }

  /**
   * Registers a new TalonFX.
   *
   * @param talonFX The TalonFX.
   */
  // TODO: implement
  static void register(TalonFX talonFX) {
    String name = CTREUtil.getName(talonFX);

    register(()->talonFX.getFault_Hardware().getValue(),
             name + "- Hardware Fault.", FaultType.ERROR);
    register(()->talonFX.getFault_BootDuringEnable().getValue(),
             name + "- Boot While Enabling.", FaultType.WARNING);
    register(()->talonFX.getFault_DeviceTemp().getValue(),
             name + "- Device Temperature Too High.", FaultType.WARNING);
    register(()->talonFX.getFault_ProcTemp().getValue(),
             name + "- Processor Temp Too High.", FaultType.WARNING);
    register(()->talonFX.getFault_Undervoltage().getValue(),
             name + "- Voltage Too Low, Check For Brownouts.",
             FaultType.WARNING);
  }

  /**
   * Registers a new CANcoder.
   *
   * @param cancoder The CANcoder.
   */
  // TODO: implement cancoder
  static void register(CANcoder cancoder) {
    String name = CTREUtil.getName(cancoder);

    register(()->cancoder.getFault_Hardware().getValue(),
             name + "- Hardware Fault.", FaultType.ERROR);
    register(()->cancoder.getFault_BadMagnet().getValue(),
             name + "- Bad Magnet Signal.", FaultType.ERROR);
    register(()->cancoder.getFault_BootDuringEnable().getValue(),
             name + "- Boot While Enabling.", FaultType.WARNING);
    register(()->cancoder.getFault_Undervoltage().getValue(),
             name + "- Voltage Too Low, Check For Brownouts.",
             FaultType.WARNING);
  }

  /**
   * Registers a new Pigeon.
   *
   * @param pigeon The Pigeon.
   */
  // TODO: implement pigeon
  static void register(Pigeon2 pigeon) {
    String name = CTREUtil.getName(pigeon);

    register(()->pigeon.getFault_Hardware().getValue(),
             name + "- Hardware Fault.", FaultType.ERROR);
    register(()->pigeon.getFault_BootDuringEnable().getValue(),
             name + "- Boot While Enabling.", FaultType.WARNING);
    register(()->pigeon.getFault_Undervoltage().getValue(),
             name + "- Voltage Too Low, Check For Brownouts.",
             FaultType.WARNING);
  }

  /**
   * Registers a new PhotonCamera (more detailed logs on the web ui).
   *
   * @param photonCamera The PhotonCamera.
   */
  // TODO: implement photoncamera
  static void register(PhotonCamera photonCamera) {
    register(()->!photonCamera.isConnected(),
             photonCamera.getName() + ": Disconnected.", FaultType.ERROR);
  }
}