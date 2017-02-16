list(APPEND tests
    "catch.cpp"
    "freetype.cpp"
    "menu_builder.cpp"
    "mouse.cpp"
    "scene_manager.cpp"
)
add_executable(catch ${tests})
target_link_libraries(catch "shimmer")
