#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

struct HookedCharacterColorPage : geode::Modify<HookedCharacterColorPage, CharacterColorPage> {

	struct Fields {
		CCMenuItemSpriteExtra* player2GlowButton = nullptr;
	};

	static void onModify(auto&);
	$override void onPlayerColor(cocos2d::CCObject*);
	$override void createColorMenu();
	$override void onMode(cocos2d::CCObject*);
};
