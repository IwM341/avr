import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Quick3DRuntimeRender"
    Depends { name: "Qt"; submodules: ["quick3drender-private","quick3dassetimport-private","quick3dutils-private","quick3druntimerender"]}

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
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include/QtQuick3DRuntimeRender/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtQuick3DRuntimeRender/5.15.2/QtQuick3DRuntimeRender"]
    cpp.libraryPaths: []
    
}
