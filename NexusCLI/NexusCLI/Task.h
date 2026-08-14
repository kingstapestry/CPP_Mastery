#pragma once

#include "MyCPPUtils/data/EntityManager.h"

#include <string>
#include <ctime>

enum class Priority { Low, Medium, High };
enum class Status { Pending, Completed };

class Task {
private:
	int _id;
	std::string _title;
	std::string _description;
	Priority _priority;
	Status _status;
	std::time_t _createdAt;
	static int _nextId;

public:
	Task(const std::string& title);

	int getId() const;
	std::string getTitle() const; 
	std::string getDescription() const;
	Priority getPriority() const;
	Status getStatus() const;
	std::time_t getCreatedAt() const;

	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
	void setPriority(Priority priority);
	void setStatus(Status status);

	std::string priorityToString(Priority priority) const;
	std::string statusToString(Status status) const;
	void displayTask() const;

	static void displayAllTasks(const Data::Manager<Task>& tasks);
};