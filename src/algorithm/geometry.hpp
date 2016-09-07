//
// Copyright (c) 2015-2016 CNRS
//
// This file is part of Pinocchio
// Pinocchio is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// Pinocchio is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Lesser Public License for more details. You should have
// received a copy of the GNU Lesser General Public License along with
// Pinocchio If not, see
// <http://www.gnu.org/licenses/>.

#ifndef __se3_algo_geometry_hpp__
#define __se3_algo_geometry_hpp__

#include "pinocchio/multibody/visitor.hpp"
#include "pinocchio/multibody/model.hpp"

#include "pinocchio/algorithm/kinematics.hpp"
#include "pinocchio/multibody/geometry.hpp"

namespace se3
{

  ///
  /// \brief Apply a forward kinematics and update the placement of the geometry objects.
  ///
  /// \param[in] model The model structure of the rigid body system.
  /// \param[in] data The data structure of the rigid body system.
  /// \param[in] geom The geometry model containing the collision objects.
  /// \param[out] geom_data The geometry data containing the placements of the collision objects. See oMg field in GeometryData.
  /// \param[in] q The joint configuration vector (dim model.nq).
  ///
  inline void updateGeometryPlacements(const Model & model,
                                       Data & data,
                                       const GeometryModel & geom,
                                       GeometryData & geom_data,
                                       const Eigen::VectorXd & q
                                       );
  
  ///
  /// \brief Update the placement of the geometry objects according to the current joint placements contained in data.
  ///
  /// \param[in] model The model structure of the rigid body system.
  /// \param[in] data The data structure of the rigid body system.
  /// \param[in] geom The geometry model containing the collision objects.
  /// \param[out] geom_data The geometry data containing the placements of the collision objects. See oMg field in GeometryData.
  ///
  inline void updateGeometryPlacements(const Model & model,
                                       const Data & data,
                                       const GeometryModel & geom,
                                       GeometryData & geom_data
                                       );

#ifdef WITH_HPP_FCL

  /// Compute the forward kinematics, update the geometry placements and
  /// calls computeCollision for every active pairs of GeometryData.
  ///
  /// \param[in] model robot model (const)
  /// \param[out] data corresponding data (nonconst) where FK results are stored
  /// \param[in] model_geom geometry model (const)
  /// \param[out] data_geom corresponding geometry data (nonconst) where distances are computed
  /// \param[in] q robot configuration.
  /// \param[in] stopAtFirstCollision if true, stop the loop on pairs after the first collision.
  /// \return When ComputeShortest is true, the index of the collision pair which has the shortest distance.
  ///         When ComputeShortest is false, the number of collision pairs.
  /// \warning if stopAtFirstcollision = true, then the collisions vector will
  /// not be entirely fulfilled (of course).
  inline bool computeCollisions(const Model & model,
                                Data & data,
                                const GeometryModel & model_geom,
                                GeometryData & data_geom,
                                const Eigen::VectorXd & q,
                                const bool stopAtFirstCollision = false
                                );

  /// Compute the forward kinematics, update the geometry placements and
  /// calls computeDistance for every active pairs of GeometryData.
  ///
  /// \param[in] ComputeShortest default to true.
  /// \param[in][out] model: robot model (const)
  /// \param[out] data: corresponding data (nonconst) where FK results are stored
  /// \param[in] model_geom: geometry model (const)
  /// \param[out] data_geom: corresponding geometry data (nonconst) where distances are computed
  /// \param[in] q: robot configuration.
  /// \return When ComputeShortest is true, the index of the collision pair which has the shortest distance.
  ///         When ComputeShortest is false, the number of collision pairs.
  template <bool ComputeShortest>
  inline std::size_t computeDistances(const Model & model,
                                      Data & data,
                                      const GeometryModel & model_geom,
                                      GeometryData & data_geom,
                                      const Eigen::VectorXd & q
                                      );

  /// Compute the radius of the geometry volumes attached to every joints.
  /// \sa GeometryData::radius
  inline void computeBodyRadius(const Model &         model,
                                const GeometryModel & geomModel,
                                GeometryData &        geomData);
#endif // WITH_HPP_FCL

  /// Append geomModel2 to geomModel1
  ///
  /// The steps for appending are:
  /// \li add GeometryObject of geomModel2 to geomModel1,
  /// \li add the collision pairs of geomModel2 into geomModel1 (indexes are updated)
  /// \li add all the collision pairs between geometry objects of geomModel1 and geomModel2.
  /// \li update the inner objects of geomModel1 with the inner objects of geomModel2
  /// \li update the outer objects (see TODO)
  /// It is possible to ommit both data (an additional function signature is available which makes
  /// them optionnal), then inner/outer objects are not updated.
  ///
  /// \param[out] geomModel1   geometry model where the data is added
  /// \param[out] geomData1    corresponding geometry data, where in/outer objects are updated
  /// \param[in]  geomModel2   geometry model from which new geometries are taken
  /// \param[out] geomData2    geometry data corresponding to geomModel2.
  /// \warning Radius should be recomputed.
  /// \todo The geometry objects of geomModel2 should be added as outerObjects
  ///       of the joints originating from model1 but I do not know how to do it.
  inline void appendGeometryModel(GeometryModel & geomModel1,
                                  GeometryData & geomData1,
                                  const GeometryModel & geomModel2,
                                  const GeometryData & geomData2);

} // namespace se3 

/* --- Details -------------------------------------------------------------------- */
#include "pinocchio/algorithm/geometry.hxx"

#endif // ifndef __se3_algo_geometry_hpp__
