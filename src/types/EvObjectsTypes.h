#ifndef EVOBJECTSTYPES_H
#define EVOBJECTSTYPES_H

namespace Ev {

enum ObjectType {
    UnknownType,// for search
// Ev.Core
    Object,Link,Property,
    ApplicationDocumentation,Documentation,

// Ev.Variation
    GlobalProcess,
    Process,
    Library,
    DeviceFamily,
    Mismatch,
    MismatchItem,
    Corner,
    Parameter,
    Filter,


// Ev.Verification
    Requirement,
// Ev.Circuit
    Cell,
    Schematic,
    State,
    SimulationCommands,
// Ev.Simulation
    Simulation,
    Scenario,

// Ev.Session

    Session,
    Project,

// Ev.Simulation
    SimulationManager,
    SimulationPlan





};

}



#endif // EVOBJECTSTYPES_H
