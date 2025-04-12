set(target ${TABLES_CUSTOM})

file(GLOB hdrs "*.h*")

add_custom_target(${target} SOURCES ${hdrs})