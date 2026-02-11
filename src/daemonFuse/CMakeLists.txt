cmake_minimum_required(VERSION 3.20)

message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

# --- 1. CONFIGURATION DU CROSS-COMPILATION ---
if($ENV{CROSS_COMPILE})
    message(STATUS "Configuring for Raspberry Pi (Cross-Compilation)...")
    set(CMAKE_TOOLCHAIN_FILE $ENV{HOME}/arm-cross-comp-env/rpi-zero-w-toolchain.cmake)
else()
    message(STATUS "Configuring for Local Development (VM Native)...")
endif()

project(SETR_TP2_CLIENT)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_CLIENT setrfs.c fstools.c communications.c)

add_executable(setr_tp2_daemonfuse ${SOURCE_CLIENT})

# --- 2. GESTION DES DRAPEAUX (CORRECTION ICI) ---
# IMPORTANT : J'ai enlevé les guillemets (") autour des flags.
# Cela crée une LISTE CMake au lieu d'une STRING unique.

set(WARNING_FLAGS 
    -Wall -Wextra -Wpedantic -Wduplicated-cond 
    -Wlogical-op -Wnull-dereference -Wjump-misses-init -Wshadow
)

# Choix des flags selon le mode
if($ENV{CROSS_COMPILE})
    # Sur le Pi
    set(SANITIZER_FLAGS -fno-omit-frame-pointer) 
else()
    # En Local (J'ai aussi enlevé les guillemets ici !)
    set(SANITIZER_FLAGS -fno-omit-frame-pointer -fsanitize=address -g) 
endif()

# --- 3. APPLICATION DES OPTIONS ---

# Pour les définitions (-D...)
target_compile_definitions(setr_tp2_daemonfuse PRIVATE _FILE_OFFSET_BITS=64)

# Pour les options (-Wall, -fsanitize...)
# Maintenant que WARNING_FLAGS est une liste (sans guillemets), ça va marcher.
target_compile_options(setr_tp2_daemonfuse PRIVATE 
    ${WARNING_FLAGS} 
    ${SANITIZER_FLAGS}
)

target_include_directories(setr_tp2_daemonfuse PRIVATE 
    "/usr/include/fuse"
)

# Pour le linker
target_link_options(setr_tp2_daemonfuse PRIVATE ${SANITIZER_FLAGS})

# Liaison FUSE
target_link_libraries(setr_tp2_daemonfuse fuse)