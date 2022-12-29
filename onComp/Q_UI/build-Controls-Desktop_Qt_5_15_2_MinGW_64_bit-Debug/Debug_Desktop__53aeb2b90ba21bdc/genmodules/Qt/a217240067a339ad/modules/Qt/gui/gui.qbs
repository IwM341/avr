import qbs.FileInfo
import qbs.ModUtils
import qbs.Utilities
import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Gui"

    property string uicName: "uic"

    FileTagger {
        patterns: ["*.ui"]
        fileTags: ["ui"]
    }

    Rule {
        inputs: ["ui"]

        Artifact {
            filePath: FileInfo.joinPaths(input.moduleProperty("Qt.core", "generatedHeadersDir"),
                                         'ui_' + input.completeBaseName + '.h')
            fileTags: ["hpp"]
        }

        prepare: {
            var uicPath = Utilities.versionCompare(product.Qt.gui.version, "6.1") < 0
                    ? product.Qt.core.binPath + '/' + product.Qt.gui.uicName
                    : product.Qt.core.libExecPath + '/' + product.Qt.gui.uicName;

            var cmd = new Command(uicPath, [input.filePath, '-o', output.filePath]);
            cmd.description = 'uic ' + input.fileName;
            cmd.highlight = 'codegen';
            return cmd;
        }
    }

    property string defaultQpaPlugin: "qwindows"
    architectures: ["x86_64"]
    targetPlatform: "windows"
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5Gui"
    libNameForLinkerRelease: "Qt5Gui"
    libFilePathDebug: undefined
    libFilePathRelease: "D:/Soft/Prog/5.15.2/mingw81_64/lib/libQt5Gui.a"
    pluginTypes: ["accessiblebridge","platforms","platforms/darwin","xcbglintegrations","platformthemes","platforminputcontexts","generic","iconengines","imageformats","egldeviceintegrations"]

    cpp.entryPoint: qbs.targetOS.containsAny(["ios", "tvos"])
                      && Utilities.versionCompare(version, "5.6.0") >= 0
                  ? "_qt_main_wrapper"
                  : undefined

    cpp.defines: ["QT_GUI_LIB"]
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include","D:/Soft/Prog/5.15.2/mingw81_64/include/QtGui","D:/Soft/Prog/5.15.2/mingw81_64/include/QtANGLE"]
    cpp.libraryPaths: []

    Properties {
        condition: Qt.core.staticBuild && qbs.targetOS.contains("ios")
        cpp.frameworks: base.concat(["UIKit", "QuartzCore", "CoreText", "CoreGraphics",
                                     "Foundation", "CoreFoundation", "AudioToolbox"])
    }
    cpp.frameworks: base
    Group {
        files: "D:/Soft/Prog/5.15.2/mingw81_64/lib/metatypes/qt5gui_metatypes.json"
        filesAreTargets: true
        fileTags: ["qt.core.metatypes"]
    }
    Group {
        files: [Qt["gui"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary_import"]
    }
}

