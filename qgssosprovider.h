/***************************************************************************
                          qgssosprovider.h  -  description
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

#ifndef QGSSOSPROVIDER_H
#define QGSSOSPROVIDER_H

#include "qgscoordinatereferencesystem.h"
#include "qgsfeatureiterator.h"
#include "qgsvectordataprovider.h"

class QgsSpatialIndex;
class QgsSOSFeatureIterator;

class QgsSOSProvider: public QgsVectorDataProvider
{
  public:
    QgsSOSProvider( const QString& uri );
    ~QgsSOSProvider();

    QgsFeatureIterator getFeatures( const QgsFeatureRequest& request = QgsFeatureRequest() ) const override;

    virtual QgsAbstractFeatureSource* featureSource() const;

    //abstract methods QgsVectorDataProvider
    QgsWkbTypes::Type wkbType() const override;
    long featureCount() const;
    QgsFields fields() const override;

    //abstract methods QgsDataProvider
    QgsCoordinateReferenceSystem crs() const override;
    QgsRectangle extent() const override;
    bool isValid() const override;
    QString name() const;
    QString description() const;

  private:
    QgsRectangle mExtent;
    bool mValid;
    QgsFields mFields;
    QMap<QgsFeatureId, QgsFeature* > mFeatures;
    QgsSpatialIndex* mSpatialIndex;
    QgsCoordinateReferenceSystem mCrs;

    QgsSOSFeatureIterator* mActiveIterator;

    void loadData();
    void reloadSpatialIndex();

    friend class QgsSOSFeatureSource;
};

#endif // QGSSOSPROVIDER_H
