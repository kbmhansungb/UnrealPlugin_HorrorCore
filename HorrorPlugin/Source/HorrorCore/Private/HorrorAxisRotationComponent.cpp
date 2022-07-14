// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorAxisRotationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/PrimitiveComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UHorrorAxisRotationComponent::UHorrorAxisRotationComponent()
{
}

void UHorrorAxisRotationComponent::ApplyAxisMovealbe_Implementation(USceneComponent* Target, const FVector2D& Deleta)
{
	APlayerCameraManager* PCM = UGameplayStatics::GetPlayerController(this, 0)->PlayerCameraManager;
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Target);

	const FVector& Pos = Target->GetComponentLocation();
	const FQuat& OldQuat = Target->GetComponentQuat();
	const FQuat& DeletaQuat = FQuat(PCM->GetActorUpVector(), -Deleta.X) * FQuat(PCM->GetActorRightVector(), -Deleta.Y);
	FQuat NewQuat = DeletaQuat * OldQuat;
	
	TArray<FHitResult> HitResults;
	FComponentQueryParams Parms(FName(), Target->GetOwner());
	auto Sweep = [&]() -> void 
	{
		this->GetWorld()->ComponentSweepMulti(HitResults, Primitive, Pos, Pos, NewQuat, Parms);
	};
	Sweep();

	if (HitResults.Num())
	{
		for (const auto& Hit : HitResults)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 2.0f, 16, FColor::Red);
			
			const FVector& R = Hit.ImpactPoint - Pos;
			const FQuat& Adjust = FRotationMatrix::MakeFromX(R).ToQuat() * FRotationMatrix::MakeFromX(R + Hit.Normal * Hit.PenetrationDepth).ToQuat().Inverse();
			NewQuat *= Adjust;
		}

		Sweep();

		if (HitResults.Num())
		{
			NewQuat = OldQuat;
		}

		return;
	}

	Target->SetWorldRotation(NewQuat);
}

