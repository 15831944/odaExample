
android {
  DEFINES += ANDROID
  DEFINES += ANDROID_NDK_NATIVE
  DEFINES += ANDROID_WCHAR
  QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions -frtti
  ##QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions
  ##QMAKE_CXXFLAGS_RTTI_ON = -frtti

  CONFIG += exceptions_on
  ##CONFIG += rtti_on
  CONFIG += warn_off
}

include(./OdaQtViewSystem.pri)
