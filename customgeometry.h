#ifndef CUSTOMGEOMETRY_H
#define CUSTOMGEOMETRY_H

#include <QQuick3DGeometry>
#include <QVector3D>
#include <QObject>

class CustomGeometry : public QQuick3DGeometry
{
    Q_OBJECT
public:
    CustomGeometry();

private:
    void rebuildGeometry();
    void findBoundaries();

    QVector< QVector3D > m_vertices;
    QVector< unsigned int > m_indices;
    QVector3D* m_minVertex;
    QVector3D* m_maxVertex;
};

#endif // CUSTOMGEOMETRY_H
