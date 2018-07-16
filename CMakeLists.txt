find_package( Qt4 REQUIRED )

SET ( QGIS_INCLUDE_DIR "C:/Program Files/QGIS 2 18/include" CACHE PATH "Path to QGIS include directory")
SET ( QGIS_CORE_LIB "C:/Program Files/QGIS 2 18/lib/qgis_core.lib" CACHE PATH "QGIS core library" )
SET ( EXPAT_INCLUDE_DIR "" CACHE PATH "Path to Expat include files" )
SET ( EXPAT_LIBRARY "" CACHE FILEPATH "Path to libexpat")
SET ( QT_INCLUDE_DIR "" CACHE PATH "Path to Qt include directory" )
SET ( QT_LIB_DIR "" CACHE PATH "Path to the directory containing the Qt libraries")

SET (CMAKE_CXX_STANDARD 11)

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

QT4_WRAP_CPP(SOS_MOC_SRCS ${SOS_MOC_HDRS})

INCLUDE_DIRECTORIES (
  ${QGIS_INCLUDE_DIR}
  ${EXPAT_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}/QtCore
  ${QT_INCLUDE_DIR}/QtGui
  ${QT_INCLUDE_DIR}/QtNetwork
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
  ${QT_LIB_DIR}/QtCore4.lib
  ${QT_LIB_DIR}/QtGui4.lib
  ${QT_LIB_DIR}/QtNetwork4.lib
  ${QT_LIB_DIR}/QtXml4.lib )
ELSE()
  TARGET_LINK_LIBRARIES (sosprovider
  ${QT_LIB_DIR}/libQtCore.so
  ${QT_LIB_DIR}/libQtGui.so
  ${QT_LIB_DIR}/libQtNetwork.so
  ${QT_LIB_DIR}/libQtXml.so )
ENDIF(WIN32)


########################################################
# Install

INSTALL(TARGETS sosprovider DESTINATION . )
