aux_source_directory(. PARSER_DIR_SRC)
aux_source_directory(src PARSER_DIR_SRC)

add_library(parser STATIC ${PARSER_DIR_SRC})

target_link_libraries(parser
        lexer
        codegen)