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
	FVector2D PitchArange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D YawArange = FVector2D(-30.0f, 30.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D RollArange = FVector2D(-30.0f, 30.0f);

	UFUNCTION(BlueprintCallable)
	void ClickedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	virtual FRay GetNowMouseRay(APlayerController* PC);
	
	// IHorrorAxisMoveableInterface에서 상속됨
	virtual FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction);
	virtual FTransform GetNewReleativeTransform(const FVector& OutClosestPoint);
	virtual FTransform ClampTransform(const FTransform& Transform);

private:
	FKey Key;
	float SphereRadius;
	FVector FirstClosestPoint;
	FTransform OriginalRelativeTransform;
};
