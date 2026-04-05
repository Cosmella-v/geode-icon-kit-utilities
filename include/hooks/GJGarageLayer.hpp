#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

struct HookedGJGarageLayer : geode::Modify<HookedGJGarageLayer, GJGarageLayer> {
	static void onModify(auto&);
	$override void showUnlockPopup(int, UnlockType) override;
	$override void onToggleItem(cocos2d::CCObject*);
	$override void onSelect(cocos2d::CCObject*);
	$override bool init() override;
	void onPlayerOptions(cocos2d::CCObject*);
	void createPlayerOptionsButton();
};
