// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorAxisMoveableInterface.h"
#include "InputCoreTypes.h"
#include "HorrorAxisRotationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORCORE_API UHorrorAxisRotationComponent : public USceneComponent,
	public IHorrorAxisMoveableInterface
{
	GENERATED_BODY()

public:	
	UHorrorAxisRotationComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetComponentTickEnabled(bool bEnabled) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Swing1Limit;// = FVector2D(-60.0f, 60.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Swing2Limit;// = FVector2D(-60.0f, 60.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TwistLimit = FVector2D(-10.0f, 10.0f);

	UFUNCTION(BlueprintCallable)
	void ClickedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	virtual FRay GetNowMouseRay(APlayerController* PC);
	
protected:
	// IHorrorAxisMoveableInterface에서 상속됨
	virtual void PreAxisMoveable(const FHitResult& HitResult) override;
	virtual void ApplyAxisMoveable(const FVector& Origin, const FVector& Direction) override;

	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction) const override;

	virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint) const override;
	virtual FTransform ClampTransform(const FTransform& Transform) const override;
	virtual FTransform AdjustTransform(const FTransform& Transform) const override;



private:
	FKey Key;
	float SphereRadius;
	FVector FirstClosestPoint;
	FTransform OriginalRelativeTransform;
};
