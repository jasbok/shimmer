list(APPEND tests
    "catch.cpp"
    "mouse.cpp"
)
add_executable(catch ${tests})
target_link_libraries(catch "shimmer")
