// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorHandComponentTest.h"
#include "Misc/AutomationTest.h"


void UTestHorrorHoldableObject::ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHorrorHandComponentTest, "Horror.HandComponent.Hold_Swap_ReleaseTest",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter
);

bool FHorrorHandComponentTest::RunTest(const FString& Parameters)
{
	UHorrorHandComponent* HandComponent = NewObject<UHorrorHandComponent>();
	HandComponent->HandDominance = EHandType::RIGHT;

	UTestHorrorHoldableObject* A = NewObject<UTestHorrorHoldableObject>();
	UTestHorrorHoldableObject* B = NewObject<UTestHorrorHoldableObject>();

	if (!HandComponent->CompareHoldedObject(nullptr, nullptr))
	{
		AddError(FString("Hand not reset."));
	}

	HandComponent->Hold(EHandType::RIGHT, A);
	if (!HandComponent->CompareHoldedObject(nullptr, A))
	{
		AddError(FString("Hand does not pick up object."));
	}

	HandComponent->Hold(EHandType::RIGHT, B);
	if (!HandComponent->CompareHoldedObject(nullptr, A))
	{
		AddError(FString("Replaced the item in hand."));
	}

	HandComponent->Swap();
	if (!HandComponent->CompareHoldedObject(A, nullptr))
	{
		AddError(FString("Hands not swapped."));
	}

	HandComponent->Hold(EHandType::RIGHT, B);
	if (!HandComponent->CompareHoldedObject(A, B))
	{
		AddError(FString("Hand does not pick up object."));
	}

	HandComponent->Swap();
	if (!HandComponent->CompareHoldedObject(B, A))
	{
		AddError(FString("Hands not swapped."));
	}

	HandComponent->Release(EHandType::RIGHT);
	if (!HandComponent->CompareHoldedObject(B, nullptr))
	{
		AddError(FString("Hands do not discard items."));
	}

	HandComponent->Swap();
	if (!HandComponent->CompareHoldedObject(nullptr, B))
	{
		AddError(FString("Hands not swapped."));
	}

	HandComponent->Release(EHandType::RIGHT);
	if (!HandComponent->CompareHoldedObject(nullptr, nullptr))
	{
		AddError(FString("Hands do not discard items."));
	}
	return true;
}



void UTestHorrorHoldableHoldReleaseTestObject::ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface)
{
	this->IsReleased = true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHorrorHandComponentReleaseHoldableTest, "Horror.HandComponent.Hold_ReleaseResponseTest",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter
);

bool FHorrorHandComponentReleaseHoldableTest::RunTest(const FString& Parameters)
{
	UHorrorHandComponent* HandComponent = NewObject<UHorrorHandComponent>();
	HandComponent->HandDominance = EHandType::RIGHT;

	UTestHorrorHoldableHoldReleaseTestObject* HoldableObject = NewObject<UTestHorrorHoldableHoldReleaseTestObject>();

	HandComponent->Hold(EHandType::RIGHT, HoldableObject);
	if (!HandComponent->CompareHoldedObject(nullptr, HoldableObject))
	{
		AddError(FString("Hand does not pick up object."));
	}

	HandComponent->Release(EHandType::RIGHT);
	if (!HandComponent->CompareHoldedObject(nullptr, nullptr))
	{
		AddError(FString("Hands do not discard items."));
	}

	if (!HoldableObject->IsReleased)
	{
		AddError(FString("Holdable is not released."));
	}

	return true;
}
