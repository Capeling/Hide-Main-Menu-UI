#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

struct HookMenuLayer : Modify<HookMenuLayer, MenuLayer> {
	struct Fields {
		bool m_isHidden = false;
		CCMenuItemToggler* m_eyeButton;
	};

	bool init() {
		if(!MenuLayer::init())
			return false;
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto on = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("eye_open.png"_spr), CircleBaseColor::Green, CircleBaseSize::Small);
		
		auto offEye = CCSprite::createWithSpriteFrameName("eye_closed.png"_spr);
		offEye->setOpacity(255 / 2.5);
		auto off = CircleButtonSprite::create(offEye, CircleBaseColor::Gray, CircleBaseSize::Small);
		off->setOpacity(255 / 2.5);

		m_fields->m_eyeButton = CCMenuItemToggler::create(on, off, this, menu_selector(HookMenuLayer::onToggleHide));
		m_fields->m_eyeButton->setID("hide-menu-button"_spr);
		
		auto menu = static_cast<CCMenu*>(getChildByID("top-right-menu"));

		menu->addChild(m_fields->m_eyeButton);
		menu->updateLayout();
		return true;
	}	

	void onToggleHide(CCObject* sender) {
		m_fields->m_isHidden = !m_fields->m_isHidden;
		HookMenuLayer::updateMenu();
	}

	void updateMenu() {
		CCObject* node;
		CCMenu* menu = static_cast<CCMenu*>(getChildByID("top-right-menu"));
		if(m_fields->m_isHidden) {
			CCARRAY_FOREACH(getChildren(), node) {
				auto node2 = static_cast<CCNode*>(node);
				
				if(node2->getID() != "main-menu-bg" && node2->getID() != "top-right-menu") {
					node2->setVisible(false);
				}
			}
			CCARRAY_FOREACH(menu->getChildren(), node) {
				auto node2 = static_cast<CCNode*>(node);

				log::debug("{}", node2->getID());

				if(node2->getID() != "hide-menu-button"_spr) {
					node2->setVisible(false);
				}
			}
		} else {
			CCARRAY_FOREACH(getChildren(), node) {
				auto node2 = static_cast<CCNode*>(node);
				node2->setVisible(true);
			}

			CCARRAY_FOREACH(menu->getChildren(), node) {
				auto node2 = static_cast<CCNode*>(node);
				node2->setVisible(true);
			}
		}
	}
};
