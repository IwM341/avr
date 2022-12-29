import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "3DQuickInput"
    Depends { name: "Qt"; submodules: ["core-private","qml-private","3dquick-private","3dcore-private","3dinput-private","3dquickinput"]}

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
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include/Qt3DQuickInput/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/Qt3DQuickInput/5.15.2/Qt3DQuickInput"]
    cpp.libraryPaths: []
    
}
