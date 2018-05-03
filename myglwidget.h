#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QGLWidget>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

protected:
    //对3个纯虚函数的重定义
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);           //处理键盘按下事件

private:
    bool fullscreen;                                //是否全屏显示
    QString m_filename;
    GLuint m_texture;

    static const int PARTICLE_NUMBLE = 100;

    float m_slowdown;
    float m_xvelocity;
    float m_yvelocity;
    float m_zvelocity;
    float m_deepth;

    struct PARTCLE
    {
        float life;
        float fade;
        float x_pos,y_pos,z_pos;
        float x_vel,y_vel,z_vel;
        float x_acc,y_acc,z_acc;
    }m_particle[PARTICLE_NUMBLE];
};

#endif // MYGLWIDGET_H
