#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../config.h"

NS_TZ_BEGIN

class MyTableView :public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate {
public:
	virtual bool init();
	virtual void onEnter();
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

	// init
	void InitTable(const cocos2d::Point& table_pos,const cocos2d::Size& table_size);
	void setCellNum(int num);
	int getCellNum() { return _num; }
	void setCellSize(const cocos2d::Size& cell_size);

	void setCreateCell(std::function<void(cocos2d::extension::TableViewCell*,int)> if_fun) { _if_fun = if_fun; }
	void setAdjustCell(std::function<void(cocos2d::extension::TableViewCell*,int)> else_fun) { _else_fun = else_fun; }

	void setFunCell(std::function<void(cocos2d::extension::TableViewCell*,int)> fun) { _fun = fun; }

	void setTouchCell(std::function<void(cocos2d::extension::TableViewCell*)> touch_fun) { _touch_fun = touch_fun; }
	void reloadData() { _table_view->reloadData(); }
	// ----
	void setDirection(cocos2d::extension::TableView::Direction eDirection) { _direction = eDirection; }
	void setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder fillOrder) { _fillOrder = fillOrder; }

	CREATE_FUNC(MyTableView);

private:
	int _num;
	cocos2d::Size _cell_size;
	cocos2d::Size _table_size;
	cocos2d::extension::TableView* _table_view;
	cocos2d::Point _table_pos;
	std::function<void(cocos2d::extension::TableViewCell*,int)> _if_fun;
	std::function<void(cocos2d::extension::TableViewCell*,int)> _else_fun;
	std::function<void(cocos2d::extension::TableViewCell*)> _touch_fun;
	std::function<void(cocos2d::extension::TableViewCell*,int)> _fun;
	cocos2d::extension::TableView::Direction _direction;
	cocos2d::extension::TableView::VerticalFillOrder _fillOrder;
};
NS_TZ_END