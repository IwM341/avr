import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "VirtualKeyboard"
    Depends { name: "Qt"; submodules: ["core","gui","qml","quick"]}

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
    libNameForLinkerDebug: "Qt5VirtualKeyboard"
    libNameForLinkerRelease: "Qt5VirtualKeyboard"
    libFilePathDebug: undefined
    libFilePathRelease: "D:/Soft/Prog/5.15.2/mingw81_64/lib/libQt5VirtualKeyboard.a"
    pluginTypes: ["virtualkeyboard"]
    moduleConfig: ["lex","yacc","debug","depend_includepath","testcase_targets","import_plugins","import_qpa_plugin","windows","prepare_docs","qt_docs_targets","qt_build_extra","file_copies","qmake_use","qt","warn_on","link_prl","debug_and_release","precompile_header","shared","shared","no_plugin_manifest","win32","mingw","gcc","copy_dir_files","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","compile_examples","force_debug_info","largefile","precompile_header","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","debug","DebugBuild","Debug","build_pass","debug","DebugBuild","Debug","build_pass","qtquickcompiler","no-pkg-config","disable-hunspell","lang-all","lang-ar_AR","lang-bg_BG","lang-cs_CZ","lang-da_DK","lang-de_DE","lang-el_GR","lang-en_GB","lang-en_US","lang-es_ES","lang-es_MX","lang-et_EE","lang-fa_FA","lang-fi_FI","lang-fr_CA","lang-fr_FR","lang-he_IL","lang-hi_IN","lang-hr_HR","lang-hu_HU","lang-id_ID","lang-it_IT","lang-ja_JP","lang-ko_KR","lang-ms_MY","lang-nb_NO","lang-nl_NL","lang-pl_PL","lang-pt_BR","lang-pt_PT","lang-ro_RO","lang-ru_RU","lang-sk_SK","lang-sl_SI","lang-sq_AL","lang-sr_SP","lang-sv_SE","lang-th_TH","lang-tr_TR","lang-uk_UA","lang-vi_VN","lang-zh_CN","lang-zh_TW","openwnn","hangul","pinyin","tcime","thai","cangjie","zhuyin","relative_qt_rpath","git_build","target_qt","c++11","strict_c++","c++14","c++1z","c99","c11","separate_debug_info","qt_install_headers","need_fwd_pri","qt_install_module","create_cmake","skip_target_version_ext","compiler_supports_fpmath","create_pc","debug","DebugBuild","Debug","build_pass","have_target","dll","no_plist","exclusive_builds","debug_info","no_autoqmake","thread","opengl","moc","resources"]
    cpp.defines: ["QT_VIRTUALKEYBOARD_LIB"]
    cpp.includePaths: ["D:/Soft/Prog/5.15.2/mingw81_64/include","D:/Soft/Prog/5.15.2/mingw81_64/include/QtVirtualKeyboard"]
    cpp.libraryPaths: []
    Group {
        files: [Qt["virtualkeyboard"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary_import"]
    }
}
