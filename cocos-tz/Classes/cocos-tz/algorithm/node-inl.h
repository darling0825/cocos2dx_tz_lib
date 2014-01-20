#pragma once

#include "../config.h"

NS_TZ_BEGIN

template<typename T>
inline T* find_nearest_node(
	cocos2d::Node* my_node,const std::vector<T*>& nodes,float length_max)
{
		float length_old = length_max;
		T* node = nullptr;
		auto my_pos = my_node->getPosition();
		for (auto c:nodes)
		{
			auto pos = c->getPosition();
			auto length = (pos - my_pos).getLength();
			if (length_old > length)
			{
				length_old = length;
				node = c;
			}
		}
		return node;
}

template<typename T>
inline T* find_nearest_node(
	cocos2d::Node* my_node,const std::vector<T*>& nodes)
{
		return find_nearest_node(my_node,nodes,FLT_MAX);
}

NS_TZ_END