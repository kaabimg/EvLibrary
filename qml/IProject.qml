import Ev.Session 1.0
import Ev.Design 1.0
import Ev.Simulation 1.0


Project {
    objectName: "AmpOP"
    Cell {
        objectName : "PAmpOP_in"

        IProcess{

        }

        Schematic {
            objectName : "testbench1"
            filePath: "/file/path"
        }
        Schematic {
            objectName : "testbench2"
            filePath: "/file/path"
        }

        State {
            objectName : "TRAN"
        }
        State {
            objectName : "AC"
        }
        State {
            objectName : "DC"
        }
        State {
            objectName : "SST"
        }


        Simulation {
            objectName : "nominal"
            Scenario  {

            }
            Scenario  {

            }


        }
    }

    Cell {
        objectName : "PAmpOP_out"
        Schematic {
            objectName : "testbench3"
            filePath: "/file/path"
        }
        Schematic {
            objectName : "testbench4"
            filePath: "/file/path"
        }


        State {
            objectName : "TRAN"
        }
        State {
            objectName : "AC"
        }
        State {
            objectName : "DC"
        }
        State {
            objectName : "SST"
        }
    }

    Cell {
        objectName : "PAmpOP"
        Schematic {
            objectName : "test_bench"
            filePath: "/file/path"
        }

        State {
            objectName : "TRAN"
        }
        State {
            objectName : "AC"
        }
        State {
            objectName : "DC"
        }
        State {
            objectName : "SST"
        }
    }


}



