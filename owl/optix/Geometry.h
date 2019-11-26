// ======================================================================== //
// Copyright 2019 Ingo Wald                                                 //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "RegisteredObject.h"
#include "SBTObject.h"
#include "Module.h"
#include "Buffer.h"

namespace owl {

  struct Geometry;
  
  struct GeometryType : public SBTObjectType {
    typedef std::shared_ptr<GeometryType> SP;
    
    GeometryType(Context *const context,
                 size_t varStructSize,
                 const std::vector<OWLVarDecl> &varDecls);

    virtual std::string toString() const { return "GeometryType"; }
    virtual void setClosestHitProgram(int rayType,
                                      Module::SP module,
                                      const std::string &progName)
    { IGNORING_THIS(); }

    virtual std::shared_ptr<Geometry> createGeometry() = 0;
  };

  struct TrianglesGeometryType : public GeometryType {
    typedef std::shared_ptr<TrianglesGeometryType> SP;
    
    TrianglesGeometryType(Context *const context,
                          size_t varStructSize,
                          const std::vector<OWLVarDecl> &varDecls)
      : GeometryType(context,varStructSize,varDecls)
    {}

    virtual std::string toString() const { return "TrianlgeGeometryType"; }
    virtual std::shared_ptr<Geometry> createGeometry() override;
  };

  struct UserGeometryType : public GeometryType {
    typedef std::shared_ptr<UserGeometryType> SP;
    
    UserGeometryType(Context *const context,
                     size_t varStructSize,
                     const std::vector<OWLVarDecl> &varDecls)
      : GeometryType(context,varStructSize,varDecls)
    {}

    virtual std::string toString() const { return "UserGeometryType"; }
    virtual std::shared_ptr<Geometry> createGeometry() override;
  };

  struct Geometry : public SBTObject<GeometryType> {
    typedef std::shared_ptr<Geometry> SP;

    Geometry(Context *const context,
             GeometryType::SP geometryType);
    virtual std::string toString() const { return "Geometry"; }
    
    GeometryType::SP geometryType;
  };

  struct TrianglesGeometry : public Geometry {
    typedef std::shared_ptr<TrianglesGeometry> SP;

    TrianglesGeometry(Context *const context,
                      GeometryType::SP geometryType)
      : Geometry(context,geometryType)
    {}

    void setVertices(Buffer::SP vertices)
    { IGNORING_THIS(); }
    void setIndices(Buffer::SP indices)
    { IGNORING_THIS(); }
    virtual std::string toString() const { return "TrianglesGeometry"; }
  };

  struct UserGeometry : public Geometry {
    typedef std::shared_ptr<UserGeometry> SP;

    UserGeometry(Context *const context,
                 GeometryType::SP geometryType)
      : Geometry(context,geometryType)
    {}
    virtual std::string toString() const { return "UserGeometry"; }
  };
  
} // ::owl
