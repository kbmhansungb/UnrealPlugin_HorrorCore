// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorMoveableInterface.h"
#include "InputCoreTypes.h"
#include "HorrorSphereMoveableComponent.generated.h"

class UHorrorSphereMoveableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSphereMoveableDelegate, UHorrorSphereMoveableComponent*, PublisherSphereMoveableComponent);

UCLASS( ClassGroup=(Custom, Horror), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorSphereMoveableComponent : public USceneComponent,
	public IHorrorMoveableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "SphereMoveable|Horror", EditAnywhere, BlueprintReadWrite)
	float MaxRotationSpeed = 10.0f;

	UPROPERTY(Category = "SphereMoveable|Horror", EditAnywhere, BlueprintReadWrite)
	bool MaintainX = true;

	UPROPERTY(Category = "SphereMoveable|Horror", EditAnywhere, BlueprintReadWrite)
	bool MaintainY = true;

	// IHorrorAxisMoveableInterface에서 상속됨
protected:
	virtual void PrepareMoving_Implementation(const FHitResult& HitLocation) override;
	virtual void EndMoving_Implementation() override;
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const override;
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) override;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FSphereMoveableDelegate StartMovingDelegate;

	UPROPERTY(BlueprintAssignable)
	FSphereMoveableDelegate EndMovingDelegate;

	UPROPERTY(BlueprintAssignable)
	FSphereMoveableDelegate BlockMovingDelegate;

#pragma region Implementation

public:
	FVector ConvertRelativeVector(const FVector& IntersectionLocation) const;
	FVector DropVectorParameter(const FVector& SphereVector) const;
	void UpdateLastBlocking(bool NewHasBlocking);

private:
	float SphereRadius;
	FQuat IntersectionCorrectionQuarts;
	bool LastBlocking;

#pragma endregion

};
