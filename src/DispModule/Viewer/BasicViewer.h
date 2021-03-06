#ifndef BasicViewer_H
#define BasicViewer_H

#include <glew-1.11.0/include/GL/glew.h>
#include <QGLViewer/qglviewer.h>

class DispObject;

class BasicViewer : public QGLViewer
{
public:
  BasicViewer(QWidget *widget);
  BasicViewer();
  ~BasicViewer();

  void addDispObj(DispObject* disp_obj);
  void deleteDispObj(DispObject* disp_obj);
  void updateGLOutside();
  std::vector<DispObject *> get_dispObjects()
  {
	  return this->dispObjects;
  }
protected:
  virtual void draw();
  virtual void init();

  std::vector<DispObject *> dispObjects;
};

#endif