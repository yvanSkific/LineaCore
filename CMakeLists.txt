cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet et la version
project(LineaCore VERSION 1.0 LANGUAGES CXX)

# Spécifier la version minimale de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Désactiver les extensions spécifiques au compilateur

#rediriger toutes les sorties vers le répertoire bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Inclure les répertoires pour les fichiers d'en-tête
include_directories(${CMAKE_SOURCE_DIR}/include)

# Ajouter la bibliothèque principale
file(GLOB_RECURSE SOURCES "src/**/*.cpp") # Inclut tous les fichiers .cpp dans le dossier src
add_library(LineaCore ${SOURCES})

# Configurer libxml2 avec des options minimalistes
set(LIBXML2_WITH_CATALOG OFF CACHE BOOL "Disable catalog support")
set(LIBXML2_WITH_DEBUG OFF CACHE BOOL "Disable debug support")
set(LIBXML2_WITH_HTML OFF CACHE BOOL "Disable HTML support")
set(LIBXML2_WITH_HTTP OFF CACHE BOOL "Disable HTTP support")
set(LIBXML2_WITH_ICONV OFF CACHE BOOL "Disable ICONV support")
set(LIBXML2_WITH_ICU OFF CACHE BOOL "Disable ICU support")
set(LIBXML2_WITH_ISO8859X ON CACHE BOOL "Enable ISO8859X support if no iconv")
set(LIBXML2_WITH_LEGACY OFF CACHE BOOL "Disable legacy APIs")
set(LIBXML2_WITH_LZMA OFF CACHE BOOL "Disable liblzma support")
set(LIBXML2_WITH_MODULES OFF CACHE BOOL "Disable dynamic modules support")
set(LIBXML2_WITH_OUTPUT ON CACHE BOOL "Enable serialization support")
set(LIBXML2_WITH_PATTERN ON CACHE BOOL "Enable xmlPattern support")
set(LIBXML2_WITH_PROGRAMS OFF CACHE BOOL "Disable programs build")
set(LIBXML2_WITH_PUSH ON CACHE BOOL "Disable PUSH parser")
set(LIBXML2_WITH_PYTHON OFF CACHE BOOL "Disable Python bindings")
set(LIBXML2_WITH_READLINE OFF CACHE BOOL "Disable readline support")
set(LIBXML2_WITH_REGEXPS ON CACHE BOOL "Enable Regular Expressions support")
set(LIBXML2_WITH_SAX1 OFF CACHE BOOL "Disable SAX1 interface")
set(LIBXML2_WITH_TESTS OFF CACHE BOOL "Disable tests build")
set(LIBXML2_WITH_THREADS ON CACHE BOOL "Enable multithread support")
set(LIBXML2_WITH_TLS OFF CACHE BOOL "Disable TLS support")
set(LIBXML2_WITH_VALID ON CACHE BOOL "Enable DTD validation")
set(LIBXML2_WITH_XINCLUDE ON CACHE BOOL "Enable XInclude support")
set(LIBXML2_WITH_XPATH ON CACHE BOOL "Enable XPath support")
set(LIBXML2_WITH_ZLIB OFF CACHE BOOL "Enable zlib support for KMZ files")

# Ajouter libxml2
add_subdirectory(external/libxml2)
target_include_directories(LineaCore PRIVATE external/libxml2/include)
target_link_libraries(LineaCore LibXml2) # LibXml2 est le nom par défaut de la bibliothèque générée

# Ajouter Google Test
add_subdirectory(external/googletest)
include_directories(${PROJECT_SOURCE_DIR}/external/googletest/googletest/include)

# Ajouter les tests
file(GLOB_RECURSE TEST_SOURCES "tests/**/*.cpp") # Inclut tous les fichiers de test

# Créer les exécutables de test
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} LineaCore gtest gtest_main)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Activer les tests
enable_testing()