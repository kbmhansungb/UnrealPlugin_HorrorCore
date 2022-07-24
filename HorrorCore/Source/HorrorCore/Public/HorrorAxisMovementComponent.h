// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorAxisMoveableInterface.h"
#include "HorrorAxisMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorAxisMovementComponent : public USceneComponent,
	public IHorrorAxisMoveableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHorrorAxisMovementComponent();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D XRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D YRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStepSize = 10.0f;

protected:
	// IHorrorAxisMoveableInterface에서 상속됨
	virtual void PreAxisMoveable(const FHitResult& HitResult) override;
	virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) override;

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override;

	virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const override;
	virtual FTransform ClampTransform(const FTransform& Transform) const override;
	virtual FTransform AdjustTransform(const FTransform& Transform) const override;

private:
	FVector FirsColsestPoint;
};
