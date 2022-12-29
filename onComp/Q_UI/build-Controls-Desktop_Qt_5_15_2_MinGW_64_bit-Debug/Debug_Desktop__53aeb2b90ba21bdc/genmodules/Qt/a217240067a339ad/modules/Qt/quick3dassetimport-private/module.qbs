import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Quick3DAssetImport"
    Depends { name: "Qt"; submodules: ["core-private","quick3drender-private","quick3dutils-private","quick3dassetimport"]}

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
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include/QtQuick3DAssetImport/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtQuick3DAssetImport/5.15.2/QtQuick3DAssetImport"]
    cpp.libraryPaths: []
    
}
