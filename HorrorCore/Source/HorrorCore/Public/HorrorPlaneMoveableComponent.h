// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "HorrorMoveableInterface.h"
#include "HorrorPlaneMoveableComponent.generated.h"


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
	virtual FVector GetIntersectionPoint_Implementation(const FVector& Origin, const FVector& Direction) const override;
	virtual void ApplyMoving_Implementation(const FVector& IntersectionLocation) override;
	virtual FTransform GetNewVirtualTransform_Implementation(const FVector& IntersectionLocation) const override;

public:
	bool IsValidDirection(const FVector& Direction) const;

public:
	void UpdateVirtualRelativeTransform(const FTransform& VirtualTransform, const FTransform& RelativeTransform);

	FTransform GetComponentTransformFromNewRelative(const FTransform& NewRelativeTransform) const;
	void SetDestination(const FTransform& NewDestinationRelativeTransfrom);
	FTransform GetStepToDestination(const float DeletaTime) const;

private:
	FVector ToFirstIntersectionFromWorldLocation;

	FVector FirstIntersectionLocation;
	FTransform OriginalRelativeTransform;

	FVector LastIntersectionLocation;
	FTransform DestinationRelativeTransfrom;

	FTransform VirtualToRelativeTransform;

public:
	inline const FVector& GetFirstIntersectionLocation() const { return FirstIntersectionLocation; }
	inline const FTransform& GetOriginalRelativeTransform() const { return OriginalRelativeTransform; }
	inline const FVector& GetLastIntersectionLocation() const { return LastIntersectionLocation; }
	inline const FTransform& GetDestinationRelativeTransfrom() const { return DestinationRelativeTransfrom; }
};
