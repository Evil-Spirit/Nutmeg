set(NEWTON_CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source/core)
set(NEWTON_PHYSICS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source/physics)
set(NEWTON_NEWTON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source/newton)

set(NEWTON_CORE_SRC
	${NEWTON_CORE_PATH}/dg.cpp
	${NEWTON_CORE_PATH}/dgRef.cpp
	${NEWTON_CORE_PATH}/dgCRC.cpp
	${NEWTON_CORE_PATH}/dgTree.cpp
	${NEWTON_CORE_PATH}/dgNode.cpp
	${NEWTON_CORE_PATH}/dgTypes.cpp
	${NEWTON_CORE_PATH}/dgMatrix.cpp
	${NEWTON_CORE_PATH}/dgGoogol.cpp
	${NEWTON_CORE_PATH}/dgMemory.cpp
	${NEWTON_CORE_PATH}/dgSphere.cpp
	${NEWTON_CORE_PATH}/dgRandom.cpp
	${NEWTON_CORE_PATH}/dgThreads.cpp
	${NEWTON_CORE_PATH}/dgPolyhedra.cpp
	${NEWTON_CORE_PATH}/dgQuaternion.cpp
	${NEWTON_CORE_PATH}/dgConvexHull3d.cpp
	${NEWTON_CORE_PATH}/dgConvexHull4d.cpp
	${NEWTON_CORE_PATH}/dgIntersections.cpp
	${NEWTON_CORE_PATH}/dgAABBPolygonSoup.cpp
	${NEWTON_CORE_PATH}/dgSmallDeterminant.cpp
	${NEWTON_CORE_PATH}/dgPolygonSoupBuilder.cpp
	${NEWTON_CORE_PATH}/dgPolyhedraMassProperties.cpp
	${NEWTON_CORE_PATH}/dgDelaunayTetrahedralization.cpp)

set(NEWTON_PHYSICS_SRC
	${NEWTON_PHYSICS_PATH}/dgWorld.cpp
	${NEWTON_PHYSICS_PATH}/dgBody.cpp
	${NEWTON_PHYSICS_PATH}/dgMeshEffect.cpp
	${NEWTON_PHYSICS_PATH}/dgMeshEffect2.cpp
	${NEWTON_PHYSICS_PATH}/dgMeshEffectSolidTree.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionConvex.cpp
	${NEWTON_PHYSICS_PATH}/dgBallConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgBilateralConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgCorkscrewConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgHingeConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgNarrowPhaseCollision.cpp
	${NEWTON_PHYSICS_PATH}/dgBroadPhaseCollision.cpp
	${NEWTON_PHYSICS_PATH}/dgMinkowskiConv.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionBox.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionCapsule.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionBVH.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionMesh.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionUserMesh.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionChamferCylinder.cpp
	${NEWTON_PHYSICS_PATH}/dgPointToCurveConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionCone.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionConvexHull.cpp
	${NEWTON_PHYSICS_PATH}/dgSlidingConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionConvexModifier.cpp
	${NEWTON_PHYSICS_PATH}/dgUniversalConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgCollision.cpp
	${NEWTON_PHYSICS_PATH}/dgUpVectorConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionCylinder.cpp
	${NEWTON_PHYSICS_PATH}/dgUserConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionEllipse.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionNull.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionScene.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionCompoundBreakable.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionHeightField.cpp
	${NEWTON_PHYSICS_PATH}/dgWorldDynamicUpdate.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionSphere.cpp
	${NEWTON_PHYSICS_PATH}/dgCollisionCompound.cpp
	${NEWTON_PHYSICS_PATH}/dgConnectorConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgConstraint.cpp
	${NEWTON_PHYSICS_PATH}/dgBodyMasterList.cpp
	${NEWTON_PHYSICS_PATH}/dgContact.cpp)

set(NEWTON_NEWTON_SRC
	${NEWTON_NEWTON_PATH}/Newton.cpp
	${NEWTON_NEWTON_PATH}/NewtonClass.cpp)

set(NEWTON_ALL_SRC ${NEWTON_CORE_SRC} ${NEWTON_PHYSICS_SRC} ${NEWTON_NEWTON_SRC})

add_library(Newton STATIC ${NEWTON_ALL_SRC})

target_include_directories(Newton PUBLIC
	${NEWTON_CORE_PATH}
	${NEWTON_PHYSICS_PATH}
	${NEWTON_NEWTON_PATH})

if(MSVC)
	# On MSVC Newton.h uses __declspec(dllimport) unless _NEWTON_USE_LIB is defined.
	# Mark PUBLIC so consumers that include Newton.h also see the definition.
	target_compile_definitions(Newton PUBLIC _NEWTON_USE_LIB)
	target_compile_definitions(Newton PRIVATE _CRT_SECURE_NO_WARNINGS)
	target_compile_options(Newton PRIVATE /O2 /fp:fast /W3)
else()
	target_compile_options(Newton PRIVATE
		-fPIC -O2 -msse -msse2 -mfpmath=sse -ffast-math -fsingle-precision-constant
		-Wno-strict-aliasing -Wno-deprecated-declarations -Wno-unused-result -Wno-maybe-uninitialized)
endif()
