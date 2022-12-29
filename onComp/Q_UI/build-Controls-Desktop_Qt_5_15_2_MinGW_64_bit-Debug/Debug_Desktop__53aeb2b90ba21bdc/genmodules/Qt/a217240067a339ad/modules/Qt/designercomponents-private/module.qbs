import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "DesignerComponents"
    Depends { name: "Qt"; submodules: ["core","gui-private","widgets-private","designer-private","xml"]}

    architectures: ["x86_64"]
    targetPlatform: "windows"
    hasLibrary: true
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
    libNameForLinkerDebug: "Qt5DesignerComponents"
    libNameForLinkerRelease: "Qt5DesignerComponents"
    libFilePathDebug: undefined
    libFilePathRelease: "D:/Soft/Prog/5.15.2/mingw81_64/lib/libQt5DesignerComponents.a"
    pluginTypes: []
    moduleConfig: ["lex","yacc","debug","depend_includepath","testcase_targets","import_plugins","import_qpa_plugin","windows","prepare_docs","qt_docs_targets","qt_build_extra","file_copies","qmake_use","qt","warn_on","link_prl","debug_and_release","shared","shared","no_plugin_manifest","win32","mingw","gcc","copy_dir_files","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","compile_examples","force_debug_info","largefile","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","debug","DebugBuild","Debug","build_pass","debug","DebugBuild","Debug","build_pass","internal_module","create_cmake","relative_qt_rpath","git_build","target_qt","c++11","strict_c++","c++14","c++1z","c99","c11","separate_debug_info","qt_install_headers","need_fwd_pri","qt_install_module","create_cmake","skip_target_version_ext","compiler_supports_fpmath","debug","DebugBuild","Debug","build_pass","have_target","dll","no_plist","exclusive_builds","debug_info","no_autoqmake","thread","designer_defines","uic","opengl","moc","resources","moc","resources"]
    cpp.defines: ["QT_DESIGNERCOMPONENTS_LIB"]
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include","D:/Soft/Prog/5.15.2/mingw81_64/include/QtDesignerComponents","D:/Soft/Prog/5.15.2/mingw81_64/include/QtDesignerComponents/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtDesignerComponents/5.15.2/QtDesignerComponents"]
    cpp.libraryPaths: []
    Group {
        files: [Qt["designercomponents-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary_import"]
    }
}
