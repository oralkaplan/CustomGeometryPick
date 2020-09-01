#include <QByteArray>
#include <QVector3D>
#include "customgeometry.h"

CustomGeometry::CustomGeometry()
{
    m_minVertex = new QVector3D();
    m_maxVertex = new QVector3D();

    m_vertices << QVector3D( -100.0f,-100.0f,-100.0f ) << QVector3D( -100.0f,-100.0f, 100.0f ) << QVector3D( -100.0f, 100.0f, 100.0f )
               << QVector3D( 100.0f, 100.0f,-100.0f ) << QVector3D( -100.0f,-100.0f,-100.0f ) << QVector3D( -100.0f, 100.0f,-100.0f )
               << QVector3D( 100.0f,-100.0f, 100.0f ) << QVector3D( -100.0f,-100.0f,-100.0f ) << QVector3D(100.0f,-100.0f,-100.0f  )
               << QVector3D( 100.0f, 100.0f,-100.0f ) << QVector3D( 100.0f,-100.0f,-100.0f ) << QVector3D( -100.0f,-100.0f,-100.0f )
               << QVector3D( -100.0f,-100.0f,-100.0f ) << QVector3D( -100.0f, 100.0f, 100.0f ) << QVector3D( -100.0f, 100.0f,-100.0f )
               << QVector3D( 100.0f,-100.0f, 100.0f ) << QVector3D( -100.0f,-100.0f, 100.0f ) << QVector3D( -100.0f,-100.0f,-100.0f )
               << QVector3D( -100.0f, 100.0f, 100.0f ) << QVector3D( -100.0f,-100.0f, 100.0f ) << QVector3D( 100.0f,-100.0f, 100.0f )
               << QVector3D( 100.0f, 100.0f, 100.0f ) << QVector3D( 100.0f,-100.0f,-100.0f ) << QVector3D( 100.0f, 100.0f,-100.0f )
               << QVector3D( 100.0f,-100.0f,-100.0f ) << QVector3D( 100.0f, 100.0f, 100.0f ) << QVector3D( 100.0f,-100.0f, 100.0f )
               << QVector3D( 100.0f, 100.0f, 100.0f ) << QVector3D( 100.0f, 100.0f,-100.0f ) << QVector3D( -100.0f, 100.0f,-100.0f )
               << QVector3D( 100.0f, 100.0f, 100.0f ) << QVector3D( -100.0f, 100.0f,-100.0f ) << QVector3D( -100.0f, 100.0f, 100.0f )
               << QVector3D( 100.0f, 100.0f, 100.0f ) << QVector3D( -100.0f, 100.0f, 100.0f ) << QVector3D( 100.0f,-100.0f, 100.0f );

    for( int i = 0; i < m_vertices.length(); i++ ) {
        m_indices.push_back( i );
    }

    addAttribute( Attribute::PositionSemantic, 0, Attribute::F32Type );
    addAttribute( Attribute::IndexSemantic, 0, Attribute::U32Type );
    addAttribute( Attribute::NormalSemantic, 0, Attribute::F32Type );
    setStride( sizeof ( QVector3D ) );
    setPrimitiveType( PrimitiveType::Triangles );
    rebuildGeometry();
}

void CustomGeometry::findBoundaries()
{
    float minX = 0, minY = 0, minZ = 0;
    float maxX = 0, maxY = 0, maxZ = 0;

    if( !m_vertices.length() ) {
        m_minVertex = new QVector3D();
        m_maxVertex = new QVector3D();
        return;
    }

    QVector< QVector3D >::iterator it;
    for( it = m_vertices.begin(); it != m_vertices.end(); ++it ) {
        if( it->x() <= minX )
            minX = it->x();
        if( it->y() <= minY )
            minY = it->y();
        if( it->z() <= minZ )
            minZ = it->z();

        if( it->x() > maxX )
            maxX = it->x();
        if( it->y() > maxY )
            maxY = it->y();
        if( it->z() > maxZ )
            maxZ = it->z();
    }

    m_minVertex = new QVector3D( minX, minY, minZ );
    m_maxVertex = new QVector3D( maxX, maxY, maxZ );
}

void CustomGeometry::rebuildGeometry()
{
    QByteArray vertices = QByteArray::fromRawData(
                reinterpret_cast< const char* >( m_vertices.data() ),
                sizeof( QVector3D ) * m_vertices.size() );

    QByteArray indices = QByteArray::fromRawData(
                reinterpret_cast< const char* >( m_indices.data() ),
                sizeof(  unsigned int ) * m_indices.size() );

    setVertexData( vertices );
    setIndexData( indices );
    findBoundaries();
    setBounds( *m_minVertex, *m_maxVertex );
}
