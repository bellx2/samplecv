cmake_minimum_required(VERSION 2.8.12)

project( samplecv ) ##プロジェクト名をいれる
set(SOURCE_FILE main.cpp) ##ファイル名を適宜書き換えること．
 
find_package(OpenCV REQUIRED) ##OpenCVのビルド環境の設定ファイルを読み込む
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB glib-2.0 REQUIRED)

##OpenCV関係のインクルードディレクトリのパスを設定
include_directories(
  ${OpenCV_INCLUDE_DIRS},
  ${GLIB_INCLUDE_DIRS},
  ./include
)

link_directories(
  ${GLIB_LIBRARY_DIRS}
)

##実行ファイル名を設定
add_executable(
  ${PROJECT_NAME} ${SOURCE_FILE}
)


##リンクするライブラリを読み込む
target_link_libraries(
  ${PROJECT_NAME} 
  ${OpenCV_LIBRARIES}
  ${GLIB_LIBRARIES}
)