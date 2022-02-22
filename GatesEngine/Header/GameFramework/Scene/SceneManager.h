#pragma once
#include "Scene.h"
#include <vector>

namespace GE
{
	class SceneManager
	{
	private:
		SceneInitializer sceneInitializer;
		std::vector<Scene*> scenes;
		Scene* currentScene;
		Scene* beforeScene;
		Scene* addScene;
	public:
		SceneManager();
		~SceneManager();
		void Initialize(const SceneInitializer& initializer);
		void Update(float deltaTime);
		void Draw();
		void LateDraw();
		void SetSceneInitializer(const SceneInitializer& sceneInitializer);

		Scene* AddScene(Scene* newScene);
		Scene* ChangeScene(const std::string& sceneName);
		Scene* GetCurrentScene();
		Scene* GetBeforeScene();
		Scene* GetAddScene();
		Scene* GetScene(const std::string& sceneName);
	};
}