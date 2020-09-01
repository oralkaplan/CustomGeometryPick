import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick3D 1.15
import QtQuick3D.Helpers 1.15
import QtQuick3D.Materials 1.15
import ymrh.com.wsds.geometry 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    View3D {
        id: view_default

        anchors.fill: parent
        environment: SceneEnvironment {
            clearColor: "darkgrey"
            backgroundMode: SceneEnvironment.Color
        }

        DirectionalLight {
            eulerRotation.y: -100
            brightness: 100
            SequentialAnimation on eulerRotation.y {
                loops: Animation.Infinite
                PropertyAnimation {
                    duration: 5000
                    to: 360
                    from: 0
                }
            }
        }

        PerspectiveCamera {
            id: pcam_default

            position: Qt.vector3d( 0, 100, 400 )

            Component.onCompleted: lookAt( mdl_sphere )
        }

        WasdController {
            controlledObject: pcam_default
            mouseEnabled: true
            keysEnabled: true
        }

        Model {
            source: "#Cube"
            pickable: true
            position: Qt.vector3d( 100, 0, 0 )
            materials: PlasticStructuredRedEmissiveMaterial{}
        }

        Model {
            id: mdl_cube

            geometry: CubeGeometry{
                name: "Cube"
            }
            pickable: true
            materials: [
                PrincipledMaterial {
                    baseColor: "#41cd52"
                    metalness: 0.1
                    roughness: 0.9
                    specularAmount: 0
                    indexOfRefraction: 2.97
                    specularTint: 0.0
                    opacity: 1.0
                }
            ]
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            const pickResult = view_default.pick( mouse.x, mouse.y )
            if( pickResult.objectHit ) {
                console.log( pickResult.objectHit )
            }
        }
    }
}
