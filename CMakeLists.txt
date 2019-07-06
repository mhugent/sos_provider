CMAKE_MINIMUM_REQUIRED (VERSION 2.8.8)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)

SET ( QGIS_INCLUDE_DIR "C:/Program Files/QGIS 2 18/include" CACHE PATH "Path to QGIS include directory")
SET ( QGIS_CORE_LIB "C:/Program Files/QGIS 2 18/lib/qgis_core.lib" CACHE PATH "QGIS core library" )
SET ( EXPAT_INCLUDE_DIR "" CACHE PATH "Path to Expat include files" )
SET ( EXPAT_LIBRARY "" CACHE FILEPATH "Path to libexpat")
SET ( QT_INCLUDE_DIR "" CACHE PATH "Path to Qt include directory" )
SET ( QT_LIB_DIR "" CACHE PATH "Path to the directory containing the Qt libraries")

SET (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
########################################################
# Files

SET(SOS_SRCS
  qgssosdata.cpp
  qgssosfeatureiterator.cpp
  qgssosprovider.cpp
  qgsxmldata.cpp
)

SET (SOS_MOC_HDRS
  qgsxmldata.h
)

########################################################
# Build


INCLUDE_DIRECTORIES (
  ${QGIS_INCLUDE_DIR}
  ${EXPAT_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}/QtCore
  ${QT_INCLUDE_DIR}/QtGui
  ${QT_INCLUDE_DIR}/QtNetwork
  ${QT_INCLUDE_DIR}/QtWidgets
  ${QT_INCLUDE_DIR}/QtXml
  ${QT_INCLUDE_DIR}/Qt
  ${QT_INCLUDE_DIR}
)

ADD_LIBRARY (sosprovider MODULE ${SOS_SRCS} ${SOS_MOC_SRCS} )

IF (WIN32)
	ADD_DEFINITIONS( -DCORE_EXPORT=__declspec\(dllimport\))
	ADD_DEFINITIONS( -DGUI_EXPORT=__declspec\(dllimport\))
	ADD_DEFINITIONS( -Dnoexcept= )
ELSE()
  ADD_DEFINITIONS( -DCORE_EXPORT= )
	ADD_DEFINITIONS( -DGUI_EXPORT= )
ENDIF (WIN32)

IF (WIN32)
  TARGET_LINK_LIBRARIES (sosprovider
  ${QGIS_CORE_LIB}
  ${EXPAT_LIBRARY}
  ${QT_LIB_DIR}/QtCore5.lib
  ${QT_LIB_DIR}/QtGui5.lib
  ${QT_LIB_DIR}/QtNetwork5.lib )
ELSE()
  TARGET_LINK_LIBRARIES (sosprovider
  ${QT_LIB_DIR}/libQt5Core.so
  ${QT_LIB_DIR}/libQt5Gui.so
  ${QT_LIB_DIR}/libQt5Network.so )
ENDIF(WIN32)


########################################################
# Install

INSTALL(TARGETS sosprovider DESTINATION . )
