#pragma once

#include "DYEngine/Core.h"

#include <string>
#include <set>
#include <vector>
#include <list>

namespace DYE
{
	class Base;

	typedef unsigned int InstanceID;

	//====================================================================================
	//	NonCopyable: Restrict copy constructor and assign operator
	//====================================================================================
	class DYE_API NonCopyable
	{
	public:
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	//====================================================================================
	//	Base: Base class that component and entity are derived from
	//====================================================================================
	class DYE_API Base : public NonCopyable
	{
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static InstanceID s_nextInstantiateID;
		static std::set<Base*> s_instancesSet;
		static std::vector<Base*> s_toBeDestryoedList;

		bool m_IsToBeDestroyed = false;
		InstanceID m_InstanceID;
		std::string m_Name;
	public:
		//==========================================
		//	procedure
		//==========================================
		static void DestructionUpdate();					// Called at the end of the frame to destroy labelled base object in the destroyed set

		//==========================================
		//	method
		//==========================================
		static void Destroy(Base* _pBase);					// Mark this and its component to be destroyed at the end of the frame (delayed destruction)
		static Base* Instantiate(const Base* _pOriginal);	// TO DO: instantiate object (copy)
		template <class Type>
		static Base* FindObjectOfType()						// TO DO: Return a Base object of type Type
		{
			return nullptr;
		}
		template <class Type>
		static std::vector<Base*> FindObjectsOfType()		// TO DO: Return all Base objects of type Type TO DO
		{
			return nullptr;
		}
	protected:
		virtual void release() = 0;							// Need to be implemented for derived class, called on destruction loop

	public:
		//==========================================
		//	getter
		//==========================================
		int GetInstanceID() const { return m_InstanceID; }
		virtual std::string GetName() const { return m_Name; }

		//==========================================
		//	setter
		//==========================================
		virtual void SetName(const std::string& _name) { m_Name = _name; }

		//==========================================
		//	opeartor
		//==========================================
	public:
		inline bool operator==(const Base& other) const
		{
			return (other.m_InstanceID == this->m_InstanceID);
		}

		inline bool operator!=(const Base& other) const
		{
			return !operator==(other);
		}
		//==========================================
		//	constructor/destructor
		//==========================================
		Base();
		virtual ~Base();
	};
}