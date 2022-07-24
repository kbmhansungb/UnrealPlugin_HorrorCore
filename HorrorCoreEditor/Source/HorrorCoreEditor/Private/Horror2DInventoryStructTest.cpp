// 2022 07    Bum moo, Kim

#include "Horror2DInventoryStructTest.h"

#include "Misc/AutomationTest.h"
#include "Engine/DataTable.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHorror2DInventoryInsertTest, "Horror.2DInventory.InsertTest", 
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter
)

bool InsertTest(const FHorrorInventory2DInsertTest& InsertTest)
{
	FHorror2DInventoryStruct Inventory = InsertTest.InventoryInfo;
	
	for (const auto& WorkUnit : InsertTest.WorkUnits)
	{
		TScriptInterface<IHorrorItemInterface> NowInterface = WorkUnit.HorrorItem;

		switch (WorkUnit.Action)
		{
		case EACTION::STORE:
		{
			if (Inventory.TryStoreItem(NowInterface, WorkUnit.Index) == false)
			{
				return false;
			}
		}
		break;
		case EACTION::TAKE:
		{
			TScriptInterface<IHorrorItemInterface> ReturnInterface;

			if (Inventory.TryTakeItem(WorkUnit.Index, ReturnInterface) == false)
			{
				return false;
			}

			if (NowInterface != ReturnInterface)
			{
				return false;
			}
		}
		break;
		default:
			break;
		}
	}

	return true;
}

bool FHorror2DInventoryInsertTest::RunTest(const FString& parameters)
{
	bool Result = true;
	
	UDataTable* TestDataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/HorrorCoreEditor/Horror2DInventoryTest/Horror2DInventoryTestDataTable.Horror2DInventoryTestDataTable'"));
	TestNotNull("TestDataTable is not valid.", TestDataTable);
	if (!TestDataTable)
	{
		return false;
	}

	TArray<FName> Names = TestDataTable->GetRowNames();
	TArray<FHorrorInventory2DInsertTest*> InsertTestPtrs;
	TestDataTable->GetAllRows(TEXT("Horror 2DInventory InsertTest : Load all test cases."), InsertTestPtrs);
	
	for (int i = 0; i < Names.Num(); ++i)
	{
		if (TestEqual(*Names[i].ToString(), InsertTest(*InsertTestPtrs[i]), InsertTestPtrs[i]->Desire) == false)
		{
			Result = false;
		}
	}

	return Result;
}