import Ev.Core 1.0

Property {

    objectName : "commandName"
    description: "Command label"

    Property {
        id : _bool
        objectName : "Boolean"
        label: "Boolean"
        editMode :Property.Boolean
        value : false
        enabled : _int.value > 5
    }

    Property {
        id : _enum
        objectName : "Enum"
        label: "Enum"
        editMode :Property.Enum
        value: "v1"
        property variant a_keys: ["v1","v2","v3","v4"]
    }

    Property {
        id : _int
        objectName : "Int"
        label: "Int"
        editMode :Property.Int
        value: 3
        property int a_min: -9
        property int a_max: 120
        property int a_step: 3
    }

    Property {
        objectName : "IntRO"
        label: "IntRO"
        editMode :Property.Int
        value: 3
        readOnly: true
        property int a_min: -9
        property int a_max: 120
        property int a_step: 3
    }

    Property {
        id : _double
        objectName : "Double"
        label: "Double"
        editMode :Property.Double
        visible : _int.value > 5
        value: 4.5
        property real a_min: -100
        property real a_max:  100
        property real a_step: 0.001

    }

    Property {
        id : _spice
        objectName : "Spice"
        label: "Spice"
        editMode :Property.SpiceNumber
        value: 4.5
        property real a_min: -100
        property real a_max:  100
        property real a_step: 0.001
    }

    Property {
        id : _str
        objectName : "String"
        label: "String"
        editMode :Property.String
        value : "a string"
    }

    Property {
        id : _color
        objectName : "Color"
        label: "Color"
        editMode :Property.Color
        value: "#346587"

    }

    Property {
        id : _font
        objectName : "Font"
        label: "Font"
        editMode :Property.Font
    }

    Property {
        id : _file
        objectName : "File"
        label: "File"
        editMode :Property.File
        value : "/home/ghaith/"
    }

    Property {
        id : _dir
        objectName : "Directory"
        label: "Directory"
        editMode :Property.Directory
        value : "/home/ghaith/"
    }


    function netlist() {
        return ".command "+ _dir.value;
    }



}
