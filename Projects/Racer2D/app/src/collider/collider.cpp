//------------------------------------------------------------------
//
// Collider Implementation (Finds collision between objects)
//
//------------------------------------------------------------------
#include "collider\collider.h"
#include "collider\geomintersector.h"
#include "collider\topointersector.h"

Collider::Collider()
{
}

Collider::~Collider()
{
	m_objects.clear();
}

void Collider::AddObject(const std::shared_ptr<Object>& pObject)
{
	m_objects.push_back(pObject);
}

bool Collider::FindCollision()
{
	int len = (int)m_objects.size();

	// This logic can be fined tunned
	for (int i = 0; i < len; ++i)
	{
		const std::shared_ptr<Object>& pObj1 = m_objects[i];
		for (int j = i + 1; j < len; ++j)
		{
			const std::shared_ptr<Object>& pObj2 = m_objects[j];

			bool bRes = GeomIntersector::Intersect(pObj1->m_objBody->m_boxGeom.get(), pObj2->m_objBody->m_boxGeom.get());
			if (bRes == false)
				continue;

			// Now find the collision between each objects
			TopoIntersector intersector;
			bRes = intersector.Intersect(pObj1->m_objBody, pObj2->m_objBody);
			if (bRes == false)
				continue;

			int len = (int)intersector.m_intersectingTopos.size();
			for (int i = 0; i < len; ++i)
			{
				const std::shared_ptr<data::Topo>& pTopo = intersector.m_intersectingTopos[i];
				long id = pTopo->m_id;

				if (pObj1->m_objectId == id)
					pObj1->AddCollideTopo(pTopo);
				else if (pObj2->m_objectId == id)
					pObj2->AddCollideTopo(pTopo);
			}
		}
	}
	return true;
}