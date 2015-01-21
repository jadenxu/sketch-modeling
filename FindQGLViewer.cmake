# - Find libQGLViewer
# libQGLViewer is a C++ library based on Qt that eases
# the creation of OpenGL 3D viewers.
# http://www.libqglviewer.com/
#
# This module defines the following variables
#  QGLVIEWER_FOUND       - system has libQGLViewer
#  QGLVIEWER_INCLUDE_DIR - where the libQGLViewer include directory can be found
#  QGLVIEWER_LIBRARY     - link to this to use libQGLViewer


FIND_PATH(QGLVIEWER_INCLUDE_DIR 
    NAMES QGLViewer/qglviewer.h
    PATHS /usr/include
          /usr/local/include
          /usr/local/Cellar/libqglviewer/2.5.1
)

FIND_LIBRARY(QGLVIEWER_LIBRARY
  NAMES qglviewer-qt4 QGLViewer QGLViewer2
  PATHS /usr/lib
        /usr/local/lib
)

INCLUDE(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libQGLViewer DEFAULT_MSG
  QGLVIEWER_LIBRARY QGLVIEWER_INCLUDE_DIR)

MARK_AS_ADVANCED(QGLVIEWER_INCLUDE_DIR QGLVIEWER_LIBRARY)
