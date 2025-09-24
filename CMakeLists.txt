cmake_minimum_required(VERSION 3.20)
project(ResourceMonitor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем include и lib для spdlog, если не используется find_package
# include_directories(/home/jahongir/spdlog/include)
# link_directories(/home/jahongir/spdlog/build)

# Если spdlog уже установлен или через vcpkg:
set(spdlog_DIR "/home/jahongir/spdlog/build")
find_package(spdlog REQUIRED)

# Добавляем исходники
add_executable(main
    src/main.cpp
)

# Линкуем с spdlog и pthread
target_link_libraries(main PRIVATE spdlog::spdlog pthread)
