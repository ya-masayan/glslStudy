#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

#if 0
void
Camera::addViewport( Viewport* viewport )
{
	m_ViewportList.push_back( viewport );
}
#endif

Viewport*
Camera::addViewport( const Viewport::ViewportInfo& arg )
{
	Viewport* viewport = new Viewport( arg );
	m_ViewportList.push_back( viewport );
	return viewport;
}

void
Camera::removeViewport( Viewport* viewport )
{
	for( std::list< Viewport* >::iterator it = m_ViewportList.begin();
		it != m_ViewportList.end();
		++it )
	{
		if( viewport == *it )
		{
			m_ViewportList.erase( it );
			delete viewport;
			return;
		}
	}
}

void
Camera::update()
{
    //Å@íPà çsóÒê∂ê¨
    m_ProjViewMtx = glm::mat4();

    auto view_matrix = glm::lookAt( m_Eye, m_At, m_Up );
    auto proj_matrix = glm::perspective( m_Fovy, m_Aspect, m_Near, m_Far );
    m_ProjViewMtx = proj_matrix * view_matrix;
}

