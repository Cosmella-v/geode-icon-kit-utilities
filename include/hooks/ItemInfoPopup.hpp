#pragma once

#include<Geode/Geode.hpp>
#include<Geode/modify/ItemInfoPopup.hpp>

struct HookedItemInfoPopup : geode::Modify<HookedItemInfoPopup, ItemInfoPopup> {

	using CCLayerColor::init;

	$override
	bool init(int, UnlockType);

	cocos2d::CCLabelBMFont* addAchievementLabel(const char*);
	TextArea* addDescriptionArea(const char*);
	const char* pickRandomLabel();
	const char* pickRandomAchievementLabel();
	cocos2d::CCLabelBMFont* addRandomLabel(const char*);

};
