// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorHandInterface.h"
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
	TScriptInterface<IHorrorHoldableInterface> HoldItem;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSYSTEM_API UHorrorHandComponent : public USceneComponent, 
	public IHorrorHandInterface
{
	GENERATED_BODY()

public:	
	UHorrorHandComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool IsDominanceHand_Implementation() const override;
	virtual TScriptInterface<IHorrorHoldableInterface> GetHoldable_Implementation() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EHandType> HandDominance = EHandType::RIGHT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct RightHand = FHoldStruct(FVector(0.f, 20.f, 0.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct LeftHand = FHoldStruct(FVector(0.f, -20.f, 0.f));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartOffset = FVector(0.f, 0.f, -30.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpSpeed = 5.0f;

	FORCEINLINE const FHoldStruct* GetHoldStruct(const EHandType Type) const;
	FORCEINLINE FHoldStruct* GetHoldStruct(const EHandType Type);

public:
	UFUNCTION(BlueprintCallable)
	bool IsEmptyHand(const EHandType Type);

	UFUNCTION(BlueprintCallable)
	void Hold(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable);

	UFUNCTION(BlueprintCallable)
	void Swap();

	UFUNCTION(BlueprintCallable)
	void Release(const EHandType Type);

public:
	void Lerp(float Deleta);
	void SetStart(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable);
};

FORCEINLINE const FHoldStruct* UHorrorHandComponent::GetHoldStruct(const EHandType Type) const
{
	switch (Type)
	{
	case EHandType::LEFT:
		return &LeftHand;
		break;
	case EHandType::RIGHT:
		return &RightHand;
		break;
	default:
		check(false && "Need add case");
		return nullptr;
	}
}

FORCEINLINE FHoldStruct* UHorrorHandComponent::GetHoldStruct(const EHandType Type)
{
	switch (Type)
	{
	case EHandType::LEFT:
		return &LeftHand;
		break;
	case EHandType::RIGHT:
		return &RightHand;
		break;
	default:
		check(false && "Need add case");
		return nullptr;
	}
}
