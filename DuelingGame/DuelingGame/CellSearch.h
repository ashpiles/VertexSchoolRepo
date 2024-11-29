#pragma once

#include <map>
#include <list>
#include <vector>
#include <string>
#include "GridItem.h"
#include "matchit.h"
#include "Player.h"
#include "Enemy.h"
using namespace matchit;

using flat_items = std::list<GridItem*>;
using vector_items = std::vector<std::list<GridItem*> >;
using mapped_items = std::map<std::string, std::list<GridItem*> >; 

template<typename T>
struct CellSearch
{
	CellSearch() {}
	~CellSearch() {}
	T& operator()(std::list<int> indecies)
	{
		if constexpr (std::is_same_v<T, flat_items>)
		{
			flat_items items;
			for (int i : indecies)
				items.push_back(Grid::GetItem(i)); 
			result = items;
		}
		else if constexpr (std::is_same_v<T, vector_items>)
		{
			// Handle vector_items type
		}
		else if constexpr (std::is_same_v<T, mapped_items>)
		{
			GridItem* item;
			mapped_items items;

			for (int index : indecies)
			{
				GridItem* itemPtr = Grid::GetItem(index);
				GridItem const& itemType = *itemPtr;
				result[match(itemType)
					(
						pattern | as<Tile>(_)	= "Tile",
						pattern | as<Enemy>(_)	= "Enemy",
						pattern | as<Player>(_) = "Player",
						pattern | _				= "Item"
					)].push_back(itemPtr);
			}
		}
		else
		{
		}
		return result;
	}

	
	T& GetData() { return result; }
private:
	T result;
};

