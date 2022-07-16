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
	
	UFUNCTION(BlueprintCallable)
	void ClickedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void ReleasedMouse(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	// IHorrorAxisMoveableInterface에서 상속됨

	void PreAxisMoveable()
	{
	}
	void PostAixsMoveable()
	{
	}
	FVector GetIntersectionPoint(const FVector& Origin, const FVector& Direction);

	FRay GetNowMouseRay(APlayerController* PC);

	FTransform GetVirtualTransform(const FVector& OutClosestPoint);


private:
	UPrimitiveComponent* ActiveComponent;
	FKey Key;
	float SphereRadius;
	FVector FirstClosestPoint;
	FTransform VirtualTransform;
	FTransform RelativeTransform;
};
