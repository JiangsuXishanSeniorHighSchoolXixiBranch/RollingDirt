#include "Widget.h"
#include "ui_widget.h"

Widget::Widget(QOpenGLWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions_1_1()
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSurfaceFormat fmt = format();
        fmt.setSamples(25);
        setFormat(fmt);

        setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowIcon(QIcon(":/dirt.png"));


        QPropertyAnimation *animation = new QPropertyAnimation(this);
        animation->setTargetObject(this);
        animation->setPropertyName("angle");
        animation->setStartValue(0);
        animation->setEndValue(359);
        animation->setDuration(5000);
        animation->setLoopCount(-1);
        animation->setEasingCurve(QEasingCurve::InCubic);
        animation->start();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    if (!initializeOpenGLFunctions())
    {
        qDebug() << "init opengl functions failed";
    }
    initialTexture();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glCullFace(GL_BACK);


    initializeCubeData();

    glClearColor(0, 0, 0, 0);
}

void Widget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width(), height());


    glLoadIdentity();

    face();

    if(mTexture)
    {
        mTexture->bind();
    }

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for(const gp::CubePoint &point: mData) {
        glTexCoord2d(point.textureCoord.x(), point.textureCoord.y());
        glVertex3f(point.posCoord.x(), point.posCoord.y(), point.posCoord.z());
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Widget::resizeGL(int w, int h)
{
    qDebug() << w << h;
}

void Widget::initialTexture()
{
    mTextureImage = new QImage(":/dirt.png");
    mTexture = new QOpenGLTexture(mTextureImage->mirrored());

    mTexture->setMinificationFilter(QOpenGLTexture::NearestMipMapNearest);
    mTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
}

void Widget::initializeCubeData()
{
    mData = {

        {{-0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5,  0.5}, {0, 1}},

        {{-0.5,  0.5,  0.5}, {0, 0}},        {{ 0.5,  0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        {{-0.5,  0.5, -0.5}, {0, 0}},        {{ 0.5,  0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5, -0.5}, {1, 1}},        {{-0.5, -0.5, -0.5}, {0, 1}},

        {{-0.5, -0.5, -0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5,  0.5}, {1, 1}},        {{-0.5, -0.5,  0.5}, {0, 1}},

        {{-0.5, -0.5, -0.5}, {0, 0}},        {{-0.5, -0.5,  0.5}, {1, 0}},
        {{-0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        {{ 0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{ 0.5,  0.5,  0.5}, {0, 1}},
    };
}

qreal Widget::angle() const
{
    return mAngle;
}

void Widget::setAngle(const qreal &angle)
{
    mAngle = angle;
    this->update();
}

void Widget::mousePressEvent(QMouseEvent *event){
#ifdef Q_OS_WIN
    if (ReleaseCapture())
        SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    event->ignore();
#else
#endif
}

void Widget::face(){
    int mx = QCursor::pos().x();
    int my = QCursor::pos().y();

    int wx = geometry().x() + (rect().x()/2);
    int wy = geometry().y() + (rect().y()/2);

    if (wx > mx){
        glRotatef(mAngle, 0.0, -0.01, 0.0);
    }
    else{
        glRotatef(mAngle, 0.0, 0.01, 0.0);
    }

    if (wy > my){
        glRotatef(mAngle, 0.0, 0.0, -0.01);
    }
    else{
        glRotatef(mAngle, 0.0, 0.0, 0.01);
    }

}

void Widget::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton){
        QApplication::exit();
    }
}



