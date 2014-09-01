import Ev.Core 1.0
import Ev.Variation 1.0


Process {
    description: "my description"
    objectName: "my_process"
    Library {
        location: "$MGC_DESIGN_KIT/demo.lib"
        DeviceFamily {
            objectName : "Bipolar"
            Corner {
                objectName : "NPN_TYP"
                section: "typ"
                description: "Typical bipolar"
            }
            Corner {
                objectName : "NPN_BMIN"
                section: "min"
            }
            Corner {
                objectName : "NPN_BMAX"
                section: "max"
            }
        }
    }

    Parameter {
        objectName : "temp"
        textualValue : "1.45"
    }
    Parameter {
        objectName : "C"
        textualValue : "2.4"
    }
}

