#include<iostream>
#include<queue>
#include <ctime>
#include <cstdlib>

#define SERVICE_TIME 100
#define NUMBER_OF_WINDOWS 5
#define TIME_UNIT 1
#define MAX_CUSTOMERS 8
#define MAX_SERVICE_TIMEUNIT 3
using namespace std;


class CUSTOM{
public:
	CUSTOM():serviced_time_unit(0), num(0), waited_start_time_unit(0)
	{

	}

	CUSTOM(int time, int serviced_time):serviced_time_unit(time), waited_start_time_unit(serviced_time), num(num_generator)
	{
		num_generator++;
	}

	int getWaitedTime() const
	{
		return serviced_time_unit;
	}

	int getWaitingTime() const
	{
		return waited_start_time_unit;
	}

	void decreaseTime()
	{
		--serviced_time_unit;
	}

	int getNum() const
	{
		return num;
	}
private:
	int serviced_time_unit;
	int num;
	static int num_generator;
	int waited_start_time_unit;
};

class SERVICE{
public:
	explicit SERVICE():total_time_unit(0), serviced_customers_amount(0), serviced_time(0)
	{
		for(size_t i=0; i<NUMBER_OF_WINDOWS; i++)
			windows_run[i]=false;
		for(size_t i=0; i<NUMBER_OF_WINDOWS; i++)
			windows_waited_time[i]=0;

	}

	int getServicedTime() const
	{
		 return serviced_time;
	}

	void print()
	{
		for(size_t i=0; i<NUMBER_OF_WINDOWS; i++)
		{
			cout<<i<<" windows are now "<<windows[i].getNum()<<", this customer waited for "<<windows_waited_time[i]<<" units"<<endl;
			cout<<"There are still "<<que[i].size()<<" customers in queue"<<endl;
			cout<<endl;
		}
	}

	void check()
	{

		for(size_t i=0; i<NUMBER_OF_WINDOWS; i++)

			if(serviced_time == SERVICE_TIME)
			{
				cout<<"average waited time is "<<total_time_unit/double(serviced_customers_amount)<<endl;
				exit(0);
			}
			serviced_time++;
		for(size_t i=0; i<NUMBER_OF_WINDOWS; i++)
			if(!windows_run[i] || windows[i].getWaitedTime()==1)
			{
				if(!que[i].empty())
				{
					CUSTOM temp = que[i].front();
					que[i].pop();
					windows_run[i] = true;
					windows[i] = temp;
					windows_waited_time[i] = serviced_time - temp.getWaitingTime();
					total_time_unit += windows_waited_time[i];
					serviced_customers_amount++;
				}
				else
				{
					windows_run[i] = false;
				}
			}
			else
			{
				windows[i].decreaseTime();
			}
	}

	void addCustomer(const CUSTOM& c)
	{
		for(size_t i=0; i<NUMBER_OF_WINDOWS; i++)
			if(!windows_run[i])
			{
				 windows_run[i] = true;
				 windows[i] = c;

				 return;
			}

		que[index_min_queue()].push(c);
	}

	int index_min_queue()
	{
		 int index = 0;
		 int min_size = que[0].size();
		 for(int i=0; i<NUMBER_OF_WINDOWS; i++)
		 {
			 if(que[i].size()<=min_size)
			 {
				  index = i;
				  min_size = que[i].size();
			 }
		 }
		 return index;
	}
private:
	queue<CUSTOM> que[5];
	CUSTOM windows[NUMBER_OF_WINDOWS];
	bool windows_run[NUMBER_OF_WINDOWS];
	int  windows_waited_time[NUMBER_OF_WINDOWS];
	int serviced_customers_amount;
	int serviced_time;
	int total_time_unit;


};

int CUSTOM::num_generator = 1;

int main()
{
	SERVICE service;
	srand(unsigned(time(0)));
	while(1)
	{

		sleep(TIME_UNIT);
		service.check();
		int rand_customer = rand() % MAX_CUSTOMERS + 1;
		srand(unsigned(time(0)));
		for(int i=0; i<rand_customer; i++)
		{
			int rand_waitingtime = rand() % MAX_SERVICE_TIMEUNIT +1;
			service.addCustomer(CUSTOM(rand_waitingtime, service.getServicedTime()));
		}
	system("clear");
	service.print();
	}
}


