#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayerColor.hpp>

struct HookedCCLayerColor : geode::Modify<HookedCCLayerColor, cocos2d::CCLayerColor> {
	$override
	bool initWithColor(cocos2d::ccColor4B const& color, GLfloat width, GLfloat height) override;
};
