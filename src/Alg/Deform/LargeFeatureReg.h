#ifndef LARGE_FEATURE_REG_H
#define LARGE_FEATURE_REG_H

#include <vector>
#include "BasicHeader.h"

class MainCanvasViewer;
class FeatureGuided;
namespace LFReg {
  double efunc(const std::vector<double>&x, std::vector<double>& grad, void *func_data);
  double efuncNonRigid(const std::vector<double>&x, std::vector<double>& grad, void *func_data);
};

class LargeFeatureReg
{
public:
  LargeFeatureReg()
  : feature_model(nullptr), main_viewer(nullptr) {};
  ~LargeFeatureReg() {};

  void setFeatureModel(FeatureGuided* model) { feature_model = model; };

  void testNlopt();
  void runReg(int method_id = 0);
  void runRegNonRigid(int method_id = 0);

private:
  double energyFunc(const std::vector<double>& X);
  double modelRadius();

  double energyFuncNonRigid(const std::vector<double>& X);
  double energyScalarField(const std::vector<double>& X);
  double energyARAP(const std::vector<double>& X);
  void updateARAPRotation(const std::vector<double>& X);
  void updateARAPGrad(const std::vector<double>& X, std::vector<double>& grad);
  void updateARAPLMatrix(SparseMatrix& matrix);
  
  double energyFlat(const std::vector<double>& X);
  void updateFlatGrad(const std::vector<double>& X, std::vector<double>& grad);
  void updateFlatProj(const std::vector<double>& X);
  void updateFlatCoefs(std::vector<double>& coefs);
  double energyFlatNew(const std::vector<double>& X);
  void updateFlatGradNew(const std::vector<double>& X, std::vector<double>& grad);
  void updateFlatProjNew(const std::vector<double>& X);

  friend double LFReg::efunc(const std::vector<double>&x, std::vector<double>& grad, void *func_data);
  friend double LFReg::efuncNonRigid(const std::vector<double>&x, std::vector<double>& grad, void *func_data);

private:
  MainCanvasViewer* main_viewer;
  FeatureGuided*    feature_model;

  // internal variables for ARAP
  std::vector<Matrix3f> ARAP_R;
  Matrix3Xf P_init;
  SparseMatrix ARAP_L_matrix;
  double lamd_ARAP;

  // internal variables for Flatness
  std::vector<double> flat_coefs;
  Matrix3Xf P_plane_proj;
  std::vector<std::vector<int> > flat_vertices;
  std::vector<Matrix3Xf> P_plane_proj_new;
  double lamd_flat;

private:
  LargeFeatureReg(const LargeFeatureReg&);
  void operator=(const LargeFeatureReg&);
};


#endif // !LARGE_FEATURE_REG_H