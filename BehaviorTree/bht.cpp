#include "BehaviorTree.h"


int main()
{
	Nano::BehaviorTree::BehaviorTreeBuilder::Ptr builder = std::make_shared<Nano::BehaviorTree::BehaviorTreeBuilder>();
	builder->Repeat("1", 3)
				->Sequence("2")
					->DebugNode("hello")
					->DebugNode("world")
				->Back()
			->End();
	builder->treeTick();
	return 0;
}