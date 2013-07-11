#include <iostream>

template<typename WorkTypes>
struct workload{
	WorkTypes work_groups;
	WorkTypes work_items;
};

template<typename WorkTypes, typename IndexTypes>
class cal_workload
{

public:
		cal_workload();
		void init_workload(WorkTypes &  worktypes);
private:
WorkTypes * work;

IndexTypes * groups;
IndexTypes * items;
};

template<typename WorkTypes, typename IndexTypes>
cal_workload<WorkTypes, IndexTypes>::cal_workload(){  }

template<typename WorkTypes, typename IndexTypes>
void cal_workload<WorkTypes,IndexTypes>::init_workload(WorkTypes & worktypes)
{
	work->work_groups = worktypes.work_groups;
	work->work_items  = worktypes.work_items;
	IndexTypes index_groupitems[work->work_groups][work->work_groups];
  for(int seed_count = 0; seed_count < work->work_groups; seed_count++)
	{
			index_groupitems[seed_count][seed_count] = seed_count;
	}

  for(int seed_count = 0; seed_count < work->work_groups; seed_count++)
	{
			std::cout<<"Data in [ "<< seed_count <<" ] : " << index_groupitems[seed_count][seed_count] <<std::endl;
	}

	
}

template<typename WorkTypes>
struct workload;	

int main()
{
	cal_workload<workload<int>,int> work_engine;
	workload<int> workset;
	workset.work_groups = 10;
	workset.work_items  = 10;
	work_engine.init_workload(workset);

}
