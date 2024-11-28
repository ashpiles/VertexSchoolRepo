#include "Grid.h"
#include "Enemy.h"
#include "Player.h"
#include "matchit.h" 
using namespace matchit;

template<typename T>
CellSearch<T>::CellSearch() {}

template<typename T>
CellSearch<T>::~CellSearch() {}

template<typename T>
T* CellSearch<T>::operator()(list<int> indecies)
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
                items[match(itemType)
                    (
						pattern | as<Tile>(_)	= "Tile",
						pattern | as<Enemy>(_)	= "Enemy",
						pattern | as<Player>(_) = "Player",
						pattern | _				= "Item"
					)].push_back(itemPtr);
                result = items;
            }
        }
        else
        {
        }
        return *result;
	}

template<typename T>
T& CellSearch<T>::GetData() { return result; }
