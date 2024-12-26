cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet et la version
project(LineaCore VERSION 1.0 LANGUAGES CXX)

# Spécifier la version minimale de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Désactiver les extensions spécifiques au compilateur

# Inclure les répertoires pour les fichiers d'en-tête
include_directories(${CMAKE_SOURCE_DIR}/include)

# Ajouter la bibliothèque
file(GLOB_RECURSE SOURCES "src/**/*.cpp") # Inclut tous les fichiers .cpp dans le dossier src
add_library(LineaCore ${SOURCES})

# Ajouter les tests
enable_testing() # Activer le support des tests
file(GLOB_RECURSE TEST_SOURCES "tests/**/*.cpp") # Inclut tous les fichiers de test
add_executable(TestLineaCore ${TEST_SOURCES})

# Lier la bibliothèque aux tests
target_link_libraries(TestLineaCore PRIVATE LineaCore)

# Ajouter une cible pour exécuter les tests
add_test(NAME TestLineaCore COMMAND TestLineaCore)