#include <Geode/loader/GameEvent.hpp>

#include <geode.devtools/include/API.hpp>

#include <constants.hpp>

$on_mod(Loaded) {
	devtools::waitForDevTools([] {
		devtools::registerNode<CharacterColorPage>([](CharacterColorPage* node) {
			devtools::label("Icon Kit Utilities\n");
			devtools::label(fmt::format("Current mode: {}", node->m_colorMode).c_str());
		});
		devtools::registerNode<ItemInfoPopup>([](ItemInfoPopup* node) {
			devtools::label("Icon Kit Utilities\n");
			devtools::label(fmt::format("Current type: {}", ICON_NAMES[static_cast<int>(node->m_unlockType)]).c_str());
			devtools::label(fmt::format("Current ID: {}", node->m_itemID).c_str());
		});
	});
}


