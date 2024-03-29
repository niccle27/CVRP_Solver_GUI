# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
# Set the project name
project (cvrp_compute)

# Create a sources variable with a link to all cpp files to compile

set(SOURCES
src/CVRP_instance.cpp
src/CVRP_Solution.cpp
src/CW_Solver.cpp
src/IHeuristic.cpp
src/IMetaheuristic.cpp
src/main.cpp
src/Node.cpp
src/SA_Optimizer.cpp
src/Saving.cpp
src/Vehicle.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(cvrp_compute
    PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
)
