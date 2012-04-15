/*
GeoJSONWriter class

Writes a Geometry object (wrapped or unwrapped) to a GeoJSON (v1.0) object.
For the The GeoJSON Format Specification see http://geojson.org/geojson-spec.html

- The "coordinates" property of the exported GeoJSON object may be null, if the geometry is empty.
- There is no "crs" property exported.
- You can set the rounding precision and whether you want to add the "bbox" property.
- 2/3-dimensional coordinates are supported.
*/

#ifndef GEOJSONWRITER_HPP
#define GEOJSONWRITER_HPP

#include <math.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/Point.h>
#include <geos/geom/LineString.h>
#include <geos/geom/Polygon.h>
#include <geos/geom/MultiPoint.h>
#include <geos/geom/MultiLineString.h>
#include <geos/geom/MultiPolygon.h>
#include "binding.hpp"
#include "geometry.hpp"

class GeoJSONWriter : public ObjectWrap {

    protected:
        int decimalPlaces;
        double factor;
        bool bbox;

    private:
        static Persistent<FunctionTemplate> constructor;
        static Persistent<String> symbolType;
        static Persistent<String> symbolCoordinates;
        static Persistent<String> symbolGeometries;
        static Persistent<String> symbolBbox;

    public:
        GeoJSONWriter();
        ~GeoJSONWriter();
        void setRoundingPrecision(int places);
        void setBbox(bool bbox);
        Handle<Value> write(const geos::geom::Geometry* geom);
        Handle<Value> writeBbox(const geos::geom::Geometry* geom);

        static void Initialize(Handle<Object> target);
        static Handle<Value> New(const Arguments& args);

    protected:
        double roundNumber(double coord);
        Handle<Array> coordinateToArray(const geos::geom::Coordinate* coord);
        Handle<Array> coordinateSequenceToArray(const geos::geom::CoordinateSequence* seq);
        Handle<Array> geometryCollectionToArrayOfArrays(const geos::geom::GeometryCollection* geom);
        Handle<Array> geometryCollectionToArrayOfObjects(const geos::geom::GeometryCollection* geom);
        Handle<Value> getCoordsOrGeom(const geos::geom::Geometry* geom);

        static Handle<Value> SetRoundingPrecision(const Arguments& args);
        static Handle<Value> SetBbox(const Arguments& args);
        static Handle<Value> Write(const Arguments& args);
        static Handle<Value> WriteBbox(const Arguments& args);

};

#endif
