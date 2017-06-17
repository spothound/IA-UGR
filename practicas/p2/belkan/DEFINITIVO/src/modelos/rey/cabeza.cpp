#include "modelos/rey/cabeza.hpp"

CabezaRey3D::CabezaRey3D(const std::string & filename) : Objeto3D(){

  //Colocamos la cara
  //setHijo(new Retrato3D(filename));
  //hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, -0.5, 0.0, 0.501));

  //Colocamos la cabeza
  setHijo(new CuboObj3D());
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.5, 0.0));
  hijos[0] -> setColor(_vertex3<float>(255.0/255.0, 153.0/255.0, 102.0/255.0));
  hijos[0] -> setAmb(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));
  hijos[0] -> setDiff(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));
  hijos[0] -> setSpec(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));

  //Colocamos el pelo
  setHijo(new CuboObj3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 1.1, 0.8, 1.1));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.8, -0.05));
  hijos[1] -> setColor(_vertex3<float>(255.0/255.0, 69.0/255.0, 0.0/255.0));
  hijos[1] -> setAmb(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[1] -> setDiff(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[1] -> setSpec(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));

  //Colocamos la corona
  setHijo(new CuboObj3D());
  hijos[2] -> setTranformacion(_vertex4<float>(Escalado_, 1, 0.12, 1));
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 9, 0));
  hijos[2] -> setColor(_vertex3<float>(205.0/255.0, 173.0/255.0, 0.0/255.0));
  hijos[2] -> setAmb(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[2] -> setDiff(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[2] -> setSpec(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));

  setHijo(new CuboObj3D());
  hijos[3] -> setTranformacion(_vertex4<float>(Escalado_, 0.12, 0.12, 0.12));
  hijos[3] -> setTranformacion(_vertex4<float>(Translacion_, -3.0, 10, 0));
  hijos[3] -> setColor(_vertex3<float>(205.0/255.0, 173.0/255.0, 0.0/255.0));
  hijos[3] -> setAmb(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[3] -> setDiff(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[3] -> setSpec(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));

  setHijo(new CuboObj3D());
  hijos[4] -> setTranformacion(_vertex4<float>(Escalado_, 0.12, 0.12, 0.12));
  hijos[4] -> setTranformacion(_vertex4<float>(Translacion_, 0, 10, 0));
  hijos[4] -> setColor(_vertex3<float>(205.0/255.0, 173.0/255.0, 0.0/255.0));
  hijos[4] -> setAmb(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[4] -> setDiff(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[4] -> setSpec(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));

  setHijo(new CuboObj3D());
  hijos[5] -> setTranformacion(_vertex4<float>(Escalado_, 0.12, 0.12, 0.12));
  hijos[5] -> setTranformacion(_vertex4<float>(Translacion_, 3.0, 10, 0));
  hijos[5] -> setColor(_vertex3<float>(205.0/255.0, 173.0/255.0, 0.0/255.0));
  hijos[5] -> setAmb(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[5] -> setDiff(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[5] -> setSpec(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));

}



CabezaRey3D::~CabezaRey3D(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
  delete hijos[3];
  delete hijos[4];
  delete hijos[5];
}
