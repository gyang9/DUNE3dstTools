LIST(APPEND INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/beamMonitoring)
LIST(APPEND INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/fluxSTV)
#LIST(APPEND INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/elecSim)
LIST(APPEND INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/nBKG)
LIST(APPEND INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/NuModel)
LIST(APPEND INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/reco)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/beamMonitoring)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fluxSTV)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/elecSim)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/nBKG)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/NuModel)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/reco)

SET(LOCAL_INCDIRS ${INCDIRS})
SET(INCDIRS ${LOCAL_INCDIRS} PARENT_SCOPE)

SET(LOCAL_MODULETargets ${MODULETargets})
LIST(REVERSE LOCAL_MODULETargets)
SET(MODULETargets ${LOCAL_MODULETargets} PARENT_SCOPE)
