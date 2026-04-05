#pragma once

#include <Geode/Geode.hpp>

class PlayerOptionsPopup : public geode::Popup {
protected:

	cocos2d::CCMenu *m_buttonMenu;

	void toggleOption(cocos2d::CCObject *sender);

	void addOption(const char*, int);
	void addOptionInfo(int, const char*);
	bool init();

public:
	static PlayerOptionsPopup* create();
};

