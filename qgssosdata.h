/***************************************************************************
                          qgssosdata.h  -  description
                          --------------------------------
    begin                : June 2013
    copyright            : (C) 2013 by Marco Hugentobler
    email                : marco dot hugentobler at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSSOSDATA_H
#define QGSSOSDATA_H

#include "qgsfeature.h"
#include "qgsxmldata.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <expat.h>

class QgsCoordinateReferenceSystem;
class QgsRectangle;

class QgsSOSData: public QgsXMLData
{
  public:
    QgsSOSData( const QString& uri );
    ~QgsSOSData();
    /**Load features into map
        @param uri  service url (GetFeatureOfInterest)
        @param features sensor points are added to the feature map*/
    int getFeatures( QMap<QgsFeatureId, QgsFeature* >* features,
                     QgsCoordinateReferenceSystem* crs, QgsRectangle* extent );

  private:
    enum ParseMode
    {
      None,
      Identifier,
      Name,
      Pos
    };

    /**XML handler methods*/
    void startElement( const XML_Char* el, const XML_Char** attr );
    void endElement( const XML_Char* el );
    void characters( const XML_Char* chars, int len );

    QMap<QgsFeatureId, QgsFeature* >* mFeatures;
    QgsCoordinateReferenceSystem* mCrs;
    QgsRectangle* mExtent;
    QgsFeature* mCurrentFeature;
    ParseMode mParseMode;
    bool mFinished;
};

#endif // QGSSOSDATA_H
