#include "DYEngine/Scene.h"
#include "DYEngine/util/Logger.h"

#include <functional>

namespace DYE
{
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================

	Entity* IScene::CreateEntity()
	{
		std::unique_ptr<Entity> uniPtr = std::make_unique<Entity>(this);
		Entity* ptr = uniPtr.get();
		ptr->SetName("Entity(" + std::to_string(ptr->GetInstanceID()) + ")");

		m_EntityList.push_back(EntityListPair(ptr->GetInstanceID(), std::move(uniPtr)));

		return ptr;
	}

	Entity* IScene::CreateEntity(const std::string& _name)
	{
		std::unique_ptr<Entity> uniPtr = std::make_unique<Entity>(this, _name);
		Entity* ptr = uniPtr.get();

		m_EntityList.push_back(EntityListPair(ptr->GetInstanceID(), std::move(uniPtr)));

		return ptr;
	}

	SceneID IScene::GetSceneID() const
	{
		return m_SceneID;
	}

	std::string IScene::GetSceneName() const
	{
		return m_SceneName;
	}

	bool IScene::IsLoaded() const
	{
		return m_IsLoaded;
	}

	void IScene::load()
	{
		m_IsLoaded = true;
	}

	void IScene::release()
	{
		m_EntityList.clear();

		m_IsLoaded = false;
	}

	void IScene::removeEntity(InstanceID _id)
	{
		auto itr = std::find_if(m_EntityList.begin(), m_EntityList.end(), 
			[_id](const EntityListPair& element) { return element.first == _id; });

		if (itr != m_EntityList.end())
		{
			itr->second.reset();		// release entity
			m_EntityList.erase(itr);	// erase entry
		}
	}

	IScene::IScene()
	{

	}

	IScene::~IScene()
	{
		release();
	}

	//====================================================================================
	//	SceneManager: Used to manage scene operation
	//====================================================================================
	void SceneManager::LoadScene(SceneID id)
	{
		m_NextSceneID = id;
		m_IsLoadingNextScene = true;
	}

	void SceneManager::Init()
	{
		// TODO: init scene manager
	}

	void SceneManager::LoadNextScene()
	{
		loadScene(m_NextSceneID);
		m_IsLoadingNextScene = false;
	}

	IScene* SceneManager::loadScene(SceneID id)
	{
		LogInfo("Loading scene : (%3d)", id);
		IScene* currScene = getScene(m_CurrSceneID);
		if (currScene->IsLoaded())
			currScene->release();

		IScene* nextScene = getScene(id);
		nextScene->load();

		m_CurrSceneID = id;

		return nextScene;
	}

	IScene* SceneManager::getScene(SceneID id) const
	{
		assert(id < m_SceneIDCounter);

		return m_Scenes[id].second.get();
	}

	bool SceneManager::IsLoadingNextScene() const
	{
		return m_IsLoadingNextScene;
	}

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}
}