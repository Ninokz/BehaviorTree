# BehaviorTree - 轻量级行为树库

## Intro.

Nano::BehaviorTree 是一个用C++实现的轻量级行为树库，供学习。

## Main Features.

- 支持基本的行为树节点类型：序列（Sequence）、选择器（Selector）、并行（Parallel）等
- 提供装饰器节点：反转器（Inverter）、重复器（Repeat）等
- 包含复合节点：过滤器（Filter）、活动选择器（ActiveSelector）、监视器（Monitor）等
- 使用智能指针进行内存管理
- 支持行为树构建器模式，方便快速构建复杂的行为树

## Core Class.

- `Behavior`: 所有行为节点的基类
- `Composite`: 复合节点的基类，可以包含多个子节点
- `Decorator`: 装饰器节点的基类，只包含一个子节点
- `Action`: 叶节点，执行具体的行为
- `BehaviorTree`: 整个行为树的容器和执行器
- `BehaviorTreeBuilder`: 用于方便地构建行为树的工具类

## Use Example.

```cpp
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
```

## Advanced Use.

- 使用 `Filter` 节点组合条件和动作
- 利用 `ActiveSelector` 实现动态切换的行为
- 通过 `Monitor` 节点同时执行条件检查和动作

## Attention.

- 确保正确管理内存，推荐使用智能指针
- 复杂的行为树可能影响性能，请适当优化结构
- 自定义节点时，确保正确实现 `onUpdate()` 方法

## Ref.

- [OwlCat](https://www.cnblogs.com/OwlCat/p/17871494.html)