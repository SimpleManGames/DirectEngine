#ifndef _UOBJECT_H
	#define _UOBJECT_H

// Additional Includes
#ifndef _CONTEXT_H
	#include "Context.h"
#endif
#ifndef _STRING_H
	#include "string.h" 
#endif
#ifndef _OBJECTCOUNTER_H
	#include "ObjectCounter.h"
#endif // !_OBJECTCOUNTER_H
#ifndef _SINGLETON_H
	#include "Singleton.h"
#endif // !_SINGLETON_H
#ifndef _TYPECHECKER_H
	#include "TypeChecker.h"
#endif // !_TYPECHECKER_H

/// Struct

// Holds the data for each BaseObject
struct ObjectData {
	// Default ObjectData Construtor
	ObjectData() 
		: name(_T(""))
	{}
	// ObjectData Construtor
	// param: n = The name for the object data
	ObjectData(const std::tstring& n) 
		: name(n)
	{}

	//void* operator new(size_t size);
	//void operator delete(void * pdelete);

	// Name of the object data
	std::tstring name;
};

// Define
// Register type inside typechecker
#define TYPE_REGISTER(class_type_id)\
	Singleton<TypeChecker>::GetInstance(true)->AddType(GetID(), _T(#class_type_id))
// Init class type hardcode methods
#define TYPE_INIT(class_type_id)\
	virtual std::tstring GetTypeID() const { return _T(#class_type_id); }\
	static std::tstring GetClassTypeID()  { return _T(#class_type_id); }

class BaseObject : public ObjectCounter<BaseObject>
{
	// Init Type Checker
	TYPE_INIT(BaseObject)

public:
	/// Construtor & Deconstrutor

	// Default BaseObject Construtor
	BaseObject();
	// BaseObject Construtor
	// param: data = takes the name and sets the ObjectData Name
	BaseObject(ObjectData* data);
	BaseObject(const std::tstring& name);
	virtual ~BaseObject();

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	virtual bool Initialize() { m_bIsInitialized = true; return true; }
	virtual bool PostInitialize() {m_bIsPostInitialized = true; return true; }
	virtual bool LoadContent() { m_bIsContentLoaded = true; return true; }
	virtual bool PostLoadContent() {m_bIsPostContentLoaded = true; return true; }
	virtual bool Update(Context& context) { return true; }
	//virtual bool LateUpdate(Context& context) { return true; }
	virtual bool Draw(Context& context)	{ return true; }
	virtual bool DrawUI(Context& context) { return true; }
	virtual bool ShutDown()	{ return true; }

	virtual void Reset();

	void SetName(const std::tstring& name) { m_Name = name; }
	const std::tstring& GetName() { return m_Name; }

	bool IsInitialized() const { return m_bIsInitialized; }
	bool IsPostInitialized() const { return m_bIsPostInitialized; }
	bool IsContentLoaded() const { return m_bIsContentLoaded; }
	bool IsPostContentLoaded() const { return m_bIsPostContentLoaded; }

	void SetCanTick(bool canTick) { m_bCanTick = canTick; }
	bool CanTick() const { return m_bCanTick; }
	void SetCanDraw(bool canDraw) { m_bCanDraw = canDraw; }
	bool CanDraw() const { return m_bCanDraw; }

	void Destory() { m_bIsDestoryed = true; }
	bool IsDestroyed() const { return m_bIsDestoryed; }

	void Activate() { m_bIsActivated = true; }
	void Deactivate() { m_bIsActivated = false; }
	bool IsActivate() { return m_bIsActivated; }

	template<typename T>
	T* GetObjectData() { return static_cast<T*>(m_pdata); }

	ObjectData* GetRawObjectData() { return m_pdata; }

	int GetID() { return m_ID; }
	int GetObjectAmount() { return ObjectCounter<BaseObject>::GetAmount(); }
	bool isType(const std::tstring& type);
	bool isA(const std::tstring& type);

protected:
	int m_ID;

	bool m_bIsInitialized;
	bool m_bIsPostInitialized;

	bool m_bIsContentLoaded;
	bool m_bIsPostContentLoaded;

	std::tstring m_Name;

	ObjectData* m_pdata;

private:
	bool m_bIsActivated;
	bool m_bIsDestoryed;

	bool m_bCanTick;
	bool m_bCanDraw;
};

#endif // !_UOBJECT_H