#ifndef CABEZAREY3D_HPP
#define CABEZAREY3D_HPP

#include "obj3dlib.hpp"
#include "modelos/retrato.hpp"
#include <string.h>


class CabezaRey3D : public Objeto3D{
private:

public:
  CabezaRey3D(const std::string & filename);
  ~CabezaRey3D();

};

#endif
