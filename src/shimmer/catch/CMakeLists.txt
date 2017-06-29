list(APPEND tests
    "catch.cpp"
    "freetype.cpp"
    "menu_builder.cpp"
    "mouse.cpp"
    "video/common/model.cpp"
    "video/common/scene.cpp"
)
add_executable(catch ${tests})
target_include_directories(catch BEFORE PUBLIC ".")
target_link_libraries(catch "shimmer")
