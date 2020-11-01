#include "../headers/App.h"

bool TodoList::app::open(const std::string& filename)
{
	reset();
	bool successful = true;
	std::ifstream fin(filename.c_str());
	if (!fin.is_open())
	{
		fin.open((filename + ".todo").c_str());
		if (!fin.is_open())
		{
			throw app_exception::file_open(filename);
			return false;
		}
		else
			this->filename = filename + ".todo";
	}
	else
		this->filename = filename;
	while (!fin.eof())
	{
		std::string line;  // 0 02032019 123 456 Text
		std::getline(fin, line, '\n');
		if (line.empty())
			continue;
		task::type ttype = task::type::t_std;
		if (line[0] == '1') // task::type::day
		{
			try
			{
				ttype = task::type::t_day;
				task::day* next_task = new task::day();

				unsigned long full_date = std::stoul(line.substr(2, 8));
				next_task->start(unsigned(full_date / 1000000UL), unsigned((full_date / 10000UL) % 100UL), unsigned(full_date % 10000UL));
				line = line.substr(11);

				next_task->title = line;

				//tasks.push_back(next_task);
				tasks.insert(get_before_date(next_task->start), next_task); // nearly-sorted
				tcount++;
			}
			catch (std::out_of_range)
			{
				throw app_exception::parsing(filename);
				successful = false;
				return false;
			}
		}
		else // task::type::std
		{
			try
			{
				ttype = task::type::t_std;
				task::std* next_task = new task::std();

				unsigned long full_date = std::stoul(line.substr(2, 8));
				next_task->start(unsigned(full_date / 1000000UL), unsigned((full_date / 10000UL) % 100UL), unsigned(full_date % 10000UL));
				line = line.substr(11);

				size_t space_pos = line.find_first_of(' ');
				unsigned long t_start = std::stoul(line.substr(0, space_pos));
				line = line.substr(space_pos + 1);
				space_pos = line.find_first_of(' ');
				unsigned long t_end = std::stoul(line.substr(0, space_pos));
				line = line.substr(space_pos + 1);
				next_task->set_start(time(unsigned(t_start)));
				next_task->set_end(time(unsigned(t_end)));

				next_task->title = line;

				//tasks.push_back(next_task);
				tasks.insert(get_before_date(next_task->start), next_task); // nearly-sorted
				tcount++;
			}
			catch (std::out_of_range)
			{
				throw app_exception::parsing(filename);
				successful = false;
				return false;
			}
		}
	}
	return successful;
}

bool TodoList::app::create(const std::string& flname)
{
	reset();
	std::string filename = flname + ".todo";
	std::ofstream fout(filename.c_str());
	tcount = 0;
	bool result = fout.is_open();
	if (!result)
	{
		throw app_exception::file_write(filename);
	}
	else
	{
		fout.close();
		this->filename = filename;
	}
	return result;
}

bool TodoList::app::save()
{
	std::ofstream fout(filename.c_str());
	if (!fout.is_open())
	{
		throw app_exception::file_write(filename);
		return false;
	}
	for (std::list<ctask*>::iterator i = tasks.begin(); i != tasks.end(); ++i)
	{
		(*i)->print(fout);
	}
	fout.close();
	return true;
}

std::list<TodoList::ctask*>::iterator TodoList::app::get_before_date(date d)
{
	std::list<ctask*>::iterator i, prev = tasks.begin();
	for (i = tasks.begin(); i != tasks.end(); ++i)
	{
		prev = i;
		if ((*i)->start > d)
			break;

	}
	return i;
}

TodoList::app::app()
{
	tcount = 0;
	filename = "";
}

TodoList::app::~app()
{
	reset();
}

bool TodoList::app::add(const std::string& title, task::type ttype, date start)
{
	ctask* next_task;
	if(ttype == task::type::t_std)
		next_task = new task::std(title, start);
	else
		next_task = new task::day(title, start);
	//tasks.push_back(next_task);
	tasks.insert(get_before_date(next_task->start), next_task);
	tcount++;
	return true;
}

