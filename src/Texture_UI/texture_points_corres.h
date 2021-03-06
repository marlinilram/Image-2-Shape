#ifndef Texture_Mesh_Corres_H
#define Texture_Mesh_Corres_H
#include <QLabel>
#include <QString>
#include <QImage>
#include <QAction>
#include "color.h"
#include "PolygonMesh.h"
#include <opencv2/core/core.hpp>
class MiniTexture;
class PolygonMesh;
class QGLViewer;
class QMoveEvent;
class QMenu;
class TexSynHandler;
class Texture_Mesh_Corres: public QLabel
{
  Q_OBJECT

public:
	Texture_Mesh_Corres(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~Texture_Mesh_Corres();
public:
	void set_data(LG::PolygonMesh* mesh, 
		const std::vector<int>& m_face_selected, 
		const QImage& image, 
		const QString& file_dir, 
		QGLViewer*, 
		const cv::Mat& mask,
		TexSynHandler*
		);

	QString file_path();
	cv::Mat	get_mask_source();
	cv::Mat	get_mask_target();
	const std::vector<int>&	get_face_ids_in_mesh(){ return this->m_face_ids_in_mesh_; };

	void draw_line();
	void draw_points();

	void set_origin_image(const QImage& m);
	void set_mesh_image(const QImage& m);
	void set_masked_image(const QImage& m);

	void show_origin_image();
	void show_mesh_image();
	void show_masked_image();
	void set_show_mode(int m);
	static void generate_mask(TexSynHandler*, cv::Mat& mask);
	static void generate_mask_region(TexSynHandler*, QPoint p_selected,cv::Mat& mask);
	static void generate_mask_region(TexSynHandler*, int f_id, cv::Mat& mask);
	static void generate_mask_region(TexSynHandler*, int f_id, cv::Mat& mask, std::vector<int>& faces_region);
private:
	void set_image(const QImage&);
	void compute_mesh_center();
	void compute_faces_centers();
	void paintEvent(QPaintEvent * event);
	void moveEvent(QMoveEvent * event);

	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void timerEvent(QTimerEvent *);
	void dropEvent(QDropEvent * event);
	void creat_menu();

	

	QString m_image_file_;
	QImage  m_origin_image_;
	QImage  m_mesh_image_;
	QImage	m_masked_image_;
	bool	m_new_image_;
	int timer_id;

private:
	LG::PolygonMesh* m_mesh_;
	LG::Vec3	 m_mesh_center_;
	std::vector<int>	m_face_ids_in_mesh_;
	std::vector<LG::Vec3>	m_face_centers_;
	cv::Mat	   m_mask_source_;
	cv::Mat	   m_mask_target_;

	Colorf		m_color_;
	QGLViewer*	m_viewer_;

	int m_width_icon_;
	int m_height_icon_;

	bool m_left_button_;
	QPoint m_p_previous_;
	QMenu*	   m_menu_;
	
	int m_show_mode_;//0->origin, 1->mesh image, 2->masked image

	QLabel*	 m_label_full_image_;
	bool	 m_focus_on_;
private slots:
	void delete_this();
signals :
	void delete_coress(Texture_Mesh_Corres*);

};
#endif // !DispModuleHandler_H
