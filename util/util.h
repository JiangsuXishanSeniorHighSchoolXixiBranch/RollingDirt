#ifndef UTIL_H
#define UTIL_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

namespace gp{

    struct CubePoint {
        QVector3D posCoord;
        QVector2D textureCoord;
        CubePoint(const QVector3D &position = QVector3D(),
                const QVector2D &texture = QVector2D()):
                posCoord(position), textureCoord(texture)
        {}

    };

    struct HyperCubePoint {
        QVector4D posCoord;
        HyperCubePoint(const QVector4D &position = QVector4D()):
            posCoord(position)
        {}
    };

}
#endif // UTIL_H
