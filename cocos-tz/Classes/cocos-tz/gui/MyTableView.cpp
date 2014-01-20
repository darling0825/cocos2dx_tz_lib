#include "MyTableView.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_TZ_BEGIN

bool MyTableView::init() {
	Layer::init();
	_table_view = nullptr;
	_num = 0;
	_cell_size = Size::ZERO;
	_direction = ScrollView::Direction::HORIZONTAL;
	_fillOrder = TableView::VerticalFillOrder::BOTTOM_UP;
	return true;
}

void MyTableView::onEnter() {
	Layer::onEnter();
	_table_view = TableView::create(this,_table_size);
	_table_view->setPosition(_table_pos);
	_table_view->setDirection(_direction);
	_table_view->setVerticalFillOrder(_fillOrder);
	_table_view->setDelegate(this);
	this->addChild(_table_view);
	_table_view->reloadData();
}

void MyTableView::InitTable(const Point& table_pos,const Size& table_size) {
	_table_pos = table_pos;
	_table_size = table_size;
}

void MyTableView::setCellNum(int num) {
	_num = num;	
	if (_table_view != nullptr) {
		_table_view->reloadData();
	}
}
void MyTableView::setCellSize(const Size& cell_size) {
	_cell_size = cell_size;
	if (_table_view != nullptr) {
		_table_view->reloadData();
	}
}

void MyTableView::tableCellTouched(TableView* table, TableViewCell* cell) {
	if (_touch_fun) _touch_fun(cell);
}

Size MyTableView::tableCellSizeForIndex(TableView *table, ssize_t idx) {
	return _cell_size;
}

TableViewCell* MyTableView::tableCellAtIndex(TableView *table, ssize_t idx) {
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new TableViewCell;
		cell->autorelease(); 
		if (_if_fun) _if_fun(cell,idx);
	} else {
		if (_fun) cell->removeAllChildren();
		if (_else_fun) _else_fun(cell,idx);
	}
	if (_fun) _fun(cell,idx);
	return cell;
}

ssize_t MyTableView::numberOfCellsInTableView(TableView *table) {
	return _num;
}
NS_TZ_END