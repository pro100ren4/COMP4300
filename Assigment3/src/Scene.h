#pragma once

#include "EntityManager.h"
#include "Common.h"


// NOTE: raylib предоставляет простую, но достаточно функциональную систему
//       обработки ввода. Если добавилять систему "Actions & Replays" как это
//       описано здесь (https://www.youtube.com/watch?v=vWvRSiIOGmI&list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV&index=10)
//       , то в любом случае не получиться инкапсулировать систему ввода от
//       системы действий, т.к. при инициализации сцены мы в любом случае ука-
//       зываем завищащие от реализации клавиши, и то с какими действиями их 
//       надо связать. Поэтому по-моему мнению проще и быстрее использовать
//       встроенный механизм ввода в raylib
class Scene
{
  EntityManager m_eneities;
  bool m_paused = false;
  bool m_ended = false;

public:
  Scene();
  ~Scene();

  virtual void systemInput();
  virtual void systemUpdate();
  virtual void systemRender();
};