bool TodoList::app::add(const std::string& title, date start, time t_start, time t_end)
{
	ctask* next_task = new task::std(title, start, t_start, t_end);
	//tasks.push_back(next_task);
	tasks.insert(get_before_date(next_task->start), next_task);
	tcount++;
	return true;
}

bool TodoList::app::add(const std::string& title, date start)
{
	ctask* next_task = new task::day(title, start);
	//tasks.push_back(next_task);
	tasks.insert(get_before_date(next_task->start), next_task);
	tcount++;
	return true;
}

bool TodoList::app::remove(ctask* t)
{
	return remove(t->get_uid());
}

bool TodoList::app::remove(unsigned uid)
{
	for (std::list<ctask*>::iterator i = tasks.begin(); i != tasks.end(); ++i)
	{
		if ((*i)->get_uid() == uid)
		{
			i = tasks.erase(i);
			tcount--;
			return true;
		}
	}
	throw app_exception::bad_uid(uid);
	return false;
}

void TodoList::app::print() const
{
	if (!tcount)
	{
		std::cout << "There is no tasks in this list.\n";
		return;
	}
	std::cout << "---------------------------------------------------------\n";
	std::list<ctask*>::const_iterator i = tasks.begin();
	for (; i != tasks.end(); ++i)
	{
		(*i)->print();
	}
	std::cout << "---------------------------------------------------------\n";
}

void TodoList::app::print(date d) const
{
	std::cout << "---------------------------------------------------------\n";
	int k = 0;
	std::list<ctask*>::const_iterator i = tasks.begin();
	for (; i != tasks.end(); ++i)
	{
		if ((*i)->start == d)
		{
			(*i)->print();
			k++;
		}
	}
	if (!k)
		std::cout << "There is no tasks on " << std::string(d) << ".\n";
	std::cout << "---------------------------------------------------------\n";
}

void TodoList::app::print(unsigned uid) const
{
	std::list<ctask*>::const_iterator i = tasks.begin();
	for (; i != tasks.end(); ++i)
	{
		if ((*i)->get_uid() == uid)
		{
			(*i)->print();
			return;
		}
	}
	throw app_exception::bad_uid(uid);
}

std::string TodoList::app::get_filename() const
{
	return filename;
}

