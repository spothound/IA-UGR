#ifndef TORSOREY3D_HPP
#define TORSOREY3D_HPP

#include "obj3dlib.hpp"
#include "modelos/rey/cabeza.hpp"
#include "modelos/rey/brazo.hpp"
#include "modelos/rey/cintura.hpp"
#include <string.h>


class TorsoRey3D : public Objeto3D{
private:

public:
  TorsoRey3D(const std::string & filename);
  ~TorsoRey3D();

};

#endif
