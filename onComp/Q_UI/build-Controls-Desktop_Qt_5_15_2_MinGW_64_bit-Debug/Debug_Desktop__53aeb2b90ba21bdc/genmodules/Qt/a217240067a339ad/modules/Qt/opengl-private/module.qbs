import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "OpenGL"
    Depends { name: "Qt"; submodules: ["core-private","gui-private","widgets-private","opengl"]}

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
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include/QtOpenGL/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtOpenGL/5.15.2/QtOpenGL"]
    cpp.libraryPaths: []
    
}