void TodoList::app::start()
{
	std::cout << "TODO LIST (Vlasov Development)\n";
	std::cout << "1. Open list from file\n2. Create new list\n";
	int action = 1;
	do
	{
		if ((action < 1) || (action > 2))
			std::cout << "Wrong code. Try again: ";
		else
			std::cout << "Enter code of action: ";
		std::cin >> action;
	} while ((action < 1) || (action > 2));

	std::string tmp;
	int attempts = 0;
	switch (action)
	{
	case 1:
		std::cout << "Enter path to file: ";
		do
		{
			std::cin >> tmp;
			try
			{
				open(tmp);
				break;
			}
			catch (app_exception::file_open& e)
			{
				std::cout << "[ERROR] " << e.what() << " Try again: ";
			}
		} while (1);
		break;
	case 2:
		std::cout << "Enter list name (filename will be <your_name>.todo): ";
		do
		{
			std::cin >> tmp;
			try
			{
				create(tmp);
				break;
			}
			catch (app_exception::file_write& e)
			{
				std::cout << "[ERROR] " << e.what() << " Try again: ";
			}
			catch (app_exception::parsing& e)
			{
				std::cout << "[ERROR] " << e.what() << " Try again: ";
			}
		} while (1);
		break;
	}

	system("cls");
	std::cout << "TODO LIST :: " << this->filename << '\n';
	unsigned d, m, y, h;
	while (1)
	{
		std::cout << "1. Show tasks     2. Search tasks by date\n";
		std::cout << "3. Add new task   4. Delete task            5. Save & exit\n";
		action = 1;
		do
		{
			if ((action < 1) || (action > 5))
				std::cout << "Wrong code. Try again: ";
			else
				std::cout << "Enter code of action: ";
			std::cin >> action;
		} while ((action < 1) || (action > 5));

		date t_date;
		time t_start, t_end;
		std::string title;
		switch (action)
		{
		case 1:
			print();
			break;
		case 2:
			std::cout << "Enter day, month, year (separating with spaces): ";
			do
			{
				std::cin >> d >> m >> y;
				try
				{
					print(date(d, m, y));
					break;
				}
				catch (date_exception::bad_day& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
				catch (date_exception::bad_month& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
				catch (date_exception::bad_year& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
			} while (1);
			break;
		case 3:
			int type;
			type = 1;
			do
			{
				if ((type < 0) || (type > 2))
					std::cout << "Wrong type. Try again: ";
				else
					std::cout << "Enter type of task (1 - with start and end time, 2 - for whole day, 0 - cancel): ";
				std::cin >> type;
			} while ((type < 0) || (type > 2));
			if (type == 0)
			{
				std::cout << "Action cancelled.\n";
				break;
			}
			std::cout << "Enter day, month, year (separating with spaces): ";
			do
			{
				std::cin >> d >> m >> y;
				try
				{
					t_date(d, m, y);
					break;
				}
				catch (date_exception::bad_day& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
				catch (date_exception::bad_month& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
				catch (date_exception::bad_year& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
			} while (1);
			if (type == 1)
			{
				do
				{
					std::cout << "Enter hour, min of start (separating with spaces): ";
					do
					{
						std::cin >> h >> m;
						try
						{
							t_start(h, m);
							break;
						}
						catch (time_exception::bad_hour& e)
						{
							std::cout << "[ERROR] " << e.what() << " Try again: ";
						}
						catch (time_exception::bad_min& e)
						{
							std::cout << "[ERROR] " << e.what() << " Try again: ";
						}
					} while (1);
					std::cout << "Enter hour, min of end (separating with spaces): ";
					do
					{
						std::cin >> h >> m;
						try
						{
							t_end(h, m);
							break;
						}
						catch (time_exception::bad_hour& e)
						{
							std::cout << "[ERROR] " << e.what() << " Try again: ";
						}
						catch (time_exception::bad_min& e)
						{
							std::cout << "[ERROR] " << e.what() << " Try again: ";
						}
					} while (1);
					if (t_end < t_start)
						std::cout << "[ERROR] End time cannot be before start time. Try again.\n";
					else
						break;
				} while (1);
			}
			std::cout << "Enter title or description of task: ";
			getchar();
			getline(std::cin, title);
			if (type == 1)
				add(title, t_date, t_start, t_end);
			else
				add(title, t_date);
			std::cout << "Task added successfully.\n";
			break;
		case 4:
			unsigned uid;
			std::cout << "Enter uid of task you want to delete (0 - cancel): ";
			do
			{
				std::cin >> uid;
				if (uid == 0U)
				{
					std::cout << "Action cancelled.\n";
					break;
				}
				try
				{
					if (remove(uid))
						std::cout << "Task successfully deleted.\n";
					break;
				}
				catch (app_exception::bad_uid& e)
				{
					std::cout << "[ERROR] " << e.what() << " Try again: ";
				}
			} while (1);
			break;
		case 5:
			try
			{
				save();
				std::cout << "All changes saved. Have a nice day!\n";
				return;
			}
			catch (app_exception::file_write& e)
			{
				std::cout << "[ERROR] " << e.what() << '\n';
			}
			break;
		}
	}
}

void TodoList::app::reset()
{
	if (tcount > 0)
	{
		for (std::list<ctask*>::iterator i = tasks.begin(); i != tasks.end(); ++i)
			delete *i;
		tasks = std::list<ctask*>();
	}
	if (!filename.empty())
		filename = "";
	tcount = 0;
}

TodoList::app_exception::parsing::parsing(std::string value)       : exception_string("File can't be parsed because of syntax error.", value) {}
TodoList::app_exception::file_open::file_open(std::string value)   : exception_string("File can't be opened (it may not exist).", value)      {}
TodoList::app_exception::file_write::file_write(std::string value) : exception_string("File can't be overwritten (it may not exist).", value) {}
TodoList::app_exception::bad_uid::bad_uid(unsigned value)          : exception_uint("UID not found in this list.", value)                     {}