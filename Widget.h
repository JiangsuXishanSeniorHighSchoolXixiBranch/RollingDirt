#ifndef WIDGET_H
#define WIDGET_H

#include "util/util.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_1_1>
#include <QOpenGLTexture>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

#include <QPropertyAnimation>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget, protected QOpenGLFunctions_1_1
{
    Q_OBJECT
    Q_PROPERTY(float angle READ angle WRITE setAngle)

public:
    Widget(QOpenGLWidget *parent = nullptr);
    ~Widget();

    qreal angle() const;
    void setAngle(const qreal &angle);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    void initialTexture();

    void initializeCubeData();

    void face();

    QOpenGLTexture *mTexture = nullptr;
    QImage *mTextureImage = nullptr;

    qreal mAngle = 60;
    QVector<gp::CubePoint> mData;

    Ui::Widget *ui;
};
#endif // WIDGET_H
