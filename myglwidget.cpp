#include "myglwidget.h"
#include<GL/glu.h>
#include<QKeyEvent>
#include<QTimer>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    fullscreen = false;
    m_filename = "C:/Users/jingyu zhou/Desktop/OpenGLQt/qt_opengl_particle/QtImage/Particle.bmp";

    m_slowdown = 2.0f;
    m_xvelocity = 0.0f;
    m_yvelocity = 0.0f;
    m_deepth = -40.f;

    for(int i = 0; i < PARTICLE_NUMBLE ; i++)
    {
        m_particle[i].life = 1.0f;
        m_particle[i].fade = float(rand()%100)/1000.0f + 0.001f;

        m_particle[i].x_pos = 0.0f;
        m_particle[i].y_pos = 0.0f;
        m_particle[i].z_pos = 0.0f;

        m_particle[i].x_vel = (float(rand()%50)-26.0f)*10.0f;
        m_particle[i].y_vel = (float(rand()%50)-25.0f)*10.0f;
        m_particle[i].z_vel = (float(rand()%50)-25.0f)*10.0f;

        m_particle[i].x_acc = 0.0f;
        m_particle[i].y_acc = -0.8f;
        m_particle[i].z_acc = 0.0f;
    }

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer->start(10);
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL()
{
    m_texture = bindTexture(QPixmap(m_filename));
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0, 0.0, 0.0, 0.0);                     //黑色背景
    glShadeModel(GL_SMOOTH);                              //启用阴影平滑
    glClearDepth(1.0);                                    //设置深度缓存

    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_DEPTH_TEST);                            //启用深度测试
    //glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glEnable(GL_BLEND);                                   //启用融合
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);                     //设置融合因子
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    //告诉系统对透视进行修正
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();                                   //重置投影矩阵
    //设置视口的大小
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();                                   //重置模型观察矩阵
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置模型观察矩阵
    glBindTexture(GL_TEXTURE_2D,m_texture);

    for(int i = 0; i < PARTICLE_NUMBLE; i++)
    {
        float x = m_particle[i].x_pos;
        float y = m_particle[i].y_pos;
        float z = m_particle[i].z_pos + m_deepth;

        //glColor4f(0.5f,0.5f,0.5f,m_particle[i].life);
        glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2d(1, 1); glVertex3f(x + 0.1f, y + 0.1f, z);
            glTexCoord2d(0, 1); glVertex3f(x - 0.1f, y + 0.1f, z);
            glTexCoord2d(1, 0); glVertex3f(x + 0.1f, y - 0.1f, z);
            glTexCoord2d(1, 1); glVertex3f(x - 0.1f, y - 0.1f, z);
        glEnd();

        m_particle[i].x_pos += m_particle[i].x_vel/(m_slowdown*1000.0);
        m_particle[i].y_pos += m_particle[i].y_vel/(m_slowdown*1000.0);
        m_particle[i].z_pos += m_particle[i].z_vel/(m_slowdown*1000.0);

        m_particle[i].x_vel += m_particle[i].x_acc;
        m_particle[i].y_vel += m_particle[i].y_acc;
        m_particle[i].z_vel += m_particle[i].z_acc;

        m_particle[i].life += m_particle[i].fade;

        if(m_particle[i].life < 0.0f)
        {
            m_particle[i].life = 1.0f;
            m_particle[i].fade = float(rand()%100)/1000.0f + 0.003f;

            m_particle[i].x_pos = 0.0f;
            m_particle[i].y_pos = 0.0f;
            m_particle[i].z_pos = 0.0f;

            m_particle[i].x_vel = m_xvelocity + float(rand()%60) - 30.0f;
            m_particle[i].y_vel = m_yvelocity + float(rand()%60) - 30.0f;
            m_particle[i].z_vel = float((rand()%60)-30.0f);

        }

    }
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    //F1为全屏和普通屏的切换键
    case Qt::Key_F1:
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        updateGL();
        break;
    //ESC为退出键
    case Qt::Key_Escape:
        close();
    case Qt::Key_Tab:
        for(int i = 0; i < PARTICLE_NUMBLE; i++)
        {
            m_particle[i].x_pos = 0.0f;
            m_particle[i].y_pos = 0.0f;
            m_particle[i].z_pos = 0.0f;

            m_particle[i].x_vel = m_xvelocity + (float(rand()%50)-26.0f)*10.0f;
            m_particle[i].y_vel = m_yvelocity + (float(rand()%50)-26.0f)*10.0f;
            m_particle[i].z_vel = m_zvelocity + (float(rand()%50)-26.0f)*10.0f;
        }
    }
}
