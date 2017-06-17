#ifndef REY3D_HPP
#define REY3D_HPP

#include "modelos/rey/torso.hpp"
#include "obj3dlib.hpp"
#include <string.h>


class Rey3D : public Objeto3D{
private:

public:
  Rey3D(const std::string & filename);
  ~Rey3D();

};

#endif
