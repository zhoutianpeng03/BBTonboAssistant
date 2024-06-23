
# config sherpa-onnx
set(SHERPA_ONNX "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sherpa-onnx")

include_directories(${SHERPA_ONNX}/include)
link_directories(${SHERPA_ONNX}/lib/${BBTonbo_3RDPARTY_LIBRARY_FOLDER})

set(MODEL_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/models")

# configure_file(
#     "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/config.h"
#     @ONLY
# )
