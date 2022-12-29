import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "QuickTemplates2"
    Depends { name: "Qt"; submodules: ["qmlmodels-private","quicktemplates2"]}

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
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include/QtQuickTemplates2/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtQuickTemplates2/5.15.2/QtQuickTemplates2"]
    cpp.libraryPaths: []
    
}
