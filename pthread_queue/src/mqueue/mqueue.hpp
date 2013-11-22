#include<iostream>
#include<vector>
#include<iterator>

#include "apr.h"

template<typename FileQueue>
class mqueue
{

public:
	virtual std::vector<FileQueue> pop() = 0;
	virtual void push(std::vector<FileQueue*> fileQueue) = 0;
	//virtual ~mqueue_controller();
};

template<typename FileQueue>
class mqueue_controller : public mqueue<FileQueue>, public std::iterator<std::input_iterator_tag, int>
{
	public:
		virtual std::vector<FileQueue> pop();
		virtual void push(std::vector<FileQueue> fileQueue);
//		virtual ~mqueue_controller();
	public:
		FileQueue * fqueue;	
		typedef struct apr_queue_t * queue; 
};
