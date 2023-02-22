cmake_minimum_required(VERSION 3.20)
project(aoc LANGUAGES CXX)

# link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(${PROJECT_NAME} ${WIN32_GUI} main.cpp UI.cpp Simulation.cpp)

# if(WIN32)
#     set(LINK_OPTION /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
# endif()

target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTION})

# target_link_options(${PROJECT_NAME} PRIVATE ${WIN32_GUI})

# add_subdirectory(Matrix)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Matrix)
# target_link_libraries(${PROJECT_NAME} PRIVATE Matrix)

# add_subdirectory(DNN)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/DNN)
# target_link_libraries(${PROJECT_NAME} PRIVATE DNN)

# ## COMPILER SPECIFIC ##
# target_compile_options(${PROJECT_NAME} PRIVATE /MD)
# target_compile_options(${PROJECT_NAME} PRIVATE /arch:AVX2 /fp:fast)
# target_compile_options(${PROJECT_NAME} PRIVATE /openmp:llvm /openmp:experimental)

# # EXTERNAL LIBRARIES ##
# SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED COMPONENTS graphics system window audio)
set(SFML_LIBRARIES sfml-graphics sfml-system sfml-window sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})

# #  FFTW3
# target_link_libraries(${PROJECT_NAME} PRIVATE libfftw3-3)

# #  OpenMP
# find_package(OpenMP REQUIRED)
# if(OpenMP_CXX_FOUND)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
# endif()

# #  CUDA
# enable_language(CUDA)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
# # set_property(TARGET ${PROJECT_NAME} PROPERTY CUDA_SEPARABLE_COMPILATION ON) # This is for .cu files that access functions/globals defined in other .cu files.
# #   cuBLAS
# set(CUDA_TOOLKIT_LIBRARIES cublas curand cudnn)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CUDA_TOOLKIT_LIBRARIES})

# #  Python
# find_package(PythonLibs REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE ${PYTHON_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${PYTHON_LIBRARIES})

# # ACTIVATE CXX_STANDARD 20 ##
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

# # Copy bin files to the binary directory
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/openal32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/libfftw3-3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

# # Copy res files to the binary directory
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)