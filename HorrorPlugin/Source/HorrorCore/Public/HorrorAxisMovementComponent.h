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

	// IHorrorAxisMoveableInterface에서 상속됨
	virtual void ApplyAxisMovealbe_Implementation(USceneComponent* Target, const FVector2D&) override;

	void ApplyAxisMoveableToChild(USceneComponent* Target, const FVector2D& RelativePos);
};
