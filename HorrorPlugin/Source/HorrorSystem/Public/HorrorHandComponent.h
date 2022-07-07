// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorHandComponent.generated.h"

UENUM(BlueprintType)
enum EHandType
{
	RIGHT,
	LEFT,
};

USTRUCT(BlueprintType)
struct FHoldStruct
{
	GENERATED_BODY()

public:
	FHoldStruct() {}
	FHoldStruct(const FVector& RelativePosition) : RelativePosition(RelativePosition) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* HoldItem;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSYSTEM_API UHorrorHandComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UHorrorHandComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct RightHand = FHoldStruct(FVector(0.f, 20.f, 0.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct LeftHand = FHoldStruct(FVector(0.f, -20.f, 0.f));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartOffset = FVector(0.f, 0.f, -30.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpSpeed = 5.0f;

public:
	UFUNCTION(BlueprintCallable)
	void Hold(const EHandType Type, AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void Swap();

	UFUNCTION(BlueprintCallable)
	void Put(const EHandType Type);

public:
	void Lerp(float Deleta);
	void SetStart(const EHandType Type, AActor* Actor);
};
