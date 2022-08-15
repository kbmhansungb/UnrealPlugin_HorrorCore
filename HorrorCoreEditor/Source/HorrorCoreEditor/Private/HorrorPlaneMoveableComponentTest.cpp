// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorPlaneMoveableComponentTest.h"
#include <HorrorCore/Public/HorrorPlaneMoveableComponent.h>
#include <Misc/AutomationTest.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHorrorPlaneMoveableComponentTest, "Horror.PlaneMoveableComponent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter);


bool FHorrorPlaneMoveableComponentTest::RunTest(const FString& Parameters)
{
	// 목적지를 확인하고, 목적지 까지 가는 걸음을 확인합니다.
	{
		UHorrorPlaneMoveableComponent* PlaneMoveableComponent = NewObject<UHorrorPlaneMoveableComponent>();

		FHitResult HitResult;
		HitResult.TraceStart = FVector::ZeroVector;
		HitResult.TraceEnd = FVector::DownVector;
		HitResult.Location = FVector::ZeroVector;

		IHorrorMoveableInterface::Execute_PrepareMoving(PlaneMoveableComponent, HitResult);

		const FVector& NewIntersectionLocation = FVector(100.f, 0.f, 0.f);
		const FTransform& NewRelativeTransform = IHorrorMoveableInterface::Execute_GetNewVirtualTransform(PlaneMoveableComponent, NewIntersectionLocation);
		
		PlaneMoveableComponent->SetDestination(NewRelativeTransform);
		if ( (PlaneMoveableComponent->GetDestinationRelativeTransfrom().GetLocation() - NewIntersectionLocation).Size() > FLT_EPSILON )
		{
			AddError("Destination is not corrected.");
		}

		const FTransform& StepRelativeTransform = PlaneMoveableComponent->GetStepToDestination(1.0f);
		if ( (StepRelativeTransform.GetLocation() - FVector(PlaneMoveableComponent->MaxStepLength, 0.f, 0.f)).Size() > FLT_EPSILON )
		{
			AddError("Step is not corrected.");
		}
	}

	return true;
}