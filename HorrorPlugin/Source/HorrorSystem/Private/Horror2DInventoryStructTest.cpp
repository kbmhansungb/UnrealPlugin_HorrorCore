// 2022 07    Bum moo, Kim

#include "Horror2DInventoryStruct.h"
#include "HorrorItem.h"

#if WITH_EDITOR

#include "Misc/AutomationTest.h"
#include <string>
#include <vector>

using DesireTestResult = bool;
using InventorySize = FIntSize2D;
using ItemSize = FIntSize2D;
using ItemStackSize = int;
using InsertIndex = FIntPoint;

enum class ACTION
{
	NONE,
	STORE,
	TAKE,
};

struct WorkUnit
{
	WorkUnit() = default;
	WorkUnit(const FIntPoint& Index, ACTION Action)
		: Index(Index), Action(Action) 
	{
	}

	FIntPoint Index;
	ACTION Action;
};

namespace INSERT_TEST
{
	struct InsertTestCase
	{
		InsertTestCase(
			const FString& What, bool Desire, 
			const FIntSize2D& InventorySize, 
			const FIntSize2D& ItemSize, int32 ItemStackSize, 
			const std::vector<WorkUnit>& Works
		) : 
			What(What), Desire(Desire),
			InventorySize(InventorySize), 
			ItemSize(ItemSize), ItemStackSize(ItemStackSize),
			Works(Works)
		{
		}

		FString What;
		bool Desire;

		FIntSize2D InventorySize;
		FIntSize2D ItemSize;
		int32 ItemStackSize;

		std::vector<WorkUnit> Works;

		bool Test() const
		{
			UHorrorItem* Item = NewObject<UHorrorItem>();
			Item->Name = FName("TestItem");
			Item->Size = ItemSize;
			Item->StackSize = ItemStackSize;

			F2DInventoryStruct Inventory;
			Inventory.InventorySize = InventorySize;

			//bool Result = true;

			for (const auto& Work : Works)
			{
				switch (Work.Action)
				{
				case ACTION::STORE:
				{
					if (Inventory.TryStoreItem(Item, Work.Index) == false)
					{
						return false;
						//Result = false;
					}
				}
					break;
				case ACTION::TAKE:
				{
					TScriptInterface<IHorrorItemInterface> ItemInterface;

					if (Inventory.TryTakeItem(Work.Index, ItemInterface) == false)
					{
						return false;
						//Result = false;
					}
				}
					break;
				default:
					break;
				}
			}

			return true;
			//return Result == Desire;
		}
	};

	std::vector<InsertTestCase> Cases =
	{
		// store
		InsertTestCase(
			"store test start", DesireTestResult(true),
			InventorySize(1, 1), 
			ItemSize(1, 1), ItemStackSize(1),
			{ 
				WorkUnit({0, 0}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Duplicate input in 0,0", DesireTestResult(false),
			InventorySize(1, 1), 
			ItemSize(1, 1), ItemStackSize(1),
			{ 
				WorkUnit({0, 0}, ACTION::STORE), 
				WorkUnit({0, 0}, ACTION::STORE), 
			}
		),

		InsertTestCase(
			"Duplicate input in 0,0 when stack size is 2", DesireTestResult(true),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(2),
			{ 
				WorkUnit({0, 0}, ACTION::STORE), 
				WorkUnit({0, 0}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Off to the up while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({-1, 0}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Off to the down while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({1, 0}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Off to the left while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({0, -1}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Off to the right while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({0, 1}, ACTION::STORE),
			}
		),

		// Size test
		InsertTestCase(
			"Exceeded size", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(2, 2), ItemStackSize(1),
			{
				WorkUnit({0, 0}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Off to the right while storing", DesireTestResult(true),
			InventorySize(2, 2),
			ItemSize(2, 2), ItemStackSize(1),
			{
				WorkUnit({0, 0}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Out of range on the right", DesireTestResult(false),
			InventorySize(2, 2),
			ItemSize(2, 2), ItemStackSize(1),
			{
				WorkUnit({0, 1}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Out of range on the Left", DesireTestResult(false),
			InventorySize(2, 2),
			ItemSize(2, 2), ItemStackSize(1),
			{
				WorkUnit({1, 1}, ACTION::STORE),
			}
		),

		InsertTestCase(
			"Out of range on the Down", DesireTestResult(false),
			InventorySize(2, 2),
			ItemSize(2, 2), ItemStackSize(1),
			{
				WorkUnit({1, 0}, ACTION::STORE),
			}
		),
		// take
		InsertTestCase(
			"take test start", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({0, 0}, ACTION::TAKE),
			}
		),

		InsertTestCase(
			"Off to the up while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({-1, 0}, ACTION::TAKE),
			}
		),

		InsertTestCase(
			"Off to the down while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({1, 0}, ACTION::TAKE),
			}
		),

		InsertTestCase(
			"Off to the left while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({0, -1}, ACTION::TAKE),
			}
		),

		InsertTestCase(
			"Off to the right while storing", DesireTestResult(false),
			InventorySize(1, 1),
			ItemSize(1, 1), ItemStackSize(1),
			{
				WorkUnit({0, 1}, ACTION::TAKE),
			}
		),

		// store and take	
		InsertTestCase(
			"store and take test start", DesireTestResult(true),
			InventorySize(1, 1), 
			ItemSize(1, 1), ItemStackSize(1),
			{ 
				WorkUnit({0, 0}, ACTION::STORE), 
				WorkUnit({0, 0}, ACTION::TAKE), 
			}
		),

		InsertTestCase(
			"Attempts to subtract from an empty space", DesireTestResult(false),
			InventorySize(1, 1), 
			ItemSize(1, 1), ItemStackSize(1),
			{ 
				WorkUnit({0, 0}, ACTION::STORE), 
				WorkUnit({0, 0}, ACTION::TAKE), 
				WorkUnit({0, 0}, ACTION::TAKE), 
			}
		),

		// 서로 다른 아이템에 대한 테스트
	};
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHorror2DInventoryInsertTest, "Horror.2DInventory.InsertTest", 
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter
)

bool FHorror2DInventoryInsertTest::RunTest(const FString& parameters)
{
	bool Result = true;
	
	for (const auto& Case : INSERT_TEST::Cases)
	{
		if (TestEqual(*Case.What, Case.Test(), Case.Desire) == false)
		{
			Result = false;
		}

		//if (TestTrue(*Case.What, Case.Test()) == false)
		//{
		//	Result = false;
		//}
	}

	return Result;
}

#endif