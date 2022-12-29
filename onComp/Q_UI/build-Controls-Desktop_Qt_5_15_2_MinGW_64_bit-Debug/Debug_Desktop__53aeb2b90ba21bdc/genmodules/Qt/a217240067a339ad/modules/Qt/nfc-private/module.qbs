import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Nfc"
    Depends { name: "Qt"; submodules: ["nfc"]}

    architectures: ["x86_64"]
    targetPlatform: "windows"
    hasLibrary: false
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
    libNameForLinkerDebug: undefined
    libNameForLinkerRelease: undefined
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: []
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include/QtNfc/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtNfc/5.15.2/QtNfc"]
    cpp.libraryPaths: []
    
}
