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
	float MaxStepLength = 100.0f;

	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	float AllowIntersectionRadian = 0.08f;
	
	UPROPERTY(Category = "Moveable|Horror", EditAnywhere, BlueprintReadWrite)
	bool MaintainX = true;

	UPROPERTY(Category = "Moveable|Horror", EditAnywhere, BlueprintReadWrite)
	bool MaintainY = true;

	// IHorrorAxisMoveableInterface에서 상속됨
public:
	virtual void PrepareMoving_Implementation(const FHitResult& HitLocation) override;
	virtual void EndMoving_Implementation() override;
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const override;
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) override;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate PrepareMovingDelegate;

	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate EndMovingDelegate;

	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate MoveDelegate;

	UPROPERTY(BlueprintAssignable)
	FPlaneMoveableDelegate BlockMovingDelegate;

#pragma region Implementation

public:
	/*
	 * 평면에대해서 방향이 같거나, 많이 평평하다면, 교차점은 유효하지 않거나 무한대의 값일 수 있습니다.
	 * 
	 * @param Direction 평면과의 교차점을 구하고자 하는 방향으로 정규화 되어 있다고 가정합니다.
	 */
	bool IsValidDirection(const FVector& Direction) const;
	FVector DropVectorParameter(const FVector& IntersectionVector) const;

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
