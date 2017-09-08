#pragma once

#include <vector>

#include "../physics/frustum.hpp"

#include "ISpatialObject.hpp"

namespace Flounder
{
	/// <summary>
	/// A data structure that stores objects with a notion of flounder.space.
	/// </summary>
	template<class t>
	class ISpatialStructure
	{
	public:
		/// <summary>
		/// Creates a new spatial structure.
		/// </summary>
		ISpatialStructure()
		{
		}

		/// <summary>
		/// Deconstructor for the spatial structure.
		/// </summary>
		virtual ~ISpatialStructure()
		{
		}

		/// <summary>
		/// Adds a new object to the spatial structure.
		/// </summary>
		/// <param name="object"> The object to add. </param>
		virtual void Add(t object) = 0;

		/// <summary>
		/// Removes an object from the spatial structure.
		/// </summary>
		/// <param name="object"> The object to remove. </param>
		virtual void Remove(t object) = 0;

		/// <summary>
		/// Removes all objects from the spatial structure..
		/// </summary>
		virtual void Clear() = 0;

		/// <summary>
		/// Gets the size of this structure.
		/// </summary>
		/// <returns> The structures size. </returns>
		virtual int GetSize() = 0;

		/// <summary>
		/// Returns a set of all objects in the spatial structure.
		/// </summary>
		/// </param>
		/// <returns> The list specified by of all objects. </returns>
		virtual std::vector<t> *GetAll() = 0;

		/// <summary>
		/// Returns a set of all objects in the spatial structure.
		/// </summary>
		/// <param name="result"> The list to store the data into.
		/// </param>
		/// <returns> The list specified by of all objects. </returns>
		virtual std::vector<t> *QueryAll(std::vector<t> *result) = 0;

		/// <summary>
		/// Returns a set of all objects in a specific range of the spatial structure.
		/// </summary>
		/// <param name="range"> The frustum range of space being queried. </param>
		/// <param name="result"> The list to store the data into.
		/// </param>
		/// <returns> The list of all object in range. </returns>
		virtual std::vector<t> *QueryFrustum(Frustum *range, std::vector<t> *result) = 0;

		/// <summary>
		/// Returns a set of all objects in a specific range of the spatial structure.
		/// </summary>
		/// <param name="range"> The shape range of space being queried. </param>
		/// <param name="result"> The list to store the data into.
		/// </param>
		/// <returns> The list of all object in range. </returns>
		virtual std::vector<t> *QueryBounding(ICollider *range, std::vector<t> *result) = 0;

		/// <summary>
		/// If the structure contains the object.
		/// </summary>
		/// <param name="object"> The object to check for.
		/// </param>
		/// <returns> If the structure contains the object. </returns>
		virtual bool Contains(ISpatialObject *object) = 0;
	};
}
