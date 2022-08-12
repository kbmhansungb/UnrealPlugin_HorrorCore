// 2022 06    Bum moo, Kim    Free copyright

#include "HorrorInventoryComponentTest.h"
#include <Misc/AutomationTest.h>
#include "Tests/AutomationEditorCommon.h"

UTestInventoryComponent::UTestInventoryComponent()
{
	Inventory.InventorySize = FIntSize2D(1, 1);
}

ATestInventoryDelegateItemActor::ATestInventoryDelegateItemActor()
{
}

void ATestInventoryDelegateItemActor::GetItemInterface_Implementation(TScriptInterface<IHorrorItemInterface>& ReturnItemInterface)
{
	ReturnItemInterface = ItemInterface;
}

void UTestInventoryDelegateItem::Ready()
{
	SaveResponse = false;
}

bool UTestInventoryDelegateItem::IsDelegated() const
{
	return SaveResponse;
}

void UTestInventoryDelegateItem::GetItemName_Implementation(FName& ItemName) const
{
	ItemName = FName(GetName());
}

int32 UTestInventoryDelegateItem::GetItemMaxStack_Implementation() const
{
	return 1;
}

void UTestInventoryDelegateItem::GetItemActorClass_Implementation(TSubclassOf<AActor>& ItemActorClass) const
{
	ItemActorClass = ATestInventoryDelegateItemActor::StaticClass();
}

void UTestInventoryDelegateItem::GetIconSize_Implementation(FIntSize2D& ItemIntSize) const
{
	ItemIntSize = FIntSize2D(1, 1);
}

void UTestInventoryDelegateItem::GetIconBrush_Implementation(FSlateBrush& ItemIcon) const
{
	ItemIcon = FSlateBrush();
}

/*
* ATestInventoryDelegateItemActor에서 함수를 호출하지 않습니다....
*/

//IMPLEMENT_SIMPLE_AUTOMATION_TEST(
//	FHorrorInventoryComponentStoreTakeDelegateTest, "Horror.InventoryComponent.StoreTakeDelegate",
//	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter
//);

//bool FHorrorInventoryComponentStoreTakeDelegateTest::RunTest(const FString& Parameters)
//{
//	//UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
//
//	UTestInventoryComponent* InventoryComponent = NewObject<UTestInventoryComponent>();
//	ATestInventoryDelegateItemActor* ItemActor = NewObject<ATestInventoryDelegateItemActor>();
//	UTestInventoryDelegateItem* Item = NewObject<UTestInventoryDelegateItem>();
//
//	FScriptDelegate SD;
//	SD.BindUFunction(Item, FName("IsDelegated"));
//	InventoryComponent->InventoryChangedDelegate.Add(SD);
//
//	TScriptInterface<IHorrorItemInterface> ItemInterface = Item;
//	ItemActor->ItemInterface = Item;
//	
//	check(ItemInterface);
//	ItemInterface = TScriptInterface<IHorrorItemInterface>{};
//
//	const TScriptInterface<IHorrorItemActorInterface>& ItemActorInterface = ItemActor;
//	IHorrorItemActorInterface::Execute_GetItemInterface(ItemActorInterface.GetObject(), ItemInterface);
//
//	check(ItemActor);
//	check(ItemActorInterface);
//	check(ItemInterface);
//
//	Item->Ready();
//	IHorrorInventoryInterface::Execute_StoreItem(InventoryComponent, nullptr, FIntPoint(0, 0));
//	if (Item->IsDelegated())
//	{
//		AddError("Delegate is called.");
//	}
//
//	Item->Ready();
//	IHorrorInventoryInterface::Execute_StoreItem(InventoryComponent, ItemActor, FIntPoint(0, 0));
//	if (!Item->IsDelegated())
//	{
//		AddError("Delegate is not called.");
//	}
//
//	TScriptInterface<IHorrorItemActorInterface> ReturnItemActorInterface;
//	Item->Ready();
//	IHorrorInventoryInterface::Execute_TakeItem(InventoryComponent, FIntPoint(0, 0), ReturnItemActorInterface);
//	if (!Item->IsDelegated())
//	{
//		AddError("Delegate is not called.");
//	}
//
//	Item->Ready();
//	IHorrorInventoryInterface::Execute_TakeItem(InventoryComponent, FIntPoint(0, 0), ReturnItemActorInterface);
//	if (Item->IsDelegated())
//	{
//		AddError("Delegate is called.");
//	}
//
//	return true;
//}