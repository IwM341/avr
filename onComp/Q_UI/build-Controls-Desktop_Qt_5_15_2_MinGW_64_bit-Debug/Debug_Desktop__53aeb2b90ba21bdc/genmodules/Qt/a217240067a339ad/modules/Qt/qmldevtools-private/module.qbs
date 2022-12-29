import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "QmlDevTools"
    Depends { name: "Qt"; submodules: ["core-private"]}

    architectures: ["x86_64"]
    targetPlatform: "windows"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: ["$$[QT_HOST_LIBS]/libQt5Core.a"]
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5QmlDevTools"
    libNameForLinkerRelease: "Qt5QmlDevTools"
    libFilePathDebug: undefined
    libFilePathRelease: "D:/Soft/Prog/5.15.2/mingw81_64/lib/libQt5QmlDevTools.a"
    pluginTypes: []
    moduleConfig: ["lex","yacc","debug","depend_includepath","testcase_targets","import_qpa_plugin","windows","prepare_docs","qt_docs_targets","qt_build_extra","file_copies","qmake_use","qt","warn_on","link_prl","debug_and_release","precompile_header","no_plugin_manifest","win32","mingw","gcc","copy_dir_files","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","compile_examples","force_debug_info","largefile","precompile_header","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","warning_clean","debug","DebugBuild","Debug","build_pass","debug","DebugBuild","Debug","build_pass","minimal_syncqt","internal_module","generated_privates","qlalr","static","relative_qt_rpath","git_build","target_qt","c++11","strict_c++","c++14","c++1z","c99","c11","separate_debug_info","need_fwd_pri","qt_install_module","create_cmake","skip_target_version_ext","compiler_supports_fpmath","debug","DebugBuild","Debug","build_pass","have_target","staticlib","no_plist","exclusive_builds","debug_info","no_autoqmake","thread","moc","resources"]
    cpp.defines: ["QT_QMLDEVTOOLS_LIB"]
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include","D:/Soft/Prog/5.15.2/mingw81_64/include/QtQml","D:/Soft/Prog/5.15.2/mingw81_64/include/QtQml/5.15.2","D:/Soft/Prog/5.15.2/mingw81_64/include/QtQml/5.15.2/QtQml"]
    cpp.libraryPaths: ["C:/openssl/lib","C:/Utils/my_sql/mysql-5.7.25-winx64/lib","C:/Utils/postgresql/pgsql/lib"]
    isStaticLibrary: true
    Group {
        files: [Qt["qmldevtools-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
