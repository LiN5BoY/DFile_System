#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_JXCqmlTools_qml_App_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_JXCqmlTools_qml_MainWindow_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_JXCqmlTools_qml_global_ItemsOriginal_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_JXCqmlTools_qml_global_GlobalModel_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_JXCqmlTools_qml_global_ItemsFooter_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_JXCqmlTools_qml_page_Xiaoju_Jiaoliu_Config_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_JXCqmlTools_qml_page_NWwdx_Jiaoliu_Config_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::TypedFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/App.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_App_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/MainWindow.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_MainWindow_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/global/ItemsOriginal.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_global_ItemsOriginal_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/global/GlobalModel.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_global_GlobalModel_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/global/ItemsFooter.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_global_ItemsFooter_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/page/Xiaoju_Jiaoliu_Config.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_page_Xiaoju_Jiaoliu_Config_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/JXCqmlTools/qml/page/NWwdx_Jiaoliu_Config.qml"), &QmlCacheGeneratedCode::_qt_qml_JXCqmlTools_qml_page_NWwdx_Jiaoliu_Config_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_JXCqmlTools)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_JXCqmlTools))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_JXCqmlTools)() {
    return 1;
}
