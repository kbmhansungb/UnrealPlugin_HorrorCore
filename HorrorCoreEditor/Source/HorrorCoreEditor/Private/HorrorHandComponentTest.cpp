// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorHandComponentTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHorrorHandComponentTest, "Horror.HandComponentTest",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter
);

bool FHorrorHandComponentTest::RunTest(const FString& Parameters)
{
	UHorrorHandComponent* HandComponent = NewObject<UHorrorHandComponent>();

	UTestHorrorHoldableObject* A = NewObject<UTestHorrorHoldableObject>();
	UTestHorrorHoldableObject* B = NewObject<UTestHorrorHoldableObject>();

	HandComponent->HandDominance = EHandType::RIGHT;

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