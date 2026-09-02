#pragma once

#include "Task.h"

#include "MyCPPUtils/data/EntityManager.h"

class TaskManager {
public:
	static bool loadTasks(Data::Manager<Task>& tasks);
	static bool saveTasks(const Data::Manager<Task>& tasks);
};