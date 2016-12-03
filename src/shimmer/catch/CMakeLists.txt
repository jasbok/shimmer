list(APPEND tests
    "catch.cpp"
    "freetype.cpp"
    "menu_builder.cpp"
    "mouse.cpp"
)
add_executable(catch ${tests})
target_link_libraries(catch "shimmer")
