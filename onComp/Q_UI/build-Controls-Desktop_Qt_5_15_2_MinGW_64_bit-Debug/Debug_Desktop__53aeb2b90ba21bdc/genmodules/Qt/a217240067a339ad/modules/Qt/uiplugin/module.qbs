import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "UiPlugin"
    Depends { name: "Qt"; submodules: ["core","gui","widgets"]}

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
    cpp.defines: ["QT_UIPLUGIN_LIB"]
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include","D:/Soft/Prog/5.15.2/mingw81_64/include/QtUiPlugin"]
    cpp.libraryPaths: []
    
}
