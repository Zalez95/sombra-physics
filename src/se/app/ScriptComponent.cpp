#include "se/app/ScriptComponent.h"
#include "se/app/events/EventManager.h"
#include "se/app/events/ScriptEvent.h"

namespace se::app {

	void ScriptComponent::setup(EventManager* eventManager, Entity entity)
	{
		mEventManager = eventManager;
		mEntity = entity;
	}


	void ScriptComponent::setScript(const ScriptRef& script)
	{
		if (mScript) {
			mEventManager->publish(new ScriptEvent(
				ScriptEvent::Operation::Remove, mEntity
			));
			mScript = ScriptRef();
		}
		if (script) {
			mEventManager->publish(new ScriptEvent(
				ScriptEvent::Operation::Add, mEntity
			));
			mScript = script;
		}
	}


	void ScriptComponent::onAdd(const ScriptSharedState& state)
	{
		if (mScript) {
			mScript->onAdd(mEntity, state);
		}
	}


	void ScriptComponent::onRemove(const ScriptSharedState& state)
	{
		if (mScript) {
			mScript->onRemove(mEntity, state);
		}
	}


	void ScriptComponent::onUpdate(float elapsedTime, const ScriptSharedState& state)
	{
		if (mScript) {
			mScript->onUpdate(mEntity, elapsedTime, state);
		}
	}

}