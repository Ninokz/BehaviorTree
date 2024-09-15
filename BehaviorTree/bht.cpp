#include "BehaviorTree.h"

class MyDebugAction : public Nano::BehaviorTree::Action {
public:
	MyDebugAction(std::string uid) : Action(uid) {}
protected:
	Nano::BehaviorTree::Behavior::EStatus onUpdate() override {
		std::cout << "Action:" << m_uid << std::endl;
		return EStatus::Success;
	}
};

int main()
{
	Nano::BehaviorTree::BehaviorTreeBuilder::Ptr builder1 = std::make_shared<Nano::BehaviorTree::BehaviorTreeBuilder>();
	builder1->Repeat("1", 3)
				->Sequence("2")
					->Action(std::make_shared<MyDebugAction>("hello"))
					->Action(std::make_shared<MyDebugAction>("world"))
				->Back()
			->End();
	builder1->treeTick();	// / hello world hello world hello world

	Nano::BehaviorTree::BehaviorTreeBuilder::Ptr builder2 = std::make_shared<Nano::BehaviorTree::BehaviorTreeBuilder>();
	builder2->Sequence("RootSeq")
		->Selector("MainSelc")
			->Action(std::make_shared<MyDebugAction>("1"))
				->Action(std::make_shared<MyDebugAction>("2")) // 选择器下不执行
			->Back()
		->Parallel("ParallelTasks", Nano::BehaviorTree::Parallel::Policy::RequireAll, Nano::BehaviorTree::Parallel::Policy::RequireOne)
			->Action(std::make_shared<MyDebugAction>("3"))	
			->Action(std::make_shared<MyDebugAction>("4"))
			->Action(std::make_shared<MyDebugAction>("5"))
			->Action(std::make_shared<MyDebugAction>("6"))	// 全执行并行器
		->End();
	builder2->treeTick();	/// 1 3 4 5 6

	return 0;
}

