// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "HorrorMoveableInterface.h"
#include "HorrorPlaneMoveableComponent.generated.h"

class UHorrorPlaneMoveableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlaneMoveableDelegate, UHorrorPlaneMoveableComponent*, PublisherPlaneMoveableComponent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorPlaneMoveableComponent : public UPrimitiveComponent,
	public IHorrorMoveableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D XRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D YRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStepLength = 100.0f;

	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	float AllowIntersectionRadian = 0.08f;

	// IHorrorAxisMoveableInterface에서 상속됨
public:
	virtual void PrepareMoving_Implementation(const FHitResult& HitLocation) override;
	virtual void EndMoving_Implementation() override;
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const override;
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) override;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate StartMovingDelegate;

	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate EndMovingDelegate;

	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate BlockMovingDelegate;

#pragma region Implementation

public:
	bool IsValidDirection(const FVector& Direction) const;

	void UpdateRelativeWithVirtualTransform(const FTransform& VirtualTransform);
	FTransform GetNewWorldTransform(const FVector& IntersectionLocation);

	void SetDestination(const FTransform& NewDestinationTransfrom);
	FTransform GetStepToDestination(const float DeletaTime) const;

	void UpdateLastBlocking(bool NewHasBlocking);

private:
	// WorldSpace
	FTransform DestinationTransfrom;

	FVector LastIntersectionLocation;
	FTransform RelativeWithVirtualTransform;

	bool LastBlocking;
#pragma endregion
};
