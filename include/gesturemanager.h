#ifndef UGINE_IGESTURE_MANAGER_H
#define UGINE_IGESTURE_MANAGER_H

#include "event.h"

class IGestureManager {
public:
	virtual void ProcessEvent(CEvent* e) = 0;
};

class ClickManager : public IGestureManager {
public: 
	ClickManager(); 
	virtual void ProcessEvent(CEvent* e);
private: 
	bool m_onButtonDown; 
	time_t m_start;
	time_t m_stop;
};

class DoubleClickManager : public IGestureManager {
public:
	DoubleClickManager();
	virtual void ProcessEvent(CEvent* e);
private:
	bool m_onButtonDown;
	int m_count; 
	time_t m_start;
	time_t m_stop;
	time_t m_first;
	time_t m_last;
};

class DragManager : public IGestureManager {
public:
	DragManager();
	virtual void ProcessEvent(CEvent* e);
private:
	bool m_onButtonDown;
	bool m_onDragBegin;
};

#endif

