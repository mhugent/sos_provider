find_package( Qt4 REQUIRED )

SET ( QGIS_DIR "C:/Program Files/QGIS 2 18" CACHE PATH "Path to QGIS installation")
SET ( EXPAT_INCLUDE_DIR "" CACHE PATH "Path to Expat include files" )
SET ( EXPAT_LIBRARY "" CACHE FILEPATH "Path to libexpat")
SET ( QWT_INCLUDE_DIR "" CACHE PATH "Path to QWT include files" )
#SET ( GEOS_LIBRARY "" CACHE FILEPATH "Path to GEOS lib")
#SET ( GEOS_INCLUDE_DIR "" CACHE PATH "Path to geos include directory" )
SET ( QT_LIB_DIR "" CACHE PATH "Path to the directory containing the Qt libraries")


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
  ${QGIS_DIR}/include
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
ENDIF (WIN32)

TARGET_LINK_LIBRARIES (sosprovider
  ${QGIS_DIR}/lib/qgis_core.lib
  ${QGIS_DIR}/lib/qgis_gui.lib
  ${EXPAT_LIBRARY}
  ${QT_LIB_DIR}/QtCore4.lib
  ${QT_LIB_DIR}/QtGui4.lib
  ${QT_LIB_DIR}/QtNetwork4.lib
  ${QT_LIB_DIR}/QtXml4.lib
)


########################################################
# Install

INSTALL(TARGETS sosprovider DESTINATION . )
